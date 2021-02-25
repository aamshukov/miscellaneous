#! /usr/bin/env python3
# -*- encoding: utf-8 -*-
"""
AWS Lambda ffmpeg handler
"""
# pylint: disable=too-many-lines
import os
import datetime
import hashlib
import hmac
import urllib
import urllib.request
import math

from urllib.parse import unquote_plus

# pylint: disable=import-error
import botocore
import boto3

import requests

from domain_helper import execute_command

AWS_ACCESS_KEY = ''
AWS_SECRET_ACCESS_KEY = ''

AWS_ENTITY_TYPE_NAME = 'entity-type'
AWS_ENTITY_TYPE_LXX = 'LXX'
AWS_ENTITY_TYPE_IMAGE = 'avatar'
AWS_ENTITY_TYPE_JXX = 'JXX'
AWS_ENTITY_TYPE_JXX_AS_LXX = 'JXX-as-LXX'

AWS_METADATA_STATUS_NAME = 'status'
AWS_METADATA_STATUS_COMPLETED = 'done'

AWS_METADATA_AUDIO_START = 'audio-start'
AWS_METADATA_AUDIO_END = 'audio-end'

AWS_METADATA_USER_ID = 'user-id'
AWS_METADATA_USER_NAME = 'username'
AWS_METADATA_LXX_ID = 'LXX-id'
AWS_METADATA_LXX_TITLE = 'title'

AWS_METADATA_EXPIRY = 'JXX-expiry'

AWS_METADATA_ENDPOINT_HOST = 'hostname'

AWS_LXX_PAYLOAD = '{{"status": "{status}", "bucket": "{bucket}", ' \
                   '"keys": {{ "LXX": "{key}", "image": "{gif_static_key}", "imagegif": ' \
                   '"{gif_primary_key}", "imagepreview": "{gif_preview_key}" }}, ' \
                   '"metadata": {metadata}}}'
AWS_AVATAR_PAYLOAD = '{{"status": "{status}", "bucket": "{bucket}", "keys": {{ "avatar": ' \
                     '"{avatar_key}", "thumbnail": "{thumbnail_key}" }}, "metadata": {metadata}}}'
AWS_JXX_PAYLOAD = '{{"status": "{status}", "bucket": "{bucket}", ' \
                   '"keys": {{ "JXX": "{key}" }}, "metadata": {metadata}}}'
AWS_JXX_AS_LXX_PAYLOAD = '{{"status": "{status}", "bucket": "{bucket}", ' \
                          '"keys": {{ "LXX": "{key}" }}, "metadata": {metadata}}}'

AWS_LAMBDA_STATUS = '{{"payload": {payload}, ' \
                    '"post_status_code": "{code}", "post_status_text": "{text}"}}'

AWS_LXX_ENDPOINT = '{domain}/api/users/{user_id}/LXXs'
AWS_LXX_VERSION_ENDPOINT = '{domain}/api/LXXs/{LXX_id}'
AWS_JXX_ENDPOINT = '{domain}/api/users/{user_id}/JXXs'
AWS_JXX_AS_LXX_ENDPOINT = '{domain}/api/users/{user_id}/LXXs'
AWS_AVATAR_ENDPOINT = '{domain}/api/users/{user_id}/avatar'

AWS_LAMBDA_WORKING_DIR = '/tmp'
AWS_LAMBDA_GUARD_FILE = os.path.join(AWS_LAMBDA_WORKING_DIR, 'guard')

AWS_MULTRACK_FILE_NAME = 'files.completed'
AWS_MULTRACK_FILE_EXT = '.Track-{0}.rawfilepart'
AWS_MULTRACK_STATUS = 'files-completed'
AWS_MULTRACK_KEYS = 'track-keys'
AWS_MULTRACK_TRACKS = 'total-tracks'

AWS_EXISTING_ENTITY_TYPE = 'existing-entity-type'
AWS_EXISTING_AUDIO_KEY = 'existing-audio-key'


def get_s3_client():
    result = boto3.client('s3',
                          aws_access_key_id=AWS_ACCESS_KEY,
                          aws_secret_access_key=AWS_SECRET_ACCESS_KEY)
    return result


def build_src_file_name(key):
    resource_name, _ = os.path.splitext(key)  # strip off .rawfile
    return os.path.basename(resource_name)


def build_dst_file_name(key, file_name, subkey=None):
    base_key = os.path.join(os.path.dirname(os.path.dirname(key)), 'output')
    if subkey is not None:
        base_key = os.path.join(base_key, subkey)
    resource_name = os.path.basename(file_name)
    return os.path.join(base_key, resource_name)


def build_timestamp():
    return datetime.datetime.strftime(datetime.datetime.now(), "%Y%m%d%H%M%S")


def get_bucket_key(event):
    # pylint: disable=broad-except
    # pylint: disable=bare-except
    try:
        bucket = event['Records'][0]['s3']['bucket']['name']
    except KeyError:
        bucket = event['bucket']
    try:
        key = unquote_plus(event['Records'][0]['s3']['object']['key'])
    except KeyError:
        try:
            key = unquote_plus(event['key'])
        except KeyError:
            key = ''
    return bucket, key


def decorate_bucket_key(bucket, key):
    return '{0}/{1}'.format(bucket, key)


def get_object_type(metadata):
    return metadata[AWS_ENTITY_TYPE_NAME]


def get_status(metadata):
    result = ''
    try:
        result = metadata[AWS_METADATA_STATUS_NAME]
    except KeyError:
        pass
    return result


def wait_for_object(s3, bucket, key):
    if key:  # no need to wait for external objects
        print("Waiting for input object '{0}' to appear ...".format(decorate_bucket_key(bucket, key)))
        waiter = s3.get_waiter('object_exists')
        waiter.wait(Bucket=bucket, Key=key)
        print("Completed waiting input  for object '{0}'.".format(decorate_bucket_key(bucket, key)))


def get_object_metadata(s3, event):
    print("Fetching metadata ...")
    bucket, key = get_bucket_key(event)
    try:
        save_as_LXX = event['entity-type'] == AWS_ENTITY_TYPE_JXX_AS_LXX
    except KeyError:
        save_as_LXX = False
    try:
        external_avatar = event['entity-type'] == AWS_ENTITY_TYPE_IMAGE and 'url' in event
    except KeyError:
        external_avatar = False
    if save_as_LXX or external_avatar:
        result = event
    else:
        metadata = s3.head_object(Bucket=bucket, Key=key)
        result = metadata['Metadata']
    if not result:
        raise RuntimeError("Missing metadata.")
    print('Metadata:')
    print(result)
    print("Fetched metadata of {0}/{1}.".format(bucket, key))
    return result


def download_file(s3, event, metadata):
    print("Downloading file ...")
    try:
        bucket, key = get_bucket_key(event)
        if 'url' in metadata:
            url = metadata['url']
            print("URL: {}".format(url))
            timestamp = build_timestamp()
            file_name = 'avatar_{}.jpg'.format(timestamp)
            print("File name: {}".format(file_name))
            target_path = os.path.join(AWS_LAMBDA_WORKING_DIR, file_name)
            print("About to fetch file '{0}' ...".format(target_path))
            urllib.request.urlretrieve(url, target_path)
        else:
            target_path = os.path.join(AWS_LAMBDA_WORKING_DIR, build_src_file_name(key))
            print("About to fetch file '{0}' ...".format(target_path))
            with open(target_path, "wb") as file_object:
                s3.download_fileobj(bucket, key, file_object)
        result = target_path
        execute_command(['ls', '-alh', AWS_LAMBDA_WORKING_DIR])  # ??
    except botocore.exceptions.ClientError as ex:
        if ex.response['Error']['Code'] == "404":
            print("The object does not exist.")
        raise
    print("Downloaded file '{0}'.".format(result))
    return result


def download_files(s3, bucket, track_keys, existing_crap=None):
    print("Downloading {} files ...".format(len(track_keys)))
    result = list()
    try:
        count = 0
        for i, track_key in enumerate(track_keys):
            if existing_crap is not None and track_key in existing_crap:
                key = track_key
                target_path = os.path.join(AWS_LAMBDA_WORKING_DIR, os.path.basename(track_key))
            else:
                key = '{0}{1}'.format(track_key, AWS_MULTRACK_FILE_EXT.format(i))
                target_path = os.path.join(AWS_LAMBDA_WORKING_DIR,
                                           os.path.basename(track_key)) + \
                    AWS_MULTRACK_FILE_EXT.format(i)
            print("About to fetch key '{0}' into file '{1}' ...".format(key, target_path))
            with open(target_path, "wb") as file_object:
                s3.download_fileobj(bucket, key, file_object)
                count += 1
                result.append(target_path)
        execute_command(['ls', '-alh', AWS_LAMBDA_WORKING_DIR])  # ??
    except botocore.exceptions.ClientError as ex:
        if ex.response['Error']['Code'] == "404":
            print("The object does not exist.")
        raise
    print("Downloaded {} files.".format(count))
    return result


def download_resource(url, prefix):
    print("Downloading resource ...")
    try:
        print("URL: {}".format(url))
        _, file_name = os.path.split(url)
        _, ext = os.path.splitext(file_name)
        timestamp = build_timestamp()
        file_name = '{0}_{1}{2}'.format(prefix, timestamp, ext)
        print("File name: {}".format(file_name))
        target_path = os.path.join(AWS_LAMBDA_WORKING_DIR, file_name)
        print("About to fetch file '{0}' ...".format(target_path))
        urllib.request.urlretrieve(url, target_path)
        result = target_path
    except botocore.exceptions.ClientError as ex:
        if ex.response['Error']['Code'] == "404":
            print("The resource does not exist.")
        raise
    print("Downloaded resource '{0}'.".format(result))
    return result


def upload_file(s3, event, metadata, file_name, content_type, make_public, subkey=None):
    print("Uploading file '{0}' ...".format(file_name))
    try:
        metadata['status'] = AWS_METADATA_STATUS_COMPLETED
        bucket, key = get_bucket_key(event)
        if get_object_type(metadata) == AWS_ENTITY_TYPE_JXX_AS_LXX:
            parts = key.split('/')
            timestamp = build_timestamp()
            new_key = os.path.join(parts[0],  # users
                                   metadata[AWS_METADATA_USER_NAME],
                                   'LXXs',
                                   metadata[AWS_METADATA_LXX_TITLE].replace(' ', '-'),
                                   'output',
                                   'LXX_{0}-zopa.mp3'.format(timestamp))
        elif get_object_type(metadata) == AWS_ENTITY_TYPE_IMAGE:
            try:
                external_avatar = event['entity-type'] == AWS_ENTITY_TYPE_IMAGE and 'url' in event
            except KeyError:
                external_avatar = False
            if external_avatar:
                tmp_key = os.path.join('users',
                                       metadata[AWS_METADATA_USER_NAME],
                                       'avatars',
                                       'dummy')
            else:
                tmp_key = key
            new_key = build_dst_file_name(tmp_key, file_name, subkey)
        else:
            new_key = build_dst_file_name(key, file_name, subkey)
        print("Created new key '{0}'".format(new_key))
        print("About to upload '{0}' ...".format(file_name))
        s3.upload_file(file_name,
                       bucket,
                       new_key,
                       ExtraArgs={'ContentType': '{}'.format(content_type),
                                  'Metadata': metadata})
        print("Uploaded '{0}'".format(file_name))
        if make_public:
            print("Making public ...")
            s3resource = boto3.resource('s3')
            object_acl = s3resource.ObjectAcl(bucket, new_key)
            object_acl.put(ACL='public-read')
        result = new_key
    except botocore.exceptions.ClientError as ex:
        if ex.response['Error']['Code'] == "404":
            print("The object does not exist.")
        raise
    print("Uploaded file '{0}' as {1}.".format(file_name, result))
    return result


def delete_file(event, metadata):
    print("Deleting source file ...")
    try:
        object_type = get_object_type(metadata)
        if object_type != AWS_ENTITY_TYPE_JXX_AS_LXX:
            s3 = boto3.resource('s3',
                                aws_access_key_id=AWS_ACCESS_KEY,
                                aws_secret_access_key=AWS_SECRET_ACCESS_KEY)
            bucket, key = get_bucket_key(event)
            if key:
                s3.Object(bucket, key).delete()
    except botocore.exceptions.ClientError as ex:
        if ex.response['Error']['Code'] == "404":
            print("The object does not exist.")
        raise
    print("Deleted source file.")


def init():
    print("Initializing ...")
    if not os.path.exists(AWS_LAMBDA_WORKING_DIR):
        os.makedirs(AWS_LAMBDA_WORKING_DIR)
    if os.path.exists(AWS_LAMBDA_GUARD_FILE):
        print("Reusing container ...")
    else:
        open(AWS_LAMBDA_GUARD_FILE, 'a').close()
        print("New container ...")
    print("Initialized.")


def cleanup():
    print("Cleaning up '/tmp' ...")
    if os .path.exists(AWS_LAMBDA_WORKING_DIR):
        execute_command(['ls', '-alh', '/tmp'])  # ??
        execute_command(['rm', '-rf', AWS_LAMBDA_WORKING_DIR])
        execute_command(['ls', '-alh', '/tmp'])  # ??
    print("Cleaned up '/tmp'.")


def patch_executables(context):
    print("Patching executable files ...")
    avconv = os.path.join(AWS_LAMBDA_WORKING_DIR, context.aws_request_id + '-avconv')
    execute_command(['cp', '/var/task/avconv', avconv])
    execute_command(['chmod', '755', avconv])
    ffmpeg = os.path.join(AWS_LAMBDA_WORKING_DIR, context.aws_request_id + '-ffmpeg')
    execute_command(['cp', '/var/task/ffmpeg', ffmpeg])
    execute_command(['chmod', '755', ffmpeg])
    os.environ['LD_LIBRARY_PATH'] = AWS_LAMBDA_WORKING_DIR
    libmp3lame = os.path.join(AWS_LAMBDA_WORKING_DIR, 'libmp3lame.so.0.0.0')
    if not os.path.exists(libmp3lame):
        execute_command(['cp', '/var/task/libmp3lame.so.0.0.0', AWS_LAMBDA_WORKING_DIR])
        for link_libmp3lame in [os.path.join(AWS_LAMBDA_WORKING_DIR, 'libmp3lame.so'),
                                os.path.join(AWS_LAMBDA_WORKING_DIR, 'libmp3lame.so.0')]:
            if os.path.exists(link_libmp3lame):
                os.remove(link_libmp3lame)
            execute_command(['ln', '-s', libmp3lame, link_libmp3lame])

    result = ffmpeg, ffmpeg  # always use ffmpeg for now ...
    # result = avconv, ffmpeg
    print("Patched executable files '{0}'".format(', '.join(str(exe) for exe in result)))
    return result


def convert_time_to_msecs(time_text):
    # 00:00:02.97
    time_parts = time_text.split(':')
    hour = int(time_parts[0]) * 60 * 60 * 1000
    minute = int(time_parts[1]) * 60 * 1000
    seconds = time_parts[2].split('.')
    second = int(seconds[0]) * 1000
    msecond = int(seconds[1])
    result = hour + minute + second + msecond
    return str(result)


def convert_audio_file(avconv_file, ffmpeg_file, input_file, metadata):
    print("Converting audio file '{0}' with {1} ...".format(input_file, ffmpeg_file))
    file_name, _ = os.path.splitext(input_file)
    result = file_name + '-zopa'
    start = metadata[AWS_METADATA_AUDIO_START]
    end = metadata[AWS_METADATA_AUDIO_END]
    duration = float(end) - float(start)
    if os.path.exists(result):
        os.remove(result)
    returncode, _, _ = execute_command([avconv_file,
                                        '-y',
                                        '-ss',
                                        start,
                                        '-t',
                                        '{}'.format(duration),
                                        '-i',
                                        input_file,
                                        result + '.wav'])
    if returncode != 0:
        raise RuntimeError("Unable to complete avconv call.")
    # returncode, _, _ = execute_command([ffmpeg_file,
    #                                     '-y',
    #                                     # '-ss',
    #                                     # start,
    #                                     # '-t',
    #                                     # '{}'.format(duration),
    #                                     '-i',
    #                                     result + '.wav',
    #                                     '-filter:a',
    #                                     'loudnorm',
    #                                     result + '-norm.wav'])
    # if returncode != 0:
    #     raise RuntimeError("Unable to complete ffmpeg call.")
    returncode, _, _ = execute_command([avconv_file,
                                        '-y',
                                        # '-ss',
                                        # start,
                                        # '-t',
                                        # '{}'.format(duration),
                                        '-i',
                                        # result + '-norm.wav',
                                        result + '.wav',
                                        result + '.mp3'])
    if returncode != 0:
        raise RuntimeError("Unable to complete avconv call after normalization.")
    result = result + '.mp3'
    print("Converted audio file '{0}' into '{1}'.".format(input_file, result))
    return result


def extract_duration(stdout, stderr):
    def extract_duration0(text):
        duration = ''
        for line in iter(text.splitlines()):
            if 'Duration' in line:
                line_parts = list(filter(None, line.split(',')))
                if line_parts:
                    duration_parts = list(filter(None, line_parts[0].split(' ')))
                    if len(duration_parts) > 1:
                        duration = duration_parts[1].strip(' ')
                        break
        return duration
    result = extract_duration0(stdout)
    if not result:
        result = extract_duration0(stderr)
    print('Duration extracted is: {0}'.format(result))
    return result


def calculate_pan(pan):
    pan = max(-1.0, pan)
    pan = min(1.0, pan)
    x = (pan + 1.0) / 2
    gain_l = math.cos(x * math.pi / 2)
    gain_r = math.sin(x * math.pi / 2)
    return gain_l, gain_r


def convert_audio_files(s3,
                        metadata,
                        avconv_file,
                        bucket,
                        input_files,
                        track_keys,
                        existing_crap=None):
    # avconv -i 1.mp3 -i 2.mp3 -filter_complex
    # "[0:a]atrim=0:10[a0]; [1:a]atrim=0:29[a1]; [a0][a1]amix=inputs=2"
    # -c:a libmp3lame -q:a 4 output.mp3
    print("Converting '{0}' audio files ...".format(len(input_files)))
    command = list()
    command.append(avconv_file)
    for input_file in input_files:
        command.append('-i')
        command.append('{}'.format(input_file))
    command.append('-filter_complex')
    trims = ''
    mixes = ''
    volumes = ''
    pans = ''
    new_metadata = None
    durations = list()
    for i, track_key in enumerate(track_keys):
        if existing_crap is not None and track_key in existing_crap:
            key = track_key
        else:
            key = '{0}{1}'.format(track_key, AWS_MULTRACK_FILE_EXT.format(i))
        if existing_crap is not None and track_key in existing_crap:
            start = metadata['existing-audio-start']
            end = metadata['existing-audio-end']
            volume = metadata['existing-audio-volume']
            pan = metadata['existing-audio-pan']
        else:
            print('Fetching head object of {0} ...'.format(key))
            ho_response = s3.head_object(Bucket=bucket, Key=key)
            print(ho_response)
            start = ho_response['Metadata']['audio-start']
            end = ho_response['Metadata']['audio-end']
            volume = ho_response['Metadata']['audio-volume']
            pan = ho_response['Metadata']['audio-pan']
        durations.append(int((float(end) - float(start)) * 1000.0))
        trims += '[{0}:a]atrim={1}:{2}[a{0}]; '.format(i, start, end)
        volumes += '[a{0}]volume=volume={1}[a{0}]; '.format(i, float(volume))
        gain_l, gain_r = calculate_pan(float(pan))
        pans += '[a{0}]pan=stereo| c0={1}*c0| c1={2}*c1[a{0}]; '.format(i, gain_l, gain_r)
        mixes += '[a{0}]'.format(i)
        # if new_metadata is None:
        #     new_metadata = ho_response['Metadata']
    command.append('{0}{1}{2}{3}amix=inputs={4}'.format(trims,
                                                        volumes,
                                                        pans,
                                                        mixes,
                                                        len(input_files)))
    command.append('-c:a')
    command.append('libmp3lame')
    command.append('-q:a')
    command.append('4')
    file_name, _ = os.path.splitext(input_files[0])
    result = file_name + '-zopa'
    command.append(result + '.mp3')
    if os.path.exists(result):
        os.remove(result)
    returncode, _, _ = execute_command(command)
    if returncode != 0:
        raise RuntimeError("Unable to complete avconv call.")
    result = result + '.mp3'
    # duration = extract_duration(stdout, stderr)
    # metadata['duration'] = convert_time_to_msecs(duration)
    if durations:
        metadata['duration'] = str(max(durations))
    print("Converted audio files into '{0}'.".format(result))
    return new_metadata, result


def convert_image_file(input_file, size):
    print("Converting image file '{0}' ...".format(input_file))
    file_name, _ = os.path.splitext(input_file)
    result = file_name + ('-thumbnail' if size < 256 else '') + '-zopa.jpg'
    returncode, _, _ = execute_command(['convert',
                                        input_file,
                                        '-resize',
                                        '{}'.format(size),
                                        '-background',
                                        'white',
                                        '-flatten',
                                        result])
    if returncode != 0:
        raise RuntimeError("Unable to complete avconv call.")
    print("Converted image file '{0}' into '{1}'.".format(input_file, result))
    return result


def sign(key, msg):
    return hmac.new(key, msg.encode("utf-8"), hashlib.sha256).digest()


def get_signature_key(key, date_stamp, region_name, service_name):
    signed_date = sign(('AWS4' + key).encode('utf-8'), date_stamp)
    signed_region = sign(signed_date, region_name)
    signed_service = sign(signed_region, service_name)
    result = sign(signed_service, 'aws4_request')
    return result


def send_response(payload, metadata, object_type, bucket):
    print("Sending payload with bucket {} ...", bucket)
    region = 'us-east-1'
    service = 'service'
    method = 'post'
    endpoint_host = metadata[AWS_METADATA_ENDPOINT_HOST]
    if object_type == AWS_ENTITY_TYPE_LXX:
        endpoint = AWS_LXX_ENDPOINT.format(domain=endpoint_host,
                                           user_id=metadata[AWS_METADATA_USER_ID])
        try:
            LXX_id = metadata[AWS_METADATA_LXX_ID]
            endpoint = AWS_LXX_VERSION_ENDPOINT.format(domain=endpoint_host, LXX_id=LXX_id)
        except KeyError:
            pass
    elif object_type == AWS_ENTITY_TYPE_IMAGE:
        endpoint = AWS_AVATAR_ENDPOINT.format(domain=endpoint_host,
                                              user_id=metadata[AWS_METADATA_USER_ID])
        method = 'put'
    elif object_type == AWS_ENTITY_TYPE_JXX:
        endpoint = AWS_JXX_ENDPOINT.format(domain=endpoint_host,
                                           user_id=metadata[AWS_METADATA_USER_ID])
    elif object_type == AWS_ENTITY_TYPE_JXX_AS_LXX:
        endpoint = AWS_JXX_AS_LXX_ENDPOINT.format(domain=endpoint_host,
                                                  user_id=metadata[AWS_METADATA_USER_ID])
    else:
        endpoint = ''
    content_type = 'application/json'
    host = ''
    t = datetime.datetime.utcnow()
    amz_date = t.strftime('%Y%m%dT%H%M%SZ')
    date_stamp = t.strftime('%Y%m%d')  # date w/o time, used in credential scope
    canonical_uri = '/'
    canonical_querystring = ''
    canonical_headers = 'content-type:' + content_type + '\n' +\
                        'host:' + host + '\n' + 'x-amz-date:' + amz_date + '\n'
    signed_headers = 'content-type;host;x-amz-date;x-amz-target'
    payload_hash = hashlib.sha256(payload.encode('utf-8')).hexdigest()
    canonical_request = method + '\n' +\
        canonical_uri + '\n' +\
        canonical_querystring + '\n' +\
        canonical_headers + '\n' +\
        signed_headers + '\n' +\
        payload_hash
    algorithm = 'AWS4-HMAC-SHA256'
    credential_scope = date_stamp + '/' + region + '/' + service + '/' + 'aws4_request'
    string_to_sign = algorithm + '\n' +\
        amz_date + '\n' +\
        credential_scope + '\n' +\
        hashlib.sha256(canonical_request.encode('utf-8')).hexdigest()
    signing_key = get_signature_key(AWS_SECRET_ACCESS_KEY, date_stamp, region, service)
    signature = hmac.new(signing_key, string_to_sign.encode('utf-8'), hashlib.sha256).hexdigest()
    authorization_header = algorithm + ' ' +\
        'Credential=' + AWS_ACCESS_KEY + '/' + credential_scope + ', ' +\
        'SignedHeaders=' + signed_headers + ', ' +\
        'Signature=' + signature
    headers = {'Content-Type': content_type,
               'X-Amz-Date': amz_date,
               'Authorization': authorization_header}
    result = requests.post(endpoint, data=payload, headers=headers)
    print("Sent payload to '{0}'.".format(endpoint))
    return result


def build_LXX_payload(bucket, key, gif_static_key, gif_primary_key, gif_preview_key, metadata):
    # pylint: disable=too-many-arguments
    result = AWS_LXX_PAYLOAD.format(status='OK',
                                    bucket=bucket,
                                    key='{0}'.format(key),
                                    gif_static_key=gif_static_key,
                                    gif_primary_key=gif_primary_key,
                                    gif_preview_key=gif_preview_key,
                                    metadata=metadata)
    result = result.replace('\'', '"')
    return result


def build_avatar_payload(bucket, avatar_key, thumbnail_key, metadata):
    result = AWS_AVATAR_PAYLOAD.format(status='OK',
                                       bucket=bucket,
                                       avatar_key='{0}'.format(avatar_key),
                                       thumbnail_key='{0}'.format(thumbnail_key),
                                       metadata=metadata)
    result = result.replace('\'', '"')
    return result


def build_JXX_payload(bucket, key, metadata):
    result = AWS_JXX_PAYLOAD.format(status='OK',
                                    bucket=bucket,
                                    key='{0}'.format(key),
                                    metadata=metadata)
    result = result.replace('\'', '"')
    return result


def build_JXX_as_LXX_payload(bucket, key, metadata):
    result = AWS_JXX_AS_LXX_PAYLOAD.format(status='OK',
                                           bucket=bucket,
                                           key='{0}'.format(key),
                                           metadata=metadata)
    result = result.replace('\'', '"')
    return result


def processing_LXX(s3, event, context, metadata, bucket, object_type, input_file):
    print("Start converting audio file ...")
    result = ''
    avconv_file, ffmpeg_file = patch_executables(context)
    if avconv_file is not None and ffmpeg_file is not None:
        existing = False
        existing_crap = list()
        try:
            existing = metadata[AWS_EXISTING_ENTITY_TYPE] is not None
        except KeyError:
            pass
        multitracks = False
        try:
            multitracks = metadata[AWS_MULTRACK_STATUS] == 'true'
        except KeyError:
            pass
        if multitracks:
            print("Multitrack mode detected ...")
            track_keys = metadata[AWS_MULTRACK_KEYS].split(',')
            if existing:
                track_keys.append(metadata[AWS_EXISTING_AUDIO_KEY])
                existing_crap.append(metadata[AWS_EXISTING_AUDIO_KEY])
            track_keys = list(filter(None, track_keys))
            print(track_keys)
            input_files = download_files(s3, bucket, track_keys, existing_crap)
            _, output_file = convert_audio_files(s3,
                                                 metadata,
                                                 avconv_file,
                                                 bucket,
                                                 input_files,
                                                 track_keys,
                                                 existing_crap)
            # metadata = copy.deepcopy(new_metadata)
        else:
            output_file = convert_audio_file(avconv_file, ffmpeg_file, input_file, metadata)
        if os.path.exists(output_file):
            new_key = upload_file(s3,
                                  event,
                                  metadata,
                                  output_file,
                                  'audio/mp3',
                                  False)
            gif_static_key, gif_primary_key, gif_preview_key = process_gif(s3,
                                                                           event,
                                                                           bucket,
                                                                           metadata)
            payload = build_LXX_payload(bucket,
                                         new_key,
                                         gif_static_key,
                                         gif_primary_key,
                                         gif_preview_key,
                                         metadata)
            wait_for_object(s3, bucket, new_key)
            post_result = send_response(payload, metadata, object_type, bucket)
            result = AWS_LAMBDA_STATUS.format(payload=payload,
                                              code=post_result.status_code,
                                              text=post_result.text)
            print("Completed converting audio file, URL is '{0}'.".format(result))
    return result


def process_gif(s3, event, bucket, metadata):
    gif_static_key = ''
    gif_primary_key = ''
    gif_preview_key = ''
    try:
        if 'image' in metadata and 'image-gif' in metadata and 'image-preview' in metadata:
            gif_static_image_file = download_resource(metadata['image'], 'image')
            gif_primary_image_file = download_resource(metadata['image-gif'], 'image_gif')
            gif_preview_image_file = download_resource(metadata['image-preview'], 'image_preview')
            gif_static_key = upload_file(s3,
                                         event,
                                         metadata,
                                         gif_static_image_file,
                                         'image/gif',
                                         True)
            gif_primary_key = upload_file(s3,
                                          event,
                                          metadata,
                                          gif_primary_image_file,
                                          'video/mp4',
                                          False)
            gif_preview_key = upload_file(s3,
                                          event,
                                          metadata,
                                          gif_preview_image_file,
                                          'image/gif',
                                          False)
            host = 'https://s3.amazonaws.com/{0}/'.format(bucket)
            print("Static GIF: {0}".format(gif_static_key))
            metadata['image'] = host + gif_static_key
            print("Image GIF: {0}".format(gif_primary_key))
            metadata['image-gif'] = host + gif_primary_key
            print("Preview GIF: {0}".format(gif_preview_key))
            metadata['image-preview'] = host + gif_preview_key
    except Exception as ex:
        print("Failed to process gif, {0}".format(ex))
    return gif_static_key, gif_primary_key, gif_preview_key


def processing_image(s3, event, metadata, bucket, object_type, input_file):
    # pylint: disable=too-many-arguments
    print("Start converting image file ...")
    result = ''
    avatar_output_file = convert_image_file(input_file, 256)
    thumbnail_output_file = convert_image_file(input_file, 64)
    if os.path.exists(avatar_output_file) and \
            os.path.exists(thumbnail_output_file):
        avatar_key = upload_file(s3,
                                 event,
                                 metadata,
                                 avatar_output_file,
                                 'image/jpeg',
                                 True, )
        thumbnail_key = upload_file(s3,
                                    event,
                                    metadata,
                                    thumbnail_output_file,
                                    'image/jpeg',
                                    True,
                                    'thumbnail')
        payload = build_avatar_payload(bucket, avatar_key, thumbnail_key, metadata)
        post_result = send_response(payload, metadata, object_type, bucket)
        result = AWS_LAMBDA_STATUS.format(payload=payload,
                                          code=post_result.status_code,
                                          text=post_result.text)
    print("Completed converting image file, URL is {0}.".format(result))
    return result


def processing_JXX(s3, event, context, metadata, bucket, object_type, input_file):
    print("Start converting JXX file ...")
    result = ''
    avconv_file, ffmpeg_file = patch_executables(context)
    if avconv_file is not None:
        multitracks = False
        try:
            multitracks = metadata[AWS_MULTRACK_STATUS] == 'true'
        except KeyError:
            pass
        if multitracks:
            print("Multitrack mode detected ...")
            track_keys = metadata[AWS_MULTRACK_KEYS].split(',')
            input_files = download_files(s3, bucket, track_keys)
            # new_metadata, output_file = convert_audio_files(s3,
            _, output_file = convert_audio_files(s3,
                                                 metadata,
                                                 avconv_file,
                                                 bucket,
                                                 input_files,
                                                 track_keys)
            # metadata = copy.deepcopy(new_metadata)
        else:
            output_file = convert_audio_file(avconv_file, ffmpeg_file, input_file, metadata)
        if os.path.exists(output_file):
            new_key = upload_file(s3,
                                  event,
                                  metadata,
                                  output_file,
                                  'audio/mp3',
                                  False)
            payload = build_JXX_payload(bucket, new_key, metadata)
            wait_for_object(s3, bucket, new_key)
            post_result = send_response(payload, metadata, object_type, bucket)
            result = AWS_LAMBDA_STATUS.format(payload=payload,
                                              code=post_result.status_code,
                                              text=post_result.text)
    print("Completed converting JXX file, URL is {0}.".format(result))
    return result


def processing_JXX_as_LXX(s3, event, context, metadata, bucket, object_type, input_file):
    # pylint: disable=too-many-arguments
    print("Start saving JXX as LXX ...")
    result = ''
    avconv_file, ffmpeg_file = patch_executables(context)
    if avconv_file is not None:
        output_file = convert_audio_file(avconv_file, ffmpeg_file, input_file, metadata)
        if os.path.exists(output_file):
            new_key = upload_file(s3,
                                  event,
                                  metadata,
                                  output_file,
                                  'audio/mp3',
                                  False)
            payload = build_JXX_as_LXX_payload(bucket, new_key, metadata)
            wait_for_object(s3, bucket, new_key)
            post_result = send_response(payload, metadata, object_type, bucket)
            result = AWS_LAMBDA_STATUS.format(payload=payload,
                                              code=post_result.status_code,
                                              text=post_result.text)
    print("Completed saving JXX as LXX, URL is '{0}'.".format(result))
    return result


def entry_point(event, context):
    # pylint: disable=too-many-arguments
    # pylint: disable=too-many-locals
    # pylint: disable=broad-except
    # pylint: disable=too-many-nested-blocks
    result = ''
    print("\n\n----------------------------------")
    print("Start converting file ...")
    print("Event:")
    print(event)
    bucket, key = get_bucket_key(event)
    print("Bucket '{0}'".format(bucket))
    print("Key    '{}'".format(key))
    try:
        cleanup()
        init()
        s3 = get_s3_client()
        wait_for_object(s3, bucket, key)
        metadata = get_object_metadata(s3, event)
        if get_status(metadata) != AWS_METADATA_STATUS_COMPLETED:
            input_file = download_file(s3, event, metadata)
            if os.path.exists(input_file):
                object_type = get_object_type(metadata)
                if object_type == AWS_ENTITY_TYPE_LXX:
                    result = processing_LXX(s3,
                                             event,
                                             context,
                                             metadata,
                                             bucket,
                                             object_type,
                                             input_file)
                elif object_type == AWS_ENTITY_TYPE_IMAGE:
                    result = processing_image(s3,
                                              event,
                                              metadata,
                                              bucket,
                                              object_type,
                                              input_file)
                elif object_type == AWS_ENTITY_TYPE_JXX:
                    result = processing_JXX(s3,
                                            event,
                                            context,
                                            metadata,
                                            bucket,
                                            object_type,
                                            input_file)
                elif object_type == AWS_ENTITY_TYPE_JXX_AS_LXX:
                    result = processing_JXX_as_LXX(s3,
                                                    event,
                                                    context,
                                                    metadata,
                                                    bucket,
                                                    object_type,
                                                    input_file)
                else:
                    raise RuntimeError("Unknown entity type.")
        delete_file(event, metadata)
    except Exception as ex:
        print("Completed converting file, with errors.\n'{0}'.".format(ex))
        result = '{{"status":"ERROR"}}'
    finally:
        cleanup()
    print("Completed converting file.")
    print("----------------------------------\n\n")
    return result

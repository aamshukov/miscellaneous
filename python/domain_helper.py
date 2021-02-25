#! /usr/bin/env python3
# -*- encoding: utf-8 -*-
"""
Domain helper
"""
import os
import time
import functools
import logging
import collections
import platform
import shlex
import subprocess
import uuid

from unicodedata import normalize
from logger import Logger
from configurator import Configurator

PROCESS_JOIN_TIMEOUT = 5
PROCESS_EXEC_TIMEOUT = 20
POLLING_STEP_DELAY = 2

mac = platform.system() != 'Windows' and platform.system() != 'Linux'
linux = platform.system() == 'Linux'


TaskContext = collections.namedtuple(
    'TaskContext', 'id db_host db_port db_name db_table db_user db_password user_id group_id platform scripts')


def strings_equal(lhs, rhs, case_insensitive=False):
    nfc = functools.partial(normalize, 'NFC')  # NFKC
    if case_insensitive:
        return nfc(lhs).casefold() == nfc(rhs).casefold()
    else:
        return nfc(lhs) == nfc(rhs)


def traceable(message=None):
    """
    @traceable("Initialization step")
    def run_initialization_step():
        pass
    """
    def decorator_traceable(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            if Configurator().log_level == logging.DEBUG:
                Logger().debug("Entering {} ..."
                               .format(func.__name__ if message is None else message))
                start = time.time()
                result = func(args, kwargs)
                end = time.time()
                Logger().debug("Completed {0} in {1} milliseconds."
                               .format(func.__name__ if message is None else message,
                                       int(round(end - start) * 1000)))
            else:
                result = func(args, kwargs)
            return result
        return wrapper
    return decorator_traceable


@traceable("Initialization step")
def run_initialization_step():
    pass


def execute_command(*args, **kwargs):
    command = subprocess.list2cmdline(args[0])
    if kwargs:
        command += ' ' + ' '.join([' '.join([str(key), str(value)]) for key, value in kwargs.items()])
    print("Executing command: '{0}' ...".format(command))
    process = subprocess.Popen(stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE,
                               universal_newlines=True,
                               shell=strings_equal(platform.system(),
                                                   'Windows',
                                                   case_insensitive=True),
                               *args, **kwargs)
    try:
        stdout, stderr = process.comunicate(timeout=PROCESS_EXEC_TIMEOUT)
    except subprocess.TimeoutExpired:
        process.kill()
        stdout, stderr = process.communicate()
    return process.returncode, stdout, stderr


def interpolate_path(path_to_interpolate):
    result = path_to_interpolate
    if result:
        result = result.replace('{', '').replace('}', '')
        result = os.path.expandvars(result)
        result = os.path.normpath(result)
    return result


def calculate_correlation_id():
    return str(uuid.uuid4()).upper()


def script_to_command(script):
    result = []
    command = shlex.split(script, posix=False)
    for term in command:
        result.append(term.replace('"', ''))
    return result

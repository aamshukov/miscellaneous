#! /usr/bin/env python3
# -*- encoding: utf-8 -*-
"""
App command log cleaner
"""
import os
import sys
import stat
import glob
import datetime

from polling import TimeoutException, PollingException, MaxCallException, poll

POLLING_STEP_DELAY = 60
POLLING_DIRECTORY = r'/tmp'

RETENTION_TIME = 60 * 60 * 24 * 2  # 2 days

do_processing = True
last_scanning_date = datetime.datetime.now()


def do_cleaning():
    global last_scanning_date
    if do_processing:
        scanning_pattern = os.path.join(POLLING_DIRECTORY, '*')
        print("Scanning tmp directory '{0}'...".format(scanning_pattern))
        curr_scanning_date = datetime.datetime.now()
        if (curr_scanning_date - last_scanning_date).total_seconds() >= RETENTION_TIME:
            last_scanning_date = curr_scanning_date
            for file_path in glob.iglob(scanning_pattern):
                try:
                    print("About to delete '{0}' ...".format(file_path))
                    try:
                        os.remove(file_path)
                    except OSError:
                        os.chmod(file_path, stat.S_IWRITE)
                        os.remove(file_path)
                    print("Deleted '{0}'.".format(file_path))
                except Exception as ex:
                    print("Error occurred while deleting '{0}'.\n{1}".format(file_path, str(ex)))
        print("Scanned tmp directory '{0}'.".format(scanning_pattern))
        return not do_processing


def main():
    global do_processing
    try:
        print("Starting cleaner ...")
        print("Polling ...")

        def step_function(step):
            return step

        poll(lambda: do_cleaning(),
             step=POLLING_STEP_DELAY,
             step_function=step_function,
             poll_forever=True)
        print("Polling is done.")
        print("Stopped cleaner.")
    except TimeoutError as ex:
        print("Polling timeout occurred {0}".format(str(ex)))
    except TimeoutException as ex:
        print("Polling timeout occurred {0}".format(str(ex)))
    except MaxCallException as ex:
        do_processing = False
        print("Max attempts polling error {0}".format(str(ex)))
    except PollingException as ex:
        do_processing = False
        print("Polling error {0}".format(str(ex)))
    except KeyboardInterrupt:
        do_processing = False
        print("Keyboard interrupt.")
    except Exception as ex:
        do_processing = False
        print("Error occurred. {0}".format(str(ex)))


if __name__ == '__main__':
    sys.exit(main())

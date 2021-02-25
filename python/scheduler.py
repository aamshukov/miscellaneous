#! /usr/bin/env python3
# -*- encoding: utf-8 -*-
"""
App commands scheduler
"""
import os
import concurrent.futures

from polling import TimeoutException, PollingException, MaxCallException, poll

import pymysql.cursors

from domain_helper import (PROCESS_JOIN_TIMEOUT,
                           PROCESS_EXEC_TIMEOUT,
                           POLLING_STEP_DELAY,
                           TaskContext,
                           execute_command,
                           script_to_command,
                           mac,
                           linux,
                           calculate_correlation_id)
from configurator import Configurator
from logger import Logger


def task(context):
    Logger().info("Running task {0} ...".format(context.id))
    k = len(context.scripts)
    Logger().info("Task {0}, executing {1} commands ...".format(context.id, len(context.scripts)))
    for script, return_code in context.scripts:
        result, stdout, stderr = execute_command(script_to_command(script))
        if result != return_code:
            break
        k -= 1
    Logger().info("Task {0}, executed {1} commands ...".format(context.id, len(context.scripts) - k))
    if k == 0:
        connection = None
        cursor = None
        try:
            Logger().info("Task {0}, updating AppCommands status ...".format(context.id))
            connection = pymysql.connect(user=context.db_user,
                                         passwd=context.db_password,
                                         db=context.db_name,
                                         host=context.db_host,
                                         port=context.db_port,
                                         charset='utf8',
                                         cursorclass=pymysql.cursors.Cursor)
            connection.autocommit = False
            cursor = connection.cursor()
            query = "UPDATE {0}.{1} SET Active = false WHERE UserId = {2} AND GroupId = '{3}' "\
                    .format(context.db_name, context.db_table, context.user_id, context.group_id)
            cursor.execute(query)
            connection.commit()
            Logger().info("Task {0}, updated AppCommands status.".format(context.id))
        except pymysql.Error as ex:
            Logger().exception("DBMS error. {}".format(str(ex)))
            if connection is not None:
                connection.rollback()
        except Exception as ex:
            Logger().exception("DBMS error. {}".format(str(ex)))
            if connection is not None:
                connection.rollback()
        finally:
            if cursor is not None:
                cursor.close()
            if connection is not None:
                connection.close()
    Logger().info("Completed task '{0}'.".format(context.id))
    return True


class Scheduler:
    def __init__(self,
                 concurrency=(os.cpu_count() or 1) + 1,
                 process_join_timeout=PROCESS_JOIN_TIMEOUT,
                 process_exec_timeout=PROCESS_EXEC_TIMEOUT,
                 polling_step_delay=POLLING_STEP_DELAY):
        self.pool = concurrent.futures.ThreadPoolExecutor(max_workers=concurrency) if mac or linux \
            else concurrent.futures.ProcessPoolExecutor(max_workers=concurrency)
        self.do_processing = True
        self.concurrency = concurrency
        self.process_join_timeout = process_join_timeout
        self.process_exec_timeout = process_exec_timeout
        self.polling_step_delay = polling_step_delay

    @property
    def processing(self):
        return self.do_processing

    @processing.setter
    def processing(self, value):
        self.do_processing = value

    @staticmethod
    def step_function(step):
        return step

    def start(self):
        Logger().info("Starting scheduler ...")
        try:
            Logger().info("Polling ...")
            poll(lambda:
                 self.scan_commands(Configurator().db_host,
                                    Configurator().db_port,
                                    Configurator().db_name,
                                    Configurator().db_table,
                                    Configurator().db_user,
                                    Configurator().db_password),
                 step=POLLING_STEP_DELAY,
                 step_function=Scheduler.step_function,
                 poll_forever=True)
            Logger().info("Polling is done.")
            self.shutdown()
        except TimeoutError as ex:
            Logger().exception("Polling timeout occurred. {}".format(str(ex)))
        except TimeoutException as ex:
            Logger().exception("Polling timeout occurred. {}".format(str(ex)))
        except MaxCallException as ex:
            Logger().exception("Max attempts polling error. {}".format(str(ex)))
        except PollingException as ex:
            Logger().exception("Polling error. {}".format(str(ex)))
        except KeyboardInterrupt:
            Logger().error("Keyboard interrupt.")

    def shutdown(self):
        Logger().info("Shutting down scheduler ...")
        self.do_processing = False
        # processes = self.pool._processes.items()
        self.pool.shutdown(wait=False)
        # self.cleanup_pool(processes)
        Logger().info("Shut down scheduler.")

    def cleanup_pool(self, processes):
        try:
            # processes = self.pool._processes.items()
            Logger().info("Stopping pool with {} processes ...".format(len(processes)))
            for pid, process in processes:
                if process.is_alive():
                    Logger().info("Waiting for process {} ...".format(pid))
                    process.join(timeout=self.process_join_timeout)
                    if process.is_alive():
                        Logger().info("Terminating process {} ...".format(pid))
                        process.terminate()
            Logger().info("Stopped pool.")
        except Exception as ex:
            Logger().exception("Stop pool processing has been interrupted. {}".format(str(ex)))

    def schedule_tasks(self, task_contexts):
        if self.do_processing:
            try:
                Logger().info("Scheduling tasks ...")
                futures = []
                for task_context in task_contexts:
                    if not self.do_processing:
                        break
                    try:
                        Logger().info("Submitting task {0} ...".format(task_context.id))
                        future = self.pool.submit(task, task_context)
                        futures.append(future)
                        Logger().info("Submitted task {0}.".format(task_context.id))
                    except TimeoutError:
                        Logger().error("Timeout occurred.")
                    except concurrent.futures.TimeoutError:
                        Logger().error("Timeout occurred.")
                    except KeyboardInterrupt:
                        Logger().error("Keyboard interrupt.")
                    except Exception as ex:
                        Logger().exception("Error occurred during submission task. {}".format(str(ex)))
                if not self.do_processing:
                    futures.clear()
                for future in futures:
                    if not self.do_processing:
                        break
                    try:
                        Logger().info("Awaiting result ...")
                        future.result(timeout=self.process_exec_timeout)
                        Logger().info("Awaited result.")
                    except TimeoutError:
                        Logger().error("Timeout occurred.")
                    except concurrent.futures.TimeoutError:
                        Logger().error("Futures timeout occurred.")
                    except KeyboardInterrupt:
                        Logger().error("Keyboard interrupt.")
                    except Exception as ex:
                        Logger().exception("Error occurred during submission task. {}".format(str(ex)))
                Logger().info("Scheduled tasks.")
            except Exception as ex:
                Logger().exception("Error occurred during scheduling tasks. {}".format(str(ex)))
                self.shutdown()

    def scan_commands(self, db_host, db_port, db_name, db_table, db_user, db_password):
        Logger().info("Scanning commands ...")
        connection = None
        cursor = None
        try:
            connection = pymysql.connect(host=db_host,
                                         port=db_port,
                                         db=db_name,
                                         user=db_user,
                                         passwd=db_password,
                                         charset='utf8',
                                         cursorclass=pymysql.cursors.Cursor)
            connection.autocommit = False
            cursor = connection.cursor()
            query = "SELECT UserId, Script, ReturnCode, GroupId, ExecutionOrder, Platform "\
                    "FROM {0}.{1} WHERE Active = true ORDER BY GroupId ASC, ExecutionOrder ASC"\
                .format(db_name, db_table)
            scripts = list()
            current_user_id = 0
            current_group_id = 0
            current_platform = 0
            cursor.execute(query)
            for (user_id, script, return_code, group_id, execution_order, platform) in cursor:
                if current_group_id != group_id:
                    if scripts:
                        context = TaskContext(calculate_correlation_id(),
                                              db_host,
                                              db_port,
                                              db_name,
                                              db_table,
                                              db_user,
                                              db_password,
                                              current_user_id,
                                              current_group_id,
                                              current_platform,
                                              scripts)
                        self.schedule_tasks([context])
                        scripts.clear()
                    current_user_id = user_id
                    current_group_id = group_id
                    current_platform = platform
                scripts.append((script, return_code))
            if scripts:
                context = TaskContext(calculate_correlation_id(),
                                      db_host,
                                      db_port,
                                      db_name,
                                      db_table,
                                      db_user,
                                      db_password,
                                      current_user_id,
                                      current_group_id,
                                      current_platform,
                                      scripts)
                self.schedule_tasks([context])
            connection.commit()
            Logger().info("Scanned commands.")
        except pymysql.Error as ex:
            Logger().exception("{}".format(str(ex)))
            if connection is not None:
                connection.rollback()
        except Exception as ex:
            Logger().exception("{}".format(str(ex)))
            if connection is not None:
                connection.rollback()
        finally:
            if cursor is not None:
                cursor.close()
            if connection is not None:
                connection.close()
        return not self.do_processing

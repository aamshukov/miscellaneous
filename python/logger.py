#! /usr/bin/env python3
# -*- encoding: utf-8 -*-
"""
Logger wrapper
"""
import os
import logging

from configurator import Configurator
from singleton import singleton


LOGGER_NAME = 'uilab'


@singleton
class Logger:
    """
    Logger
    """
    def __init__(self,
                 level=logging.INFO,
                 log_dir='.',
                 log_to_file=False):
        self.logger = logging.getLogger(LOGGER_NAME)
        self.logger.setLevel(level)
        formatter = logging\
            .Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
        console_handler = logging.StreamHandler()
        console_handler.setLevel(level)
        console_handler.setFormatter(formatter)
        self.logger.addHandler(console_handler)
        if log_to_file:
            file_handler = logging.FileHandler(os.path.join(log_dir, '{}.log'.format(LOGGER_NAME)))
            file_handler.setLevel(level)
            file_handler.setFormatter(formatter)
            self.logger.addHandler(file_handler)

    def debug(self, msg, *args, **kwargs):
        self.logger.debug(msg, *args, **kwargs)

    def info(self, msg, *args, **kwargs):
        self.logger.info(msg, *args, **kwargs)

    def warning(self, msg, *args, **kwargs):
        self.logger.warning(msg, *args, **kwargs)

    def error(self, msg, *args, **kwargs):
        self.logger.error(msg, *args, **kwargs)

    def exception(self, msg, *args, **kwargs):
        self.logger.exception(msg, *args, **kwargs)

    def critical(self, msg, *args, **kwargs):
        self.logger.critical(msg, *args, **kwargs)


def initialize_logging(log_to_file):
    if not os.path.exists(Configurator().log_dir):
        os.makedirs(Configurator().log_dir)
    Logger(Configurator().log_level, Configurator().log_dir, log_to_file)

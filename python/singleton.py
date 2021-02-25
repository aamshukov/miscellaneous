#! /usr/bin/env python3
# -*- encoding: utf-8 -*-
"""
Singleton design pattern
"""
def singleton(klass):
    """
    Singleton decorator
    """
    class Decorator(klass):
        # pylint: disable=too-few-public-methods
        def __init__(self, *args, **kwargs):
            if hasattr(klass, '__init__'):
                klass.__init__(self, *args, **kwargs)

        def __repr__(self):
            return klass.__name__ + ' - singleton'

        __str__ = __repr__

    Decorator.__name__ = klass.__name__

    class Instance:
        # pylint: disable=too-few-public-methods
        def __init__(self):
            self.instance = None

        def __repr__(self):
            return klass.__name__

        __str__ = __repr__

        def __call__(self, *args, **kwargs):
            if self.instance is None:
                self.instance = Decorator(*args, **kwargs)
            return self.instance

    return Instance()

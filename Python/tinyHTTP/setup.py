#!/usr/bin/env python
from setuptools import setup

VERSION = '0.1'

setup(name="tinyHTTP",
      version=VERSION,
      description="It's a toy http server written by Bruce",
      license="MIT",
      author="BruceChen",
      author_email="bofenqgqiye7@gmail.com",
      entry_points= {
            'console_script': []
      },
      install_requires=[
            'pystache',
      ]
)
from setuptools import setup, find_packages, Distribution
from codecs import open
from os import path
import sys

here = path.abspath(path.dirname(__file__))

with open(path.join(here, 'README.rst'), encoding='utf-8') as file:
    long_description = file.read()

class BinaryDistribution(Distribution):
    def has_ext_modules(foo):
        return True


data_info = {'dlr':['*.pyd', 'dlr_python.py', '*.dll', 'CharacterModel/*']}

setup(
    name = 'dlr',
    version = '1.2',
    description = 'Description',
    long_description = long_description,
    url = 'https://www.dynamsoft.com/label-recognition/overview/?utm_source=pypi',
    author = 'Dynamsoft',
    author_email = 'support@dynamsoft.com',
    license = 'https://www.dynamsoft.com/CustomerPortal/Portal/Triallicense.aspx?product=dlr&utm_source=pypi',
    classifiers = [  # Optional
        # How mature is this project? Common values are
        #   3 - Alpha
        #   4 - Beta
        #   5 - Production/Stable
        'Development Status :: 5 - Production/Stable',

        # Indicate who your project is intended for
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Libraries',

        # Pick your license as you wish
        'License :: Other/Proprietary License',

        # Specify the Python versions you support here. In particular, ensure
        # that you indicate whether you support Python 2, Python 3 or both.
        'Programming Language :: Python',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: C++',
        'Programming Language :: Python :: Implementation :: CPython',
        'Operating System :: Microsoft :: Windows :: Windows 10',
        'Operating System :: POSIX',
        'Operating System :: MacOS',
        'Topic :: Scientific/Engineering',
        'Topic :: Scientific/Engineering :: Image Recognition',
        'Topic :: Software Development',
    ],
    keywords = 'Label Recognition',
    packages = find_packages(exclude=['contrib', 'docs', 'tests']), 
    install_requires = [],
    package_data = data_info,
    distclass = BinaryDistribution,
    platforms=['Windows']
)
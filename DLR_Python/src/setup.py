from distutils.core import setup, Extension
import sys
import os
from distutils.command.install import  install
from distutils.sysconfig import get_python_lib

setup_path = os.path.dirname(os.path.realpath(__file__))

# Windows
dlr_lib_name = 'DynamsoftLabelRecognitionx64'
dlr_lib_dir = r'..\lib'
dlr_dll = r'..\bin'
dlr_include = r'..\include'

source_files = ['dlr.c']

module_dlr = Extension('dlr', sources=source_files, library_dirs=[dlr_lib_dir], libraries=[dlr_lib_name], include_dirs=[dlr_include])

setup(
    name = 'dlr',
    version = '1.2',
    description= 'Dynamsoft Label Recognition Python Extension',
    author = 'Dynamsoft',
    author_email = 'support@dynamsoft.com',
    url = 'https://www.dynamsoft.com/label-recognition/overview/?utm_source=pypi',
    license = 'https://www.dynamsoft.com/customer/license/trialLicense?product=dlr&utm_source=github',
    platforms=['Windows', 'Linux', 'macOS'],
    ext_modules=[module_dlr]
)
import os
import re
import sys
import sysconfig
import platform
import subprocess
from os import path
from distutils.version import LooseVersion
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import shutil


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the following extensions: " +
                ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            cmake_version = LooseVersion(re.search(r'version\s*([\d.]+)',
                                                   out.decode()).group(1))
            if cmake_version < '3.1.0':
                raise RuntimeError("CMake >= 3.1.0 is required on Windows")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):

        extdir = os.path.abspath(
            os.path.dirname(self.get_ext_fullpath(ext.name)))
        cmake_args = ["-DCMAKE_BUILD_TYPE=Release", "-DCMAKE_CXX_STANDARD=17", "-DPYTHON_EXECUTABLE=" + sys.executable]
        build_args = ["-j8"]

        if platform.system() == "Darwin":
            cmake_args += ["-DOPENSSL_ROOT_DIR=/usr/local/opt/openssl",
                           "-DOPENSSL_LIBRARIES=/usr/local/opt/openssl/lib"]

            os.environ['CXX'] = "/usr/local/opt/llvm/bin/clang++"
        else:
            build_args += ['--', '-j8']

        build_path_suffix = os.environ.get('build_dir')
        build_path = self.build_temp if not build_path_suffix else path.join(build_path_suffix, self.build_temp)
        if not os.path.exists(build_path):
            os.makedirs(build_path)

        subprocess.check_call(["cmake"] + cmake_args + [ext.sourcedir],
                              cwd=build_path
                              )

        subprocess.check_call(['cmake', '--build', ".", '--target', 'secyan_python'] + build_args,
                              cwd=build_path)
        copy_target_path = extdir if not os.environ.get('output_dir') else os.environ.get('output_dir')
        wrapper_path = path.join(build_path, 'src/python_wrapper')
        for file in os.listdir(wrapper_path):
            if file.endswith(".so"):
                file_path = path.join(wrapper_path, file)
                shutil.copy(file_path, copy_target_path)

        print()


setup(
    name='secyan_python',
    version='0.1',
    author='Qiwei Li',
    description='A hybrid Python/C++ test project',
    long_description='',
    # add extension module
    ext_modules=[CMakeExtension('secyan_python')],
    # add custom build_ext command
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False,
)

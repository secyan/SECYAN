import subprocess
import os
from os import path

env = {
    "DEBIAN_FRONTEND": "noninteractive"
}

install_dependencies = [
    "build-essential",
    "gcc",
    "g++",
    "gdb",
    "clang",
    "cmake",
    "rsync",
    "tar",
    "libssl-dev",
    "libgmp-dev",
    "libboost-all-dev",
    "ninja-build",
    "python3-dev",
    "git",
    "python3-setuptools",
]

curdir = os.getcwd()
pybind11_path = path.join(curdir, "pybind11")
pybind11_build_path = path.join(pybind11_path, "build")

# subprocess.check_output(["apt-get", "update"], env=env)
subprocess.check_call(["apt-get", "install", "-y"] + install_dependencies)
subprocess.check_call(
    ["git", "clone", "https://github.com/pybind/pybind11.git"])
subprocess.check_call(["mkdir", "build"], cwd=pybind11_path)
subprocess.check_call(["cmake", ".."], cwd=pybind11_build_path)
subprocess.check_call(["make", "install",  "-j8"], cwd=pybind11_build_path)


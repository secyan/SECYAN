# [Choice] Debian / Ubuntu version: debian-10, debian-9, ubuntu-20.04, ubuntu-18.04
ARG VARIANT=buster
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

# Install needed packages. Use a separate RUN statement to add your own dependencies.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install build-essential cmake cppcheck valgrind clang lldb llvm gdb \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

ENV TZ=Europe/Minsk
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
  && apt-get install -y ssh \
    build-essential \
    gcc \
    g++ \
    gdb \
    clang \
    cmake \
    rsync \
    tar \
    python \
  && apt-get clean

RUN useradd -m user \
  && yes password | passwd user

RUN apt install cmake
RUN apt install -y libssl-dev
RUN apt install -y libgmp-dev
RUN apt install -y libboost-all-dev

# [Optional] Uncomment this section to install additional OS packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

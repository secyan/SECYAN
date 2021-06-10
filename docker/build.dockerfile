FROM ubuntu:20.04
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
# Required for python binding
RUN apt install -y ninja-build
RUN apt install --no-install-recommends -y python3 python3-pip python3-dev
RUN apt install -y git
WORKDIR /usr/local/project
RUN git clone https://github.com/pybind/pybind11.git
WORKDIR /usr/local/project/pybind11
RUN mkdir build
WORKDIR /usr/local/project/pybind11/build
RUN cmake ..
RUN make install -j4
WORKDIR /usr/local/project


#CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test_clion"]
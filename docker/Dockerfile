FROM debian AS builder
ENV TZ=Europe/Minsk
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
  && apt-get install -y build-essential \
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
#RUN git clone https://github.com/pybind/pybind11.git
#WORKDIR /usr/local/project/pybind11
#RUN mkdir build
#WORKDIR /usr/local/project/pybind11/build
#RUN cmake ..
#RUN make install -j4
RUN apt install -y python3-pybind11

FROM builder
WORKDIR /usr/local/project/SECYAN
COPY . .
RUN python3 setup.py install
RUN python3 -c "import secyan_python"
EXPOSE 7766
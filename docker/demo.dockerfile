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
WORKDIR /usr/local/project

COPY . .
RUN mkdir Release
WORKDIR /usr/local/project/Release
RUN cmake .. -DCMAKE_BUILD_TYPE=Release
RUN make -j 8

WORKDIR /usr/local/project/Release/src/example
#CMD ["./secyandemo"]
FROM ubuntu:20.04
ENV TZ=Europe/Minsk
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get install -y python3
COPY setup-scripts/ubuntu.py ubuntu.py

RUN python3 ubuntu.py

WORKDIR /usr/local/project


#CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test_clion"]
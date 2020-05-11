# CLion remote docker environment (How to build docker container, run and stop it)
#
# Build and run:
#   docker build -t clion/remote-cpp-env:0.5 -f Dockerfile .
#   docker run -d --cap-add sys_ptrace -p127.0.0.1:2222:22 --name clion_remote_env clion/remote-cpp-env:0.5
#   ssh-keygen -f "$HOME/.ssh/known_hosts" -R "[localhost]:2222"
#
# stop:
#   docker stop clion_remote_env
#
# ssh credentials (test user):
#   user@password
#   ssh user@localhost -p2222

FROM ubuntu:20.04

RUN rm /bin/sh && ln -s /bin/bash /bin/sh

ENV LC_ALL C.UTF-8
ENV LANG C.UTF-8

RUN sed -i 's/ universe/ universe multiverse/' /etc/apt/sources.list
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

RUN apt update \
  && apt install -y -q ssh \
      build-essential \
      gcc \
      g++ \
      clang \
      gdb \
      curl \
      sudo \
      neovim \
      cmake \
      ninja-build \
      rsync \
      tar \
      python3 \
      python3-pip \
      python3-distutils \
      git                        \
      wget                       \
      qt5-default \
      pkg-config \
      && rm -rf /var/lib/apt/lists/* \
      && python3 -m pip install --upgrade pip \
      && python3 -m pip install virtualenv \
      && python3 -m pip install conan conan-package-tools \
  && apt clean

RUN ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
  ) > /etc/ssh/sshd_config_test_clion \
  && mkdir /run/sshd

RUN useradd -m user \
  && yes password | passwd user

RUN adduser user sudo

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test_clion"]
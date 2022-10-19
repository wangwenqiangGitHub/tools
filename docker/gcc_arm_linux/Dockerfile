FROM ubuntu:16.04

RUN apt-get update

RUN apt install g++-4.9-arm-linux-gnueabi gcc-4.9-arm-linux-gnueabi cmake make vim

# 创建用户
RUN useradd vimuser && \
    echo "ALL            ALL = (ALL) NOPASSWD: ALL" >> /etc/sudoers

WORKDIR /home/vimuser
ENV HOME /home/vimuser

RUN chown -R vimuser:vimuser $HOME
USER vimuser


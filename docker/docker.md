# Dockerfile

- 构建镜像的文本文件，
- 构建命令

```shell
docker build -f /path/Dockerfile
docker build -t <name> .
```

```Dockerfile
FROM ubuntu:latest
RUN apt-get update
RUN apt-get install -y nginx
```

- 基本命令
  - FROM 指定基础镜像，必须作为第一个命令
  - MAINTAINER 维护这信息
  - RUN 构建镜像时，需要执行的命令
  - ADD将本地文件添加到容器中,tar类型文件会自动解压，可以访问网络资源 wget
  - COPY 类似ADD，但是不能自动解压，也不能访问网络资源
  - ENTRYPOINT
  - CMD
  - EXPOSE 指定运行该镜像的容器使用的端口
  - ENV 设置环境变量
  - VOLUME 向容器中添加卷
  - WORKDIR 从镜像创建一个新容器时，在容器中设置工作目录(类似于cd)

# Docker Compose

- Compose是用于定义和运行多容器Docker应用程序的工具。

```yaml
version:'3'
services:
	web:
	  build: .
	  ports:
	  - "5000:5000"
```

- Compose命令构建运行

```shell
docker-compose up
```

- yaml配置指令
  - build:指定构建镜像上下文路径

# clion 与Dockerfile

- 通过Edit configuration添加Dockerfile文件，名字，文件
- 编译Dockerfile
- cmake配置docker的编译工具链，编译即可

```shell
```

# docker 删除命令

- docker image rm -f xxx
- 查看所有容器: docker ps -a
- 查看所有容器id: docker ps -a -q
- docker stop $(docker ps -a -q) //停止所有容器
- docker rm $(docker ps -a -q) //删除所有容器

# Dockerfile中配置docker ssh登录的密码

- RUN echo 'root:root'|chpasswd

# docker 报错:Cannot connect to the Docker daemon at tcp://localhost:2375. Is the docker daemon running?

```
export DOCKER_HOST='unix:///var/run/docker.sock'
```

# docker报错:Ubuntu 22.04 Error response from daemon: Get “https://registry-1.docker.io/v2/”: dial tcp: lookup registry-1.docker.io on 127.0.0.53:53: read udp 127.0.0.1:48086->127.0.0.53:53: read: connection refused

```
vim  /etc/resolv.conf
nameserver 8.8.8.8
nameserver 8.8.4.4
```

# docker path

```
vi /etc/systemd/system/docker.service.d/http-proxy.conf
```

<++>

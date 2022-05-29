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


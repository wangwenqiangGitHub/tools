# http服务

```shell
python -m SimpleHTTPServer 8000
```

# python 虚拟环境

```shell
brew update
brew upgrade
brew install python

python3 -m ensurepip --upgrade
python3 -m pip install --upgrade pip

python3 -m venv .venv
source .venv/bin/activate
# coc-pyright
create venv in project: python3 -m venv .venv
source .venv/bin/activate
install modules with pip and work with Pyright
deactivate
```

# 工程中需要的包

```shell
# 在conda环境中安装pipreqs
pip install pipreqs
pipreqs ./ --encoding = utf8
#安装环境所需要的依赖
pip install -r requirement.txt

# windows 
C:\
D:\
cd py_ws
pipreqs .\  
pip install -r requirement.txt
#使用代理会比较快
pip install -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple
```

# 便携式http server

```shell
python -m http.server  # 默认启动在 0.0.0.0:8000
python -m http.server 9000
python -m http.server --bind 127.0.0.1
python -m http.server --directory /tmp/
```

# python中的(){}[]

- ()元组数据类型，元组是一中不可变序列，创建方法简单，大多数时候可以用小括号括起来

```
tup=(1,2,3)
```

- []表示list列表，可变序列
- {}字典

```
dic={'json':'boy','lili':'girl'}
```

# ftp服务器

```shell
pip install pyftpdlib
# 开启
python -m pyftpdlib
# ftp://127.0.0.1:2121
# 参数 -i 指定ip -p 指定端口 -w 写权限 -d 指定目录 -u 指定用户登录 -P 设置登录密码
```

# python的Umi-OCR环境

- 环境

```
python.exe -m venv .env
# pycharm选择配置的虚拟环境
```

# Django

- http的get是从后台取数据; post是向后台提交数据

# python优秀开源项目

- shadowsocks:
  - 地址:https://github.com/shadowsocks/shadowsocks/tree/master
    解析:https://huiliu.github.io/2016/03/19/shadowsocks.html
    ![shadowsocks](./images/whats-shadowsocks-041.png)
  - PC是需要利用shadowsocks代理的应用;
  - SS Local为shadowsocks客户端,通常运行在PC/手机上(也可以运行在任务PC可以到达的位置)，用于与shadowsocks服务端建立连接。
  - GFW
  - ss server shadowsocks服务端，与ss local通讯，完成ss local请求的访问，并将返回数据加密返回给ss local

- 数据流向:
  - 图中1Request即本地应用通过sock5代理向ss local发起访问请求
  - 图中2Encrypt Request为ss local将PC的请求经加密交给ss server
  - ss server收到ss local的数据后解密，得到目的地址和数据，再向目的地址(google/Twitter/Facebook)发起请求即图中3Request
  - 目的服务器(Google/Twitter/Facebook)响应ss server的请求，即图4Response
  - ss server 收到响应数据后，将其加密发送给ss local,即图5 Encrypt Response
  - ss local收到ss server发回的经加密的响应数据后，解密交给请求发起方PC。即图6Response

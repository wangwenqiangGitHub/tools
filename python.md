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

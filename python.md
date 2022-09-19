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

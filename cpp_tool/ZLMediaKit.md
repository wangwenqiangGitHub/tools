# 编译
- 查看编译脚本，需要下载子工程
```
 git submodule update --init --recursive
```
# mac编译支持webrtc
```
# openssl配置
brew list openssl
echo 'export PATH="/opt/homebrew/Cellar/openssl@1.1/1.1.1q/bin:$PATH"' >> ~/.zshrc
echo 'export PATH="/opt/homebrew/Cellar/openssl@1.1/1.1.1q/include:$PATH"' >> ~/.zshrc
echo 'export PATH="/opt/homebrew/Cellar/openssl@1.1/1.1.1q/lib:$PATH"' >> ~/.zshrc
./configure --enable-openssl
source ~/.zshrc
pkg-config --libs openssl
pkg-config --list-all | grep open
ln -s /opt/homebrew/Cellar/openssl@1.1/1.1.1q/lib/pkgconfig/openssl.pc /opt/homebrew/lib/pkgconfig
./configure --enable-openssl
cd /opt/homebrew/Cellar/openssl@1.1/1.1.1q/lib
ln -s /opt/homebrew/Cellar/openssl@1.1/1.1.1q/lib/pkgconfig/libcrypto.pc /opt/homebrew/lib/pkgconfig
./configure --enable-openssl
# libsrtp
mkdir build && cd build && cmake - cmake -DENABLE_OPENSSL=1 .. && make && sudo make
# ZLMediaKit开启webrtc
cmake -DENABLE_WEBRTC=true ..
# 浏览器打开网页输入本机ip。默认端口是80
```

<++>
# 多线程与智能指针

# weak\_ptr和shared\_ptr


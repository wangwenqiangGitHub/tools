# zsh离线安装

- 编译zsh

```
#ubuntu1404
wget https://sourceforge.net/projects/zsh/files/zsh/5.0.2/zsh-5.0.2.tar.gz
tar zxvf zsh-5.0.z.tar.gz
cd zsh-5.0.2
./configure --prefix=`pwd`/OUT
make -j32 && make install
```

- oh-my-zsh

```
#将已经安装的oh-my-zsh的文件打包然后在拷贝到服务器中解压
```

- 无root权限启动zsh

```shell
exec ~/zsh-5.0.2/OUT/bin/zsh
```

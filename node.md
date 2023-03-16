# windows查看node安装的全局包的路径

```
npm bin -g
```

# windows pnpm安装及配置

```
npm install -g pnpm
pnpm config set store-dir "D:\.pnpm-store" # pnpm全局仓库路径(类似 .git 仓库)
pnpm config set global-dir "D:\nodejs\pnpm\pnpm-global" # pnpm全局安装路径
pnpm config set global-bin-dir "D:\nodejs" # pnpm全局bin路径
pnpm config set state-dir "D:\nodejs\pnpm" # pnpm创建pnpm-state.json文件的目录
pnpm config set cache-dir "D:\nodejs\pnpm\cache" # pnpm全局缓存路径
```

# node更新

- 首先官网下载node:https://nodejs.org/en/download/

```
VERSION=v18.11.0;；;
DISTRO=linux-x64
sudo mkdir -p /usr/local/lib/nodejs
sudo tar -xJvf node-$VERSION-$DISTRO.tar.xz -C /usr/local/lib/nodejs
#zsh
VERSION=v18.11.0
DISTRO=linux-x64
export PATH=/usr/local/lib/nodejs/node-$VERSION-$DISTRO/bin:$PATH
# 问题N/A version is not installed yet 解决方法就是zshrc中屏蔽
# export NVM_DIR="$HOME/.config/nvm"
# [ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
# [ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion
```

<++>

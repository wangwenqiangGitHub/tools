# 学习electron的理由

- 跨平台的桌面app，目前qq，钉钉，vscode等主流应用app已经开始采用electron
- 采用前端的先进技术应用到桌面app中

# 使用镜像

```shell
# electron配置国内的镜像
pnpm config set electron_mirror=https://registry.npmmirror.com/-/binary/electron/
# nrm 配置镜像
npm install -g nrm
nrm ls
nrm use tencent
```

# Electron 脚手架使用

- 安装

```shell
pnpm create @quick-start/electron
p add -D sass scss
```

# electron主要分为哪些知识

- electron 需要js node 等，主要涉及的概念就是主进程，渲染进程

## marks
- mj
- delmarls j
- 'j跳到标记为j的位置
- 删除所有标记delmarks!
- .最近编辑的位置
- 0-9最近使用的文件
- ^最近插入的位置
- '上一次跳转的位置

## [zsh终端不显示virtualenv相关信息](https://blog.csdn.net/Zero_S_Qiu/article/details/104217295)

## vim-plug插件回退版本
```shell
cd ~/.vim/bundles/markdown_preview.nvim ，git reset --hard e5bfe9
```

## tmux重要功能补充
- ctrl+b z 全屏/恢复面板窗口

## 查看vim的安装路径
```shell
type vim
# vim的自己编译安装的路径在/usr/local/bin/vim8
```
## 更新vim9
```
sudo add-apt-repository ppa:jonathonf/vim-daily
sudo apt update

```

# coc依赖nodejs
```
sudo npm install -g n
sudo n stable
#关于错误创建文件夹/usr/local/n 无权限问题。手动创建可以解决
```

# language server安装
```
npm i -g bash-language-server
```


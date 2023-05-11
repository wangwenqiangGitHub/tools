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

- tmux session
  - ctrl+b c-f 查找session
  - ctrl+b $ 重命名session
  - ctrl+b & kill session
  - ctrl+b ( session 切换
  - ctrl+b ) session 切换
  - ctrl+b c-c new session
  - tmux list-keys查看所有快捷键

- tmux window/pane
  - ctrl+b z 全屏/恢复面板窗口
  - ctrl+b x kill pane

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

# bear工具

- bear -- make -j4

# coc配置

```
# 查看coc的配置文件
:h g:coc_config_home
```

# vim 配置文本注释

```vimscript
function! <SID>snip_cpp()
	let l:filename = expand("%:t")
	let l:text = []
	let l:text += ['/**********************************************************************']
	let l:text += [' * @file' . ' ' . l:filename .'']
	let l:text += [' * @brief' . '']
	let l:text += [' * @author' . ' ' . 'wwq']
	let l:text += [' * @date' . ' ' . strftime("%Y/%m/%d")]
	let l:text += [' * copyright' . ' ' . 'Copyright (c) 2022 Gohigh V2X Division']
	let l:text += [' * Last Modified: ' . strftime('%Y/%m/%d %H:%M:%S') ]
	let l:text += ['**********************************************************************/']
	call append(0, l:text)
endfunc
noremap <space>ee :call <SID>snip_cpp()<cr>
```

# switch nvim

- switch to nvim: https://neovim.io/doc/user/nvim.html#nvim-from-vim

## vim 跳转出现问题，当有多个command\_json文件

# vim 自带命令编辑文件

```shell
:find *.cpp
: grep xxx -r dir/file
:copen
```

# vim中显示文件路径

```
1 ctrl+g
```

# vim command

- vim中快速获取当前文件的路径

```
`dirname %`
#或者采用
%:h
```

- QuickFix窗口

```shell
# 调出QuickFix窗口
:cw
#
:cn找每一个匹配的行，或者编译中的错误
:cp 前一个
```

# vimgrep

```
:vimgrep /main/gj **\*.c
```

# vim 快速移动技巧

```
The test a ...........  vim text
# 复制test 到vim之间的内容
/test回车，y/vim就可以选中
/test回车，d/vim就可以删除
/test回车，c/vim就可以改变
change命令很适合修改代码， cc表示删除本行并开始重写。删除本行同时执行insert模式
```

# wsl vim与windows共享系统剪切板

```shell
sudo apt install vim-gtk
```

- 讲paste.exe粘贴到定义的路径

```vimrc
set clipboard+=unnamed
vmap <leader>y :!/mnt/c/Windows/System32/clip.exe <cr>u
map <leader>p :read !/mnt/c/Windows/System32/paste.exe <cr>i<bs><esc>l
map! <leader>p <esc>:read !/mnt/c/Windows/System32/paste.exe <cr>i<bs><esc>l
```

# vim替换技巧

- 删除行尾1元素

```
s/.\{1\}$//
```

- 多行前添加字符

```
s/\(\w.*\)/data[10] = "\1";
```

# CTRL-R命令

- CTRL-Ra将粘贴a寄存器的内容

# 清空寄存器

- q寄存器q

# coc snippets配置

- coc的配置文件路径

```
~/.vim/coc-settings.json
```

- 配置自己的c.snippets需要设置coc-settings.json文件

```
"snippets.extends": {
	"cpp":["app"]
},
```

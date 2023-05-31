# 代码补全 suggest 默认快捷键修改为

alt-i

# 上次打开的文件

```
View: Quick Open Least Recently Used Editor
alt-e
```

# 切换面板可见性

```
#vscode中的默认配置 ctrl，如果采用默认配置需要vim.handleKeys取消掉
alt-j
alt-shift-j
alt-b
alt-shift-b
alt-m
```

```
#setting.json
"vim.handleKeys": {
    "<C-a>": false,
        "<C-f>": false,
        "<C-i>": true,
        "<C-o>": true,
        "<C-r>": true,
        "<C-s>": false,
        "<C-v>": true,
        "<C-w>": true,
        "<C-j>": false,
        "<C-b>": false
}
```

# c++源文件与头文件切换

alt-o

# vscode vim 插件代码折叠后 k j 按键会打开折叠

设置中搜索 vim.foldfix 开启即可

# 分屏相关快捷键

分屏 ctrl+\
关闭页面 ctrl+w 合并分屏 ctrl+alt+\
合并所有分屏 ctrl+shift+alt+\
三列编辑器布局 shift+alt+3 切换分屏 ctrl+1/2/3

# 文件操作插件

- Dyno File Utils

# vscode 解决 terminal 打开默认时 shell，需要手动切换为 bash 问题

- settings 中 Terminal\>Integrade\>Default Profile:linx 选择 bash

# vs 中快速打开 vsvimrc

```
:nnoremap <leader>v :e C:\Users\戴尔\_vsvimrc<CR>
```

# 前端一些 snippetes

- snippets 光标位置采用<tab>跳转
- command +i 触发补全 ctrl+space
- imd
- imp
- fn
- log
- vue
- anfn
- iife
- rp

## 配置 snippets

- 生成 snippets 的小程序

```
https://snippet-generator.app/
```

- tab 位置 默认值 多选 变量

## vscode 前端 emmet 语法配置

- setting.json 中添加配置

```
"emmet.triggerExpansionOnTab": true,
"emmet.includeLanguages": {
  "vue-html": "html",
  "vue": "html"
}
```

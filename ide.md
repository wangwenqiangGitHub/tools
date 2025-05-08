# eclipse

- 设备环境变量:1.D:\Program Files\msys\1.0\bin 2. D:\Program Files\java\jre1.8.0_241\bin

# eclipse快捷键

- alt+/ 自动补全
- <leader>v c-v块模式
- <leader>w c/c++搜索关键字，主要通过快捷键导出的excel表查看快捷键

# idear

- <leaderf>fa 可以运行所有命令
- <esc>可以实现从其他面板跳到编辑面板

# vsVimrc

- 依赖Visual Assist
- 离线安装

```
/绝对路径/VSIXInstaller.exe VsVim.vsix
```

# vs

- 右键 - a 设置启动项
- 右键 - x 打开文件目录
- 调试相关
  - 打开测试窗口：Alt + S
  - 运行所有测试：Ctrl + R，A
  - 重复上次运行：Ctrl + R，L
  - 调试所有测试：Ctrl + R，Ctrl + A
  - 调试上次运行：Ctrl + R，D
  - 附加到进程 ：Ctrl + Alt + P
  - 调试单步执行 ：F10
  - 开始调试 ：F5 　
  - 停止调试：Shift + F5 　　
  - 添加快捷匹配: Ctrl + Alt + Q
  - 设置或删除断点: F9
- 生成相关
  - 生成解决方案：Ctrl + Shift + B
  - 对解决方案运行代码进行分析：Alt + F11
  - 生成项目：Ctrl + B
  - 编译：Ctrl + F7

- vs中番茄助手插件安装后,取消自动更新,否则后边激活失效了

# source insight工具

- 需要创建project工程
- 根据函数可以选择jump to caller查看调用关系
- 菜单栏中 `p`表示 `project_windows`查看文件列表的 ，后一个查看上下文的

# vs打开工程文件使用Unicode(UTF-8)编码问题

- 检查控制面板-时钟和区域:Beta版: 使用Unicode UTF-8提供全球语言支持 这个选项不要勾选。

# vs必要设置

- `工具-选项-c/c++高级-主动提交成员列表(true)`

# vs中运行程序显示`msvsmon.exe`不可用

- 将`msvsmon.exe`这个程序替换一下路径`C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\Remote Debugger\x86`这个路径的值替换掉

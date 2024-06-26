# 当访问某个端口失败后,重启windows网络

```
net stop winnat
net start winnat
```

# windows文件夹区分文件命名大小写

```
#终端管理员权限
#设置文件名字大小写
fsutil.exe file setCaseSensitiveInfo <path> enable
# 关闭
fsutil.exe file setCaseSensitiveInfo <path> disable
```

# powershell 使用代理

```
$env:HTTP_PROXY="http://127.0.0.1:1080"
```

# windows程序编译

- msys2中安装编译

```
pacman -S mingw-w64-x86_64-toolchain make
pacman -S mingw-w64-x86_64-gnutls mingw-w64-x86_64-libgcrypt mingw-w64-x86_64-libtasn1
./configure --prefix=/usr/local --disable-static
make
make install
https://www.freecodecamp.org/news/how-to-install-c-and-cpp-compiler-on-windows/
pacman -S mingw-w64-x86_64-gcc
```

- vs中编译

# windows配置环境变量

```
#永久生效,重启一个命令行窗口
setx PATH "%PATH%;C:\your\new\path"
# 取消
setx PATH "%PATH:;D:\msys64\mingw64\bin=%"
# 当前窗口生效 cmd中生效powershell中貌似只能采用setx
set "PATH=D:\msys64\mingw64\bin;%PATH%"

# powershell中
$env:PATH += ";D:\msys64\mingw64\bin"
$env:PATH = $env:PATH -replace ";D:\\msys64\\mingw64\\bin", ""
# 查看powershell中的配置
$PROFILE 
nvim C:\Users\戴尔\Documents\WindowsPowerShell\Microsoft.PowerShell_profile.ps1 内容
. $env:USERPROFILE\.config\powershell\user_profile.ps1
New-Alias -Name v -Value nvim
function gccscriptBlock {
    $env:PATH += ";D:\msys64\mingw64\bin"
}
function gcccscriptBlock {
    $env:PATH = $env:PATH -replace ";D:\\msys64\\mingw64\\bin", ""
}
New-Alias -Name envgcc -Value gccscriptBlock
New-Alias -Name envgccc -Value  gcccscriptBlock
# yaml问题
删除 %LOCALAPPDATA%\nvim-data\lazy\nvim-treesitter\parser\yaml.so 文件
scoop install llvm
$env:CC="clang"
```

# SecureCRT安装

- 卸载:

```
在控制面板中不能卸载，需要手动删除注册表
win+r
regedit进入注册表
HKEY_CURRENT_USER保存的是当前用户配置
HKEY_LOCAL_MACHINA是当前计算机配置信息
删除VanDyke目录。
```

# Mobaxterm

- 支持串口, ftp, sftp, ssh 免费

# oh-my-posh

-

```
scoop install https://github.com/JanDeDobbeleer/oh-my-posh/releases/latest/download/oh-my-posh.json
$env:Path += ";C:\Users\user\AppData\Local\Programs\oh-my-posh\bin"
nvim $PROFILE
# 内容
oh-my-posh init pwsh --config "$env:POSH_THEMES_PATH\powerlevel10k_rainbow.omp.json" | Invoke-Expression
# AutoComplete 参考youtobe
Install-Module PSReadLine -Force
```

# windows批处理命令

```
Get-Process | findstr.exe E
```

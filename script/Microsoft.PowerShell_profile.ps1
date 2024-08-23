# 文件位置
#echo $PROFILE                                                                                                                     ─╯
# C:\Users\wangwenqiang01\Documents\WindowsPowerShell\Microsoft.PowerShell_profile.ps1
oh-my-posh init pwsh --config "$env:POSH_THEMES_PATH\powerlevel10k_rainbow.omp.json" | Invoke-Expression
Invoke-Expression (& { (lua C:\Scoop\apps\z.lua\1.8.18\z.lua --init powershell) -join "`n" })

function cdsf {cd C:\sf_ws}
function cdhm {cd ~}
set-alias vi nvim
function onc {control.exe /name Microsoft.NetworkAndSharingCenter }
# 开启vm windows中为了使用wsl2
function vmo {dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart}
# 关闭vm windows中为了使用vmware虚拟机
function vmc {dism.exe /online /disable-Feature  /featurename:VirtualMachinePlatform /all /norestart}
# 开启wsl子系统
function wslopen {dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart}
# wsl相关命令
# 将 WSL 2 设置为默认版本
# wsl --set-default-version 2
# 将某个wsl设置为2: wsl --set-verstion xxx 2
# 注销某个wsl wsl --unregister xxx
# 导入 wsl --import Ubuntu-22.04 X:\xxx\xxx\  X:\xxx\Ubuntu.img

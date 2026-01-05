@echo off
echo "Installing packages with Scoop..."

:: 更新 Scoop 仓库
scoop update -a

:: 安装 Git
scoop install git

:: 安装 Visual Studio Code
scoop install vscode

:: 安装 Python
scoop install python3.10

:: 安装 Node.js
scoop install nodejs

scoop install everything

scoop install ffmpeg

scoop install winscp

scoop install wireshark

scoop install cmake

scoop install obs-studio

scoop install clash-party

scoop install SumatraPDF

echo "All packages have been installed successfully."
pause


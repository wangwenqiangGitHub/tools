@echo off
:: ============================================
:: 修正版Qt打包脚本
:: 版本：2023-08-20
:: ============================================

:: 配置参数（请确认这些路径正确）
setlocal
set QT_BIN=C:\Qt\Qt5.12.12\5.12.12\mingw73_32\bin
set EXE_NAME=countcode.exe
set BUILD_DIR=C:\github_ws\QWidgetDemo\tool\binA
set OUTPUT_DIR=C:\github_ws\QWidgetDemo\tool\binOUT

:: 检查关键文件是否存在
if not exist "%QT_BIN%\windeployqt.exe" (
    echo [错误] 找不到windeployqt.exe
    echo 请检查QT路径: %QT_BIN%
    pause
    exit /b 1
)

if not exist "%BUILD_DIR%\%EXE_NAME%" (
    echo [错误] 找不到可执行文件
    echo 路径: %BUILD_DIR%\%EXE_NAME%
    pause
    exit /b 1
)

:: 清理并创建输出目录
echo 正在准备输出目录...
if exist "%OUTPUT_DIR%" (
    echo 正在删除旧文件...
    rmdir /s /q "%OUTPUT_DIR%"
    timeout /t 2 >nul
)
mkdir "%OUTPUT_DIR%"

:: 复制可执行文件
echo 正在复制可执行文件...
copy "%BUILD_DIR%\%EXE_NAME%" "%OUTPUT_DIR%\%EXE_NAME%"

:: 执行windeployqt（调试模式）
echo 正在执行windeployqt...
"%QT_BIN%\windeployqt.exe" --debug --no-compiler-runtime "%OUTPUT_DIR%\%EXE_NAME%"

:: 检查是否成功
if errorlevel 1 (
    echo [错误] windeployqt执行失败
    echo 返回代码: %errorlevel%
    pause
    exit /b %errorlevel%
)

:: 复制MinGW运行时
echo 正在复制运行时库...
copy "%QT_BIN%\libgcc_s_dw2-1.dll" "%OUTPUT_DIR%"
copy "%QT_BIN%\libstdc++-6.dll" "%OUTPUT_DIR%"
copy "%QT_BIN%\libwinpthread-1.dll" "%OUTPUT_DIR%"

:: 验证基本文件
echo 正在验证文件...
dir "%OUTPUT_DIR%"

:: 完成
echo.
echo ============================================
echo 打包成功！输出目录:
echo %OUTPUT_DIR%
echo ============================================
pause
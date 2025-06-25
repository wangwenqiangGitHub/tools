@echo off
:: ============================================
:: ������Qt����ű�
:: �汾��2023-08-20
:: ============================================

:: ���ò�������ȷ����Щ·����ȷ��
setlocal
set QT_BIN=C:\Qt\Qt5.12.12\5.12.12\mingw73_32\bin
set EXE_NAME=countcode.exe
set BUILD_DIR=C:\github_ws\QWidgetDemo\tool\binA
set OUTPUT_DIR=C:\github_ws\QWidgetDemo\tool\binOUT

:: ���ؼ��ļ��Ƿ����
if not exist "%QT_BIN%\windeployqt.exe" (
    echo [����] �Ҳ���windeployqt.exe
    echo ����QT·��: %QT_BIN%
    pause
    exit /b 1
)

if not exist "%BUILD_DIR%\%EXE_NAME%" (
    echo [����] �Ҳ�����ִ���ļ�
    echo ·��: %BUILD_DIR%\%EXE_NAME%
    pause
    exit /b 1
)

:: �����������Ŀ¼
echo ����׼�����Ŀ¼...
if exist "%OUTPUT_DIR%" (
    echo ����ɾ�����ļ�...
    rmdir /s /q "%OUTPUT_DIR%"
    timeout /t 2 >nul
)
mkdir "%OUTPUT_DIR%"

:: ���ƿ�ִ���ļ�
echo ���ڸ��ƿ�ִ���ļ�...
copy "%BUILD_DIR%\%EXE_NAME%" "%OUTPUT_DIR%\%EXE_NAME%"

:: ִ��windeployqt������ģʽ��
echo ����ִ��windeployqt...
"%QT_BIN%\windeployqt.exe" --debug --no-compiler-runtime "%OUTPUT_DIR%\%EXE_NAME%"

:: ����Ƿ�ɹ�
if errorlevel 1 (
    echo [����] windeployqtִ��ʧ��
    echo ���ش���: %errorlevel%
    pause
    exit /b %errorlevel%
)

:: ����MinGW����ʱ
echo ���ڸ�������ʱ��...
copy "%QT_BIN%\libgcc_s_dw2-1.dll" "%OUTPUT_DIR%"
copy "%QT_BIN%\libstdc++-6.dll" "%OUTPUT_DIR%"
copy "%QT_BIN%\libwinpthread-1.dll" "%OUTPUT_DIR%"

:: ��֤�����ļ�
echo ������֤�ļ�...
dir "%OUTPUT_DIR%"

:: ���
echo.
echo ============================================
echo ����ɹ������Ŀ¼:
echo %OUTPUT_DIR%
echo ============================================
pause
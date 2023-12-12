# vs中的qt插件安装

- 扩展--- Qt vs tools

# 配置qt安装包的环境变量

- 路径

```
D:\Qt\Qt5.14.2\5.14.2\msvc2017_64
```

- cmake中配置直接在vs中添加

```
#set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/../Qt/Qt5.14.2/5.14.2/msvc2017_64)
-DCMAKE_PREFIX_PATH=D:\Qt\Qt5.14.2\5.14.2\msvc2017_64
#直接在vs的cmake的配置中设置
```

# qt在vs中编译问题

- 以notepad--为例子，需要checkout到cmake-dev分支, 重新clean掉工程，windows-deployqt.cmake中加载进入可以编译运行
- vs中winddows下不采用windeployqt工具，运行程序的时候会出现库找不到问题
- 设置windows中vs CMakeSettings.json

```json
{
  "configurations": [
      {
            "name": "x64-Debug",
            "generator": "Ninja",
            "configurationType": "Debug",
            "inheritEnvironments": [ "msvc_x64_x64" ],
            "buildRoot": "${projectDir}\\out\\build\\${name}",
            "installRoot": "${projectDir}\\out\\install\\${name}",
            "cmakeCommandArgs": "-DCMAKE_PREFIX_PATH=D:\\Qt\\Qt5.14.2\\5.14.2\\msvc2017_64 -DUSE_WINDOWS_UNIVERSAL=ON -DUSE_WINDOWS_UNIVERSAL=ON",
            "buildCommandArgs": "",
            "ctestCommandArgs": ""
          }
    ]
}
```

# qml

### 开源项目

- [OCR](https://github.com/hiroi-sora/Umi-OCR)

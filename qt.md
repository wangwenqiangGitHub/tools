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

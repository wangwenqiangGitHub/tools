# PC5接口
- 是车的模组和车，路侧设备，人交互的接口。使用V2X业务UE之间用户面进行D2D(Device to Device)直接通信的接口。pc5可以作为没有无线网络覆盖时直接车车通讯的途径，所以uu和PC5可以共存。(PC5接口这种不需要依赖基站的车与车之间的通信可以达到多大覆盖范围，普通城市200米左右，空旷测试场500-800米，是目前主流解决方案)
# Uu接口：
- 是车模组和基站的空口,uu口遵循3gpp LTE/5G的协议。

# openv2x服务
- 搭建服务器
```
git clone https://github.com/open-v2x/docs.git
cd src
sudo bash ./install.sh
```

- OpenV2X 边缘云控平台网址：http://{host}:80/user/login 
- RSE 模拟器: http://{host}:6688

# python fastAPI框架
```
uvicorn main:app --reload
```
命令unicorn main:app指的是:
	main:文件中main.py(Python模块)
	app:在main.py中使用app = FastAPI()创建的对象。
	-- reload 在代码更改后重新启动服务器。


## netcat
- 服务器监听TCP和UDP的端口
```shell
nc -l 1111
```
- 客户端监听1111端口
```shell
nc 127.0.0.1 1111
```

- busybox
```shell
#服务器
nc -l -p 1234
#客户端 
nc 0.0.0.0 1234
```





# mosquitto 设置
- mosquitto version 2.0.14及以上不支持1883端口。
- 修改mosquito的配置文件为:
```
listener 8885
allow_anonymous true
```

# mqtt设置
- 配置非加密为ssl地址: 本机ip
- 打开终端订阅topic:
```shell
mosquitto_sub -h 192.216.223.11 -p 8885 -t "vpub/status"
```
- 发布topic:
```
mosquitto_pub -t 'buildchange' -m '{"state":"building","resultKey":"IRNG-CORE-GC-JOB1-197","chainName":"BRANCH-IR-1-123"}'
```

<++>

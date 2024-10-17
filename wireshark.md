# mqtt包查看

- 右键解析协议：选中一条报文--> Decode As ---\>mqtt
- 如何查看谁先断开，fin 或者RST

# 过滤hex

![查找hex](./images/wireshake_hex.png)

# 通过wireshake查看fin

```
(mms||((tcp.port == 102)&&(tcp.flags.fin==1||tcp.flags.reset==1||tcp.flags.syn==1))||(cotp.type==0x0d)||(cotp.type==0x0e)||(cotp.type==0x08))
```

# 通过数据内容过滤

```
tcp.port == 2404 && (tcp contains 852A)
```

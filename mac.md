# terminal显示GB2312

- 需要使用mac自己的terminal配置GB2312:终端--->设置--->高级--->多语言环境(GB2312)


# citrix
```
cd /Library/Application\ Support/Citrix\ Receiver/
cat usb.conf
# 优先允许 ASIX 网卡
 ALLOW: vid=0b95 pid=1790
 ALLOW: vid=0bda pid=8153  # Realtek USB 10/100/1000 LAN

# 原有规则（保持后续拒绝逻辑）
 DENY: vid=17e9
 DENY: class=02
 DENY: class=09
 ALLOW:vid=056a pid=0315 class=03
 ALLOW:vid=056a pid=0314 class=03
 ALLOW:vid=056a pid=00fb class=03
 DENY: class=03 subclass=01 prot=01
 DENY: class=03 subclass=01 prot=02
 DENY: class=0a
 DENY: class=0b
 DENY: class=e0
 DENY: class=ef subclass=04  # 此规则不会影响已允许的 ASIX 设备
 ALLOW:

```


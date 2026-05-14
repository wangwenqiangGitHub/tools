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

# mac配置静态ip

````
# **IP设置**
# 参考:https://github.com/Curiouserw/gitbooks-devops-roadmap/blob/318d608e92838244428cd7257000ae3a139e41a2/origin/macos-tips.md?plain=1#L386

networksetup -listallhardwareports
# （Hardware Ports）与其对应的设备名称（如 en0, en1），方便后续使用 networksetup 命令时指定正确的接口
# 字段
#   Hardware Port	人类可读的接口名称（用于 networksetup 命令的 <networkservice> 部分，例如 "Wi-Fi"）
#   Device	BSD 设备名称，例如 en0，用于底层命令如 ifconfig 或 airport
#   Ethernet Address	网卡的物理 MAC 地址

```bash
# 设置为静态 IP
networksetup -setmanual "Wi-Fi" 192.168.1.100 255.255.255.0 192.168.1.1

# 设置为 DHCP
networksetup -setdhcp "Wi-Fi"
````

# mac mouse鼠标设置

```bash
defaults read -g com.apple.mouse.scaling

defaults write -g com.apple.mouse.scaling 8
```

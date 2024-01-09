# 运维om(operations and maintenance)
# 波特率查寻
- `stty -F /dev/ttyS1 speed`
# 设置波特率
- `stty -F /dev/ttyS1 ospeed 921600 ispeed 921600`
- 查看:`cat /dev/ttyS1`
# ifconfig用于配置网络
- `ifconfig eth0 192.168.1.100 netmask 255.255.255.0`

### 基础命令

- dd命令是用于复制文件和转换文件的命令工具,它可以从一个文件或设备复制数据，并将数据输出到另一个文件或者设备中，可以创建镜像文件,备份和恢复数据,以及执行数据转换等操作。

```
/bin/busybox dd if=/dev/do/u-boot.bin of=/dev/block/mmcblk0boot0 seek=0 skip=0 bs=512 count=1063
# -if 是指定输入文件
# -of 是指定输出文件
# seek 是跳过输出文件的前0个块
# skip 跳过输入文件的前0个块
# bs=512是设置块大小为512字节
# count = 1063: 仅拷贝1063个块.
# 命令的作用是将u-boot.bin的数据写入到mmcblk0boot0设备中，从第0个块开始,每次拷贝512个字节，总共拷贝1063个块的数据
```

### 加密算法

ECDSA密钥对, 椭圆曲线选择secp256k1: openssl ecparam -genkey -name secp256k1 -out private.pem openssl ec -in
private.pem -pubout -out public.pem

## 哈希

- 特点:
  - 不可逆
  - 抗碰撞性强
    - 不同的数据有不同的哈希值，相同的数据哈希值是相同的
  - 原始数据有细微的变化，哈希值的变化是非常大的
  - 通过哈希函数得到原始数据进行运算，得到的哈希值长度是固定的
  - 原始的哈希值是一个定长的二进制字符串
- 哈希算法：
  - MD5
    - 散列值是16byte
  - sha1
    - 散列值是20byte
  - sha224
    - 散列值是24byte
  - sha256
    - 散列值是32byte
  - sha384
    - 散列值是48byte
  - sha512
    - 散列值是64byte

> 以上说的散列值长度是二进制数据长度，一般散列值使用16进制格式的数字串表示，看到的字符串长度是原来的2倍。

> sha系列对应的头文件是<openssl/sha.h>

```cpp
#include <iostream>
#include <openssl/sha.h>

using namespace std;

void sha1Test(){
	// 初始化
	SHA_CTX ctx;
	SHA1_Init(&ctx);
	// 添加数据
	SHA1_Update(&ctx, "hello", strlen("hello"));
}
int main(){
	return 0;
}
```

## 非对称加密

- 密钥是一个密钥对:公钥，私钥
  - 公钥加密，必须私钥解密
  - 私钥加密，必须公钥解密
- 加密强队比较高，效率低
  - 不会使用非对称加密，加密特别大的数据
- 应用场景:
  - 密钥分发--->对称加密
    - 核心思想:
  - 签名->验证数据是否被篡改，验证数据的所有者

## 对称加密

- 实现

```
证书：https://blog.csdn.net/huang714/article/details/104748829
	：https://blog.csdn.net/zz420521/article/details/81226113
```

<++>

//=====================================================================
//
// test_rsa.cpp - 
//
// Created by wwq on 2022/05/20
// Last Modified: 2022/05/20 17:00:22
// 非对称加密
//=====================================================================
#include <cstdio>
#include <iostream>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h> //将密钥对写入到磁盘

// OPENSSL_Uplink no OPENSSL_Applink错误 Applink()函数不属于Openssl的dll內部函数的一部分
// 通过的dll分析器看出这个函数不存在，所以必须把applink.c文件应用程序的一部分编译。
void generateRsaKey(){
	// 1.创建rsa变量
	RSA* rsa = RSA_new();
	// 1.5 创建bignum对象，并初始化
	BIGNUM* e = BN_new();
	BN_set_word(e, 12345);
	// 2 生成密钥对->密钥对在内存中
	RSA_generate_key_ex(rsa, 1024, e, NULL);
	// 3.将密钥对写入到磁盘
	FILE* fp = fopen("public.pem", "w");
	PEM_write_RSAPublicKey(fp,rsa);
	fclose(fp);
	// 写私钥
	fp = fopen("private.pem", "w");
	PEM_write_RSAPrivateKey(fp, rsa, NULL, NULL, 0, NULL, NULL);
	fclose(fp);
}


int main(){
	generateRsaKey();
	return 0;
}

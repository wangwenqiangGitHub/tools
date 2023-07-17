#! /bin/sh
#======================================================================
#
# rsa.sh - 
#
# Created by wwq on 2023/07/07
# Last Modified: 2023/07/07 16:51:22
#
#======================================================================

# 生成RSA私钥
openssl genrsa -out private.key 512

# 从RSA私钥中提取公钥
openssl rsa -in private.key -outform PEM -pubout -out public.key


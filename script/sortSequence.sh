#! /bin/sh
#======================================================================
#
# sortSequence.sh - 
#
# Created by wwq on 2024/05/09
# Last Modified: 2024/05/09 14:28:23
#
#======================================================================
# 生成一个从1-128的文件
seq 1 128 | sort -n > compare.txt
# 将原来的文件按照第三列排序
awk '{print $3}' test.txt | sort -n -k1 > num.txt
# 比较两个文件
comm -23 num.txt compare.txt

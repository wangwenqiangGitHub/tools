#!/bin/bash  
#======================================================================
#
# convert.sh - 
#
# Created by wwq on 2024/07/24
# Last Modified: 2024/07/24 15:07:28
#
#======================================================================

# 指定要处理的目录
DIRECTORY=$1

# 遍历目录下的所有.c、.cpp和.h文件
find "$DIRECTORY" -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.h" \) | while read file; do
    # 去除UTF-8-BOM（如果有的话），这里使用sed简单处理
    # 注意：这个方法可能不是100%准确，特别是对于非文本文件
    # 如果你的文件大多是文本，且确实可能包含BOM，可以使用这个方法
    # sed -i '1s/^\xEF\xBB\xBF//' "$file"

    # 将文件从UTF-8转换为GBK  
    # 注意：这里假设你的文件已经是UTF-8编码（无论是否去除了BOM）
    iconv -f UTF-8 -t GBK "$file" -o "${file}.tmp" && mv "${file}.tmp" "$file"
done

find . -type f -name "*.tmp"
#find . -type f -name "*.tmp" -exec rm {} \;
echo "所有文件已转换为GBK编码"

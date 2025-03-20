#!/bin/bash

# 脚本功能：自动清理依赖包名并下载安装 samba-libs 及其依赖

# 步骤1：提取依赖包名并清理版本信息
echo "正在提取并清理依赖包名..."
depends_line=$(dpkg -s samba-libs | grep Depends | sed 's/Depends: //')

# 使用多步处理确保完全清理
cleaned_packages=$(echo "$depends_line" | \
                   sed -E 's/ $[^)]+$//g; s/,//g; s/ /\n/g' | \
                   grep -E '^[a-z][a-z0-9-]+(\.[a-z0-9]+)?$' | \
                   sort | uniq)

# 将清理后的包名写入文件
echo "$cleaned_packages" > packages.txt
echo "已生成干净的包列表："
# cat packages.txt
column -t packages.txt

# 步骤2：下载所有依赖包
echo "正在下载依赖包..."
mkdir -p debs
cd debs

# 使用循环处理确保稳定性
while read pkg; do
    if [ -n "$pkg" ]; then
        echo "正在下载: $pkg"
        sudo apt-get download "$pkg"
    fi
done < ../packages.txt

# 步骤3：安装所有包并修复依赖
echo "开始安装..."
sudo dpkg -i *.deb 2>&1 | grep -v "warning: files list"  # 忽略常见警告

# 处理可能的依赖问题（离线环境中需提前下载所有依赖）
if [ $? -ne 0 ]; then
    echo "警告：部分依赖可能未完全安装，请检查 debs 目录是否包含所有依赖包"
else
    echo "安装完成！"
fi

# 验证结果
echo "验证已安装的包："
dpkg -l | grep -E "$(tr '\n' '|' < ../packages.txt | sed 's/|$//')"

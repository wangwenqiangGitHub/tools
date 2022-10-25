#! /bin/sh
#======================================================================
#
# frpc.sh - 
#
# Created by wwq on 2022/10/25
# Last Modified: 2022/10/25 09:39:36
#
#======================================================================
echo '密码'|sudo -S service ssh start
cd /home/kingwq/frp/frp_0.37.1_linux_amd64
nohup ./frpc -c ./frpc.ini > /dev/null &


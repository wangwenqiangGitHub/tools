DDOS deflate `DDOS deflate`是一款免费的用来防御和减轻DDOS攻击的脚本. 它通过netstat监测跟踪创建大量网络连接的IP地址, 在检测到某个结点超过预设的限制时,
该程序会通过APF或IPTABLES禁止或阻挡这些IP.

安装:

```
wget http://www.moerats.com/usr/down/DDOS/deflate.sh && \
chmod +x deflate.sh && \
./deflate.sh
```

配置文件`/usr/local/ddos/ddos.conf`

```
##### Paths of the script and other files
PROGDIR="/usr/local/ddos"
PROG="/usr/local/ddos/ddos.sh"
IGNORE_IP_LIST="/usr/local/ddos/ignore.ip.list"
# 白名单.如有反向代理,注意添加本机地址和本机外网IP地址,防止提供反向代理的主机被判定为攻击.
CRON="/etc/cron.d/ddos.cron"
APF="/etc/apf/apf"
IPT="/sbin/iptables"##### frequency in minutes for running the script

##### Caution: Every time this setting is changed, run the script with cron
##### option so that the new frequency takes effect
FREQ=1

##### How many connections define a bad IP? Indicate that below. 
# 单IP发起连接数阀值,不建议设置太低.
NO_OF_CONNECTIONS=150

##### APF_BAN=1 (Make sure your APF version is atleast 0.96)
##### APF_BAN=0 (Uses iptables for banning ips instead of APF) 
#一般情况下你是使用iptables来做防火墙,所以这里你需要将 APF_BAN的值改为0.
APF_BAN=1

##### KILL=0 (Bad IPs are’nt banned, good for interactive execution of script)
##### KILL=1 (Recommended setting)
KILL=1 
#是否屏蔽IP, 默认即可

##### An email is sent to the following address when an IP is banned. 
# 当单IP发起的连接数超过阀值后,将发邮件给指定的收件人.
##### Blank would suppress sending of mails
EMAIL_TO="root" 
# 这里是邮箱, 可以把root替换成你的邮箱

##### Number of seconds the banned ip should remain in blacklist. 
# 设置被挡IP多少秒后移出黑名单.
BAN_PERIOD=600
```

将上述配置文件修改完成后, 使用命令启动即可

```
ddos -d
```

Ubuntu中可能会报错:

```
root@localhost:~# ddos -d
/usr/local/sbin/ddos: 13: [: /usr/local/ddos/ddos.conf: unexpected operator
DDoS-Deflate version 0.6
Copyright (C) 2005, Zaf <zaf@vsnl.com>
```

因为启动大多数为 bash 脚本, 而 Ubuntu 的默认环境为 dash, 所以需要使用 dpkg-reconfigure dash, 选择 NO, 切换为 bash 运行脚本:

```
dpkg-reconfigure dash
```

# ubuntu apt
```
/etc/apt/apt.conf.d

dtvl@ubuntu:/etc/apt/apt.conf.d$ vi 05proxy
Acquire::http::Proxy "http://192.216.223.13:808";
```

# git
```
#.gitconfig

```

# wsl2
```shell
#!/bin/bash
host_ip=$(cat /etc/resolv.conf |grep "nameserver" |cut -f 2 -d " ")
export ALL_PROXY="http://$host_ip:7890"
```



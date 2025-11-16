1. 对于本地的`.svn`文件恢复所有文件
```
svn revert --recursive .
```

2. svn转git
```
svn log --xml | grep "^<author" | sort -u | \awk -F '<author>' '{print $2}' | awk -F '</author>' '{print $1}' > userinfo.txt
#输出如下:
alex
misha
loki
#手动修改
 alex = alex <alex@alibaba.com>
misha = misha <misha@alibaba.com>
loki = loki <loki@alibaba.com>
# svn转git
 git svn clone "SVN repo URL" --prefix=svn/ --no-metadata --authors-file=userinfo.txt
```



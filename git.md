# 使用前一次的commit
```shell
git add .
#--amend 修改最新的一次commit，将最近一次的staged change直接添加到上一次commit 去，不用生成新的commit
# --no-edit 不修改提交信息
git commit --amend --no-edit

# 想要修改提交信息
git commit --amend
```
# git时光机 git查看历史操作及记录
```shell
git reflog
#看到一系列提交记录，返回某一个提交记录
git reset HEAD@{index}
# --hard, 当前操作啥都不要了
#--soft 保留当前的修改回到对应的状态
```

# git后悔药  修改很长时间的一次提交
```shell
git log
# c111 commit 3
# c222 commit 2
# c333 commit 1

# commit 2 出问题了，要恢复某个文件在commit1中的内容，先看它修改了什么
git show c222
git checkout c333 -- test.txt 
# 这个时候就会发现 test.txt 恢复到了c333的状态

# 删除对应的commit，这次commit带来了各种bug，想清理一下
- commit2 出了问题，我们要一次性删除掉对应的提交
git revert c222[第二天对应的hash]
```
# git切换远程分支，并且切换到某个版本tag
```shell
git checkout -b dev origin/dev

#新建分支并推送至远程分支
git branch -b test
git push --set-upstream origin test

#切换到某个版本
git reset --hard 3efad
```


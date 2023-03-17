# 使用前一次的commit

```shell
git add .
#--amend 修改最新的一次commit，将最近一次的staged change直接添加到上一次commit 去，不用生成新的commit
# --no-edit 不修改提交信息
git commit --amend --no-edit

# 想要修改提交信息
git commit --amend
# 删除提交的commit-Id
```

# git时光机 git查看历史操作及记录

```shell
git reflog
#看到一系列提交记录，返回某一个提交记录
git reset HEAD@{index}
# --hard, 当前操作啥都不要了
#--soft 保留当前的修改回到对应的状态
```

# git后悔药 修改很长时间的一次提交

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

# git pull script

```shell
set -x
function git_pull_all() {
	for dir_name in `ls $1`
	do
		cur_dir="$1/$dir_name"
		if [ -d $cur_dir ]
		then
			cd $cur_dir
			git pull
		fi
	done
}

git_pull_all $PWD
```

# rebase使用场景

- 当远程分支是超前于本地分支，本地开发的代码可以少一次merge，通过rebase实现:

```shell
git pull -r
```

- clone了远程仓库dev分支，然后基于dev分支创建了自己的本地开发分支xyz，并进行了一些代码修改工作,这时候同事A告诉你他修复了重要的bug。并且已经merge到远程dev分支了，问：如何同步到你本地xyz分支;

```shell
git checkout dev && git pull -r && git checkout - && git rebase dev
```

# git 切换分支

- 当前在A分支上开发，但是没有完成开发，想切换到B分支，如果当前分支所做的修改没有提交就切换去其他分支也会看到相同的修改，所以解决这个问题有两个办法：

```shell
# 方法1:
git add ;git commit提交修改，只要用git status检查工作区和暂存区是干净的。
# 方法2:当我当前分支上的工作还没做完，不能提交，但是想提交到其他分支，这时需要将当前分支的工作现场隐藏起来，用git stash 隐藏起来，这个时候用git status查看工作区是干净的，所以就是可以放心去其他分支。用git stash list可以查看隐藏起来的工作现场。
# 通过stash恢复方法1:先恢复，在删除stash内容
git stash apply && git stash drop
# 通过stash恢复方法2:
git stash pop
```

- 可以多次 stash ，恢复的时候，先用 git stash list查看，然后用 git stash apply stash@{0}或者 git stash pop
  stash@{0}恢复指定的stas

> 产生这种现象的原因：1.没有add，也没commit 切换分支修改的内容在另一个分支上也有 （有时候也无法切换分支，原因如切换时会提示会覆盖另一个分支文件的内容，也可强制切换git
> checkout branchname -f ，最好不要强制切换，会丢失之前分支的修改内容，可以先stash或commit，再切换） 2.add，但没有commit
> 切换分支，修改的内容在另一分支上也有（有时和情况1一样无法切换） 3. add并且commit 切换分支，在另一个分支就看不到修改内容了 ;原因：一个本地的git
> repo只有一个工作区和暂存区，但是有多个分支的提交区，而我们的checkout只是将HEAD指针从一个分支切换到另一个分支。

# 在多个git服务器和用户之间进行切换的解决方案

- 所有的git仓都使用git config --local配置邮箱，用户名
- 更优雅的方案(参考卖逗搞IT)
  - 创建一个private的git config:
  ```
  ➜  ~ more ~/.gitconfig-private
  [user]
      email = pengxiao@private.com
      name = Peng Xiao
  ```
  - 在global的gitconfig里设置当使用私人目录的时候，就加载私人的git config:
  ```
  ➜  ~ more ~/.gitconfig
  [user]
      email = pengxiao@company.com
      name = Peng Xiao
  [includeIf "gitdir:~/tmp/private/"]
  path = .gitconfig-private
  ```
  - 验证:
  ```
  ```

#测试公司仓库 ➜ ~ cd tmp/company/github-test ➜ github-test git:(master) touch test.txt ➜ github-test
git:(master) ✗ git add test.txt ➜ github-test git:(master) ✗ git commit -m 'first commit' [master
a64b46f] first commit 1 file changed, 0 insertions(+), 0 deletions(-) create mode 100644 test.txt ➜
github-test git:(master) git log commit a64b46f0cecac00c2791f169a722b805596eec71 (HEAD -> master)
Author: Peng Xiao <pengxiao@company.com> Date: Fri Jul 2 12:39:33 2021 +0200 first commit

# 测试私有仓库

    ➜  ~ cd tmp/private/gitlab-test
    ➜  gitlab-test git:(main) more .git/config
    [core]
            repositoryformatversion = 0
            filemode = true
            bare = false
            logallrefupdates = true
    [remote "origin"]
            url = git@gitlab.com:zhangsan163/gitlab-test.git
            fetch = +refs/heads/*:refs/remotes/origin/*
    [branch "main"]
            remote = origin
            merge = refs/heads/main
    ➜  gitlab-test git:(main) touch test.txt
    ➜  gitlab-test git:(main) ✗ git add test.txt
    ➜  gitlab-test git:(main) ✗ git commit -m 'first commit'
    [main b91a660] first commit
     1 file changed, 0 insertions(+), 0 deletions(-)
     create mode 100644 test.txt
    ➜  gitlab-test git:(main) git log
    ➜  gitlab-test git:(main)
    commit b91a6607e20bb07b55e60ffa7478f25e3d621cd8 (HEAD -> main)
    Author: Peng Xiao <pengxiao@private.com>
    Date:   Fri Jul 2 12:41:59 2021 +0200
        first commit
    ```

# git 搜索

在commit中搜索字符串:

```
git log --grep "update st"
```

搜索某个动词

```sh
git log --grep "fix " --pretty=format:'%h %an %ci %s'|sort|grep --color "fix "
```

搜索某个人的提交

```sh
git log --author "Rob king" --pretty=format:"%an %ci %s"
```

可以一次指定多个作者

```sh
git log --author="Rob Pike" --author="Brad Fitzpatrick" --author="Russ Cox" --author="Robert Griesemer"
```

显示某个详情

```sh
git log -1 141b09726dcfc1fa9f04ee9e08e6fa4af00fa57b
git show 141b09726dcfc1fa9f04ee9e08e6fa4af00fa57b
```

# git 代理

```
[http]
            proxy = socks5://127.0.0.1:7890
[https]
            proxy = socks5://127.0.0.1:7890
```

# git 拉取错误

> bower error status code of git: 128 fatal: unable to connect to github.com: github.com[0: 你的IP]:
> errno=Operation timed out 原因： 需要用https才能读到数据 解决方法：输入命令 git config --global
> url."https://".insteadOf git://

# git同步fork的代码

```
cd .vim/vim-init
git remote -v
git remote add upstream https://github.com/skywind3000/vim-init.git
git remote -v
git fetch upstream
git checkout master
git branch -a
git merge upstream/master
# 如果有冲突需要解决冲突
git push origin master
```

# .gitignore文件自动生成

- https://www.toptal.com/developers/gitignore

# git撤销git add

```
git reset <file>  或  git reset 取消所有更改即可。
在旧版本的 Git 中，以上两个命令分别是 
git reset HEAD <file> 和 git reset HEAD。Git 1.8.2 做了更新。
```

# git 查看本地修改文件做了哪些改动

- git diff .

# git 提交空消息，保持上一次提交的commit

```shell
git commit --allow-empty-message --allow-empty -m ""
```

# ssh免密登录

```
ssh-genkey -o
```

# 将远程分支与本地分支关联

```
git branch --set-upstream-to=origin/develop develop
```

# git中出现^M问题

```
#删除 :
    %s/^M$//g
# 或者配置git:
    git config --global core.whitespace cr-at-eol
```

# git submodule

- 克隆含有子模块的项目:

```
git submodule update --init
```

- git 拉取远程引用的子代码仓库的更新 git submodule update --remote

# vim中git查看修改记录

```
G blame
```

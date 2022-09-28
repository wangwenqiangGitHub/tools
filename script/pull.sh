#! /bin/bash
#======================================================================
#
# pull.sh -
#
# Created by wwq on 2022/07/08
# Last Modified: 2022/07/08 10:32:27
#
#======================================================================
set -x
function git_pull_all( ){
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

#! /bin/sh
#======================================================================
#
# installTmux.sh - 
#
# Created by wwq on 2024/05/09
# Last Modified: 2024/05/09 20:32:20
#
#======================================================================
wget https://github.com/tmux/tmux/releases/download/3.4/tmux-3.4.tar.gz
tar zxvf tmux-3.4.tar.gz
cd tmux-3.4
sudo apt update
sudo apt-get install libncurses5-dev libncursesw5-dev
sudo apt install libevent-dev
sudo apt install byacc
sudo mv /usr/bin/tmux /usr/bin/tmux-
./configure
make -j8
sudo make install

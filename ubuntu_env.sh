#! /bin/sh
#======================================================================
#
# install_vim.sh - 
#
# Created by wwq on 2022/05/25
# Last Modified: 2022/05/25 10:21:15
#
#======================================================================
set -x

sudo apt install gcc g++ make cmake gdb
sudo apt install clangd
sudo apt install nodejs
sudo apt install yarn
sudo apt install ripgrep

#----------------------------------------------------------------------
# gtags
#----------------------------------------------------------------------
sudo apt-get install libncurses-dev
wget https://ftp.gnu.org/pub/gnu/global/global-6.6.tar.gz
cd global-6.6
./config
make
sudo make install

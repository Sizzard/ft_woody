#!/bin/bash

sudo apt-get update -y
sudo apt-get install hexedit -y
sudo apt-get install valgrind -y
sudo apt-get install make -y
sudo apt-get install gcc -y
sudo apt-get install nasm -y
sudo apt-get install strace -y

echo 'alias c="clear"' >> .bashrc
echo 'cd /vagrant' >> .bashrc
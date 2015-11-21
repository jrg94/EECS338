#!/bin/sh
clear
rpcgen cookies.x
make clean
cd ..
tar -cvf "Assignment6.tar" "Assignment6"
scp "Assignment6.tar" jrg170@eecslinab3.case.edu:\~
ssh -f jrg170@eecslinab3 "tar -xvf Assignment6.tar;
			cd Assignment6;
			rpcgen cookies.x;
			make"
ssh -f jrg170@eecslinab3 "./Assignment6/mother > Assignment6/mother.stdout"
ssh -f jrg170@eecslinab3 "./Assignment6/tina localhost > Assignment6/tina.stdout"
ssh -f jrg170@eecslinab3 "./Assignment6/judy localhost > Assignment6/judy.stdout"

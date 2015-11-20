#!/bin/sh
clear
rpcgen cookies.x
make
ssh -f jrg170@eecslinab2 
ssh -f jrg170@eecslinab3
ssh -f jrg170@eecslinab7

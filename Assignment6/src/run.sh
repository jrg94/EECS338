#!/bin/sh
clear
rpcgen cookies.x
make
ssh -f jrg170@eecslinab2 "./tina"
ssh -f jrg170@eecslinab3 "./judy"
ssh -f jrg170@eecslinab7 "./mother"

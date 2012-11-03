#!/bin/sh
DIR=$1
FILE=$2
ftp -i -in <<!
open 192.168.0.201 21
user root root
cd /home
lcd $DIR         
put $FILE
bye 
!
ls -l $DIR/$FILE

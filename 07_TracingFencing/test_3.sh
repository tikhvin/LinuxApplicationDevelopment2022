#!/usr/bin/env bash

if [ $# -eq 2 ] ; then
	cal > $1
	strace -e fault=read:error=EPERM:when=2 -o /dev/null ./move $1 $2 &> /dev/null

	if [ $? -eq 3 ] && [ -f $1 ] ; then
		echo "Test#3 - PASS!"
	else
		echo "Test#3 - FAIL!"
	fi

	if [ -f $1 ] ; then
		rm $1
	fi

	if [ -f $2 ] ; then
		rm $2
	fi
else
	echo "Help:"
	echo -e "\t> ./$(basename $0) infile outfile"
fi

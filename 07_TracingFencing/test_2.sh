#!/usr/bin/env bash

if [ $# -eq 2 ] ; then
	cal > $1
	strace -e fault=openat:error=ENOENT:when=4 -o /dev/null ./move $1 $2 &> /dev/null

	if [ $? -eq 2 ] && [ -f $1 ] ; then
		echo "Test#2 - PASS!"
	else
		echo "Test#2 - FAIL!"
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

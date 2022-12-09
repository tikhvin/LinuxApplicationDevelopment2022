#!/usr/bin/env bash

if [ $# -eq 2 ] ; then
	cal > $1
	strace -e fault=openat:error=ENFILE:when=3 -o /dev/null ./move $1 $2 &> /dev/null

	if [ $? -eq 1 ] && [ -f $1 ] ; then
		echo "Test#1 - PASS!"
	else
		echo "Test#1 - FAIL!"
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

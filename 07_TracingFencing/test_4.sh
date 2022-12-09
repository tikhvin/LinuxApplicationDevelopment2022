#!/usr/bin/env bash

if [ $# -eq 2 ] ; then
	cal > $1
	LD_PRELOAD=$(pwd)/fake_remove.so ./move $1 $2 &> /dev/null

	if [ $? -eq 0 ] && [ -f $1 ] ; then
		echo "Test#4 - PASS!"
	else
		echo "Test#4 - FAIL!"
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

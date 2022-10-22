#!/usr/bin/env bash

if [ -z $1 ] ; then
	time=0.05
else
	time=$1
fi

declare -a triplets

row=0
while IFS= read -r line ; do
	column=0
	while [ $column -lt ${#line} ] ; do
		character=${line:$column:1}
		if [ "$character" != ' ' ] ; then
			triplets+=("$row-$column-$character")
		fi
		((column=column+1))
	done
	((row=row+1))
done

tput clear

for triplet in $(shuf -e "${triplets[@]}") ; do
	row=$(echo $triplet | cut -f1 -d "-")
	column=$(echo $triplet | cut -f2 -d "-")
	character=$(echo $triplet | cut -f3 -d "-")
	tput cup $row $column
	echo -ne $character
	sleep $time
done

tput cup $(tput lines) 0

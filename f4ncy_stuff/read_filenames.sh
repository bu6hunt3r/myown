#!/bin/bash

function usage() {
		echo "Usage: $0 -f <file containing dl-list>";
		exit 0;
	}

function grab() {
	LIST=()
	echo "Parsing $1";	
	while read line; do
		LIST+="$line"
	done < $1
	echo $LIST
}
if [[ $# -lt 2 ]]; then
		usage;
else
	while getopts ":f:" opt
	do
		case $opt in  
			f)	
			echo "Retrieving files from list...[$OPTARG]";
			file=$OPTARG
			[[ ! -f $file ]] && echo "Not Regular file..." && exit 0;
			grab $file;
			exit 0;
			;;
			h)
			usage
			;;
			\?)
			usage;
			;;
		esac
	done
fi

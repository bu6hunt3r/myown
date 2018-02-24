#!/bin/bash


function usage() {
		echo "Usage: $0 -f <file containing dl-list>";
		exit 0;
	}

function dl() {

trap 'exit 1' INT

HOST='nextcloud'
USER='cr0c0'
PASSWD='270488'
FILE=$1
ftp -n $HOST <<END_SCRIPT
quote USER $USER
quote PASS $PASSWD
binary
cd transfer/Musik
get $FILE
quit
END_SCRIPT
}

function grab() {
	LIST=()
	line_nums=$(wc -l $1 | cut -d" " -f 1);
	echo "$line_nums";
	i=0	
	while read line; do
		LIST+="$line"
		i=$(( i+1 ))
		echo -e "\e[1AProcessing \033[1;32m$(expr $i/$line_nums)\r\033[0m"
		dl $line;
	done < $1
}
if [[ $# -lt 2 ]]; then
		usage;
else
	while getopts ":f:" opt
	do
		case $opt in  
			f)	
			echo -e "\xE2\x9C\x94 Retrieving files from list...[$OPTARG]";
			file=$OPTARG
			[[ ! -f $file ]] &&  printf "Not Regular file...\n" && exit 0;
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

int:
	echo "033[1;31mReceived Ctrl-C interrupt signal...Exiting\033[0m"
	exit 1

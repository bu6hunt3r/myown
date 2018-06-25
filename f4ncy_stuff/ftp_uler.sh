#!/bin/bash

function usage() {
		echo "Usage: $0 -f <file containing dl-list>";
		exit 0;
	}

function ul() {

trap 'exit 1' INT

HOST='nextcloud'
USER='cr0c0'
PASSWD='270488'
FILE=$1
ftp -n $HOST <<END_SCRIPT
quote USER $USER
quote PASS $PASSWD
binary
cd transfer/Musik/Offenbarung_23
put $FILE
quit
END_SCRIPT
}

if [[ $# -lt 2 ]]; then
		usage;
else
	while getopts ":d:" opt
	do
		case $opt in  
			d)	
			echo -e "\xE2\x9C\x94 Uploading files from dir: $OPTARG";
			dir=$OPTARG
			[[ ! -d $dir ]] &&  printf "Not Regular dir...\n" && exit 0;
			for file in "$dir"/*; do 
				echo "Uploading ${file##*/}...";
				ul "${file##*/}";
			done
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

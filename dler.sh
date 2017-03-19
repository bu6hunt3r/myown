#!/bin/bash

LIST=""
function do_something()
{
	#echo "LIST: $LIST"
	if ! [[ -f $1 ]]; then
		echo "File $1 seems not be a regular file!..."
		exit 1
	else
		echo "Starting to download from list:"
		for i in $(grep -vE '(^#.*$|^$)' $1); do
			youtube-dl -x --audio-format mp3 --no-playlist $i
		done
	fi
}


function usage()
{
	echo -e "\033[1;31mDownload list of videos:\033[0m"
	echo -e "\t$0 -f <file including list of urls to download>"
	echo -e "\033[1;31mShow this message:\033[0m"
	echo -e "\t$0 -h"
}

if [[ $# -ge 1 ]]; then
	while [ $# -ge 1 ]; do
		key="$1"
		param="$2"

		case $key in
			-f|--file)
				shift
				LIST=$param
				do_something $LIST
				;;

			-h|--help)
				shift
				usage
				exit
				;;
			*)
				echo "Unknown value..."
				usage
				exit 1
				;;
		esac
		shift
	done 
else
	usage
	exit
fi

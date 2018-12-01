#!/bin/bash

LIST=""
PLAYLIST=""
function do_playlist()
{
	#echo "PLAYLIST: $PLAYLIST"
	echo "Starting do download playlist from index $2 to $3..."
	#echo "Parameters are: $1 $2 $3"
	youtube-dl -x --audio-format mp3 --playlist-start $2 --playlist-end $3 $1
}
function do_something()
{
	#echo "LIST: $LIST"
	if ! [[ -f $1 ]]; then
		echo "File $1 seems not be a regular file!..."
		exit 1
	else
		echo "Starting to download from list:"
		for i in $(grep -vE '(^#.*$|^$)' $1); do
			#youtube-dl -x --audio-format mp3 --no-playlist $i
			youtube-dl --no-playlist $i
		done
	fi
}


function usage()
{
	echo -e "\033[1;31mDownload list of videos:\033[0m"
	echo -e "\t$0 -f <file including list of urls to download>"
	echo -e "\033[1;31mDownload playlist from to:\033[0m"
	echo -e "\t$0 -p <URL to playlist> <Start index> <Stop index>"
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
			-p|--playlist)
				PLAYLIST=$2
				START=$3
				END=$4
				do_playlist $PLAYLIST $START $END
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

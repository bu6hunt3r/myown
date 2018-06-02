#!/bin/bash

usage() { echo "Usage: $0 -i [INPUT FILE NAMES] -o [DIR WITHIN TO PERFORM] -p [PATTERN TO SEARCH FOR]"; exit 1; }

while getopts "i:o:p:h" o; do
    case "${o}" in
        i)
            inames=${OPTARG}
            echo -e "\xe2\x9c\x93 Using $inames as input..."
            [[ ! -f "$inames" ]] && echo "NO Regular file";
            ;;
        o)
            outdir=${OPTARG}
            ;;
        h)
            usage
            ;;
        *)
            usage
            ;;
    esac
done

shift $((OPTIND-1))
if [[ $# < 1 ]]; then
    usage;
fi
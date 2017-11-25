#!/bin/sh

in_dir=()
in_conf=()

for i in $(ls /usr/share/grc/); do
	in_dir+=" $(echo $i | cut -d"." -f2)"
done 

for i in $(cat /etc/grc.conf | grep -E "^conf\." | cut -d"." -f2); do
	in_conf+=" $i"
done

echo -e "\033[1;31mIn dir\033[0m"
echo ${in_dir[@]}
echo -e "\033[1;31mIn conf\033[0m"
echo ${in_conf[@]}

echo -e "\033[1;31mDiff\033[0m"
l2=" ${in_conf[*]} "                    # add framing blanks
for item in ${in_dir[@]}; do
  if ! [[ $l2 =~ " $item " ]] ; then    # use $item as regexp
    result+=($item)
  fi
done
echo  ${result[@]}:

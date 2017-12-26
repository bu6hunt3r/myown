#!/bin/bash

if [[ $(date +'%a') == 'Sun' ]]; then
	SUN=$(date +'%B %d')
else
	SUN=$(date --date='last Sunday' +'%B %d')
fi

if [[ $(date +'%a') == 'Sat' ]]; then
	SAT=$(date +'%B %d')
else
	SAT=$(date --date='next Saturday' +'%B %d')
fi
{
	echo -e "Subject: Weekly reminders for week $SUN to $SAT";
	remind -cu+ ~/.reminders/reminders.rem
} | msmtp Felix1Koch@gmail.com

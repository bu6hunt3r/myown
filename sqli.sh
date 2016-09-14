#!/usr/bin/env bash

url="http://challenge01.root-me.org/web-serveur/ch9/"
cookies=spip_version=1234_deadbeefdeadbeefdeadbeafdeadbeef

docurl() {
	curl -s -b "$cookies" -d "login=$1" -d "password=$2" "${url}" |\
		tidy -iq -w 0 -utf8 --show-warnings 0 --show-body-only 1 --quote-nbsp 0 |\
		sed '/^\([[:space:]]<br>\)\?$/d'
}

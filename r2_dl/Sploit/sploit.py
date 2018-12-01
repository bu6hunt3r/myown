#!/usr/bin/env python
#-*- encoding: utf-8 -*-
# vi: set ft=python :

from pwn import *
import optparse
import sys
import os
from genrr2 import GenRR2

BOLD_RED="\033[1;31m"
END="\033[0m"

def check_path(p):
    print os.path.dirname(p)
    return os.path.dirname(p) 

def main():

    required="binpath rr2path payload".split(" ")

    parser=optparse.OptionParser()
    parser.add_option("-b","--binpath",help="Path to binary")
    parser.add_option("-d","--breakpoints",help="Breakpoints to enable")
    parser.add_option("-r","--rr2path",help="Path to rarun2 file")
    parser.add_option("-p","--payload",help="Path to payload")

    opts, args = parser.parse_args()

    forgotten=[]

    for r in required:
        if opts.__dict__[r] is None:
            forgotten.append(r)

    if forgotten:
        print "%sRequired but not available arguments: %s" % (BOLD_RED, END),
        for r in forgotten:
            print " %s " % r,
        print ""
        parser.print_help()
        sys.exit(0)


    for p in opts.__dict__:
        if not check_path(opts.__dict__[p]):
            print "Invalid path %s " % p
            sys.exit(0)

    g=GenRR2(os.path.abspath(opts.binpath), os.path.abspath(opts.rr2path), os.path.abspath(opts.payload))
    g.gen_payload("A"*8)
    g.gen_rr2()

if __name__ == '__main__':
    main()
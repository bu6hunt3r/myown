#!/usr/bin/python

import struct
from binascii import hexlify
import sys

mem = int(sys.argv[1],16)

def to_little_endian(input):
    string=input
    hexStr = hexlify(struct.pack("<i",string))
    print(hexStr)


to_little_endian(mem)

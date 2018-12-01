#!/usr/bin/env python

def encode(l):
    ret=[]
    for n in reversed(l):
        fmask=0
        while True:
            ret.append(n & 127) | fmask
            fmask=128
            n >>= 7
            if n == 0:
                break

    return list(reversed(ret))

def decode(l):
    ret = []
    tmp = 0
    for n in l:
        tmp = (tmp << 7) | (n & 127)
        if not (n & 128):
            ret.append(tmp)
            c, tmp = True, 0
        else:
            c = False
    if not c:
        raise ValueError()
    return ret

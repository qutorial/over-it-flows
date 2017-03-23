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

3. Controlling EIP




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



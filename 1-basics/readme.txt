Abstract.

This sample demonstrates a basic stack overflow and stack protector feature of gcc.

1. The buffer overflow

In the overflow.c we have two adjacent stack variables:

```
 char buff[8];
 int pass=0;
```

We use then an unsafe gets() function to read the password into buffer:

```
 gets(buff);
```

When more than the length of buff characters are provided to gets(),
it will write into the pass variable setting it to true and enabling
the protected by it code:

```
 if(pass) {
  printf("Access granted\n");
 }
```

Even when the password given is not right.

Test it by: 
```
$ make vuln
$ ./overflow
Password please: AAAAAAAAAAAA
Wrong password
Access granted
```

The hack.py and the target hack of Makefile automate the process.

2. Debugging the vulnerable code
Run 

```
make debug
```

And check what happens in edb.


3. Debugging with stack protector

In the make file we disabled the stack protector feature 
of GCC for vuln target. It is enabled for protect target though.

```
make protect
```

The stack smashing is prevented.

```
$ ./overflow 
Password please: AAAAAAAAAAAA
Wrong password
*** stack smashing detected ***: ./overflow terminated
Aborted (core dumped)
```

Let's debug it and figure out how the stack protector works.

4. Debugging with stack protector

Let's compile it with stack protector on and debug in edb.

```
make protect
make debug
```

Debugger starts, press F9 to stop at main() function.

Make a break point with F2 after the call to gets().

Track the execution. 

The canary is saved in the region of memory pointed to by gs register
with a certain offset. It is check before int pass is addressed.

These commands perform the check.

```
xor edx, gs:[0x14] 
je 0x88485aa
call overflow!__stack_chk_fail@plt
```

In the Data Dump window follow an expression 'gs', pressing Ctrl+G.
It will show you the region of memory to which gs register points.
This region is a thread local segment storing canaries.


5. The real fix

The true problem lies in the use of gets() function as GCC rightfully 
tells us. 

```
overflow.c: In function ‘main’:
overflow.c:11:2: warning: implicit declaration of function ‘gets’ [-Wimplicit-function-declaration]
  gets(buff);
  ^~~~
/tmp/cclOM2So.o: In function `main':
overflow.c:(.text+0x3b): warning: the `gets' function is dangerous and should not be used.
```

Writing beyond the buffer on the stack is made possible by it.
So to fix the problem, the program has to be rewritten to control 
the write length into the buffer.

Check for example the fgets() function, accepting the buffer length 
as a parameter.

```
$ make fixed
$ ./fixed 
Password please: AAAAAAAAAAAA
Wrong password
```

6. Additional info and tasks

Storing password in the executable is a bad idea. Storing it in the clear 
is also a bad idea.

Null character string termination is enforced in the 
fixed.c. Is it necessary? Why?

What if we compile the fixed.c without the stack
protector, will it still be vulnerable? Why?

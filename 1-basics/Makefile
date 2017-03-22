.PHONY: clean all hack 32bit protect

all:
	gcc -fno-stack-protector overflow.c -o overflow

32bit:
	gcc -m32 -fno-stack-protector overflow.c -o overflow

protect:
	gcc overflow.c -o overflow

clean:
	rm -rf overflow
hack:
	./hack.py | ./overflow

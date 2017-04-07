.PHONY: clean edit check

classic:
	gcc -fno-stack-protector -z execstack classic.c -o classic

nx:
	gcc -fno-stack-protector classic.c -o nx

clean:
	rm -f classic nx

debug:
	gdb classic

edit:
	nano classic.c

check:
	aspell -c readme.txt

payload:
	python payloadgen.py > in.txt

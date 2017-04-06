.PHONY: clean vuln hack protect debug edit check

vuln:
	gcc -O0 -fno-stack-protector -z execstack control.c -o control

vuln32:
	gcc -m32 -O0 -fno-stack-protector -z execstack control.c -o control

clean:
	rm -rf control

fuzz: vuln
	./fuzz.py > input && ./control

debug:
	edb --run control

edit:
	nano control.c

check:
	aspell -c readme.txt

.PHONY: clean vuln hack protect debug edit check

vuln:
	gcc -O0 -fno-stack-protector control.c -o control

clean:
	rm -rf control

fuzz:
	./fuzz.py | ./control

debug:
	edb --run control

edit:
	nano control.c

check:
	aspell -c readme.txt

.PHONY: clean vuln hack protect debug edit fixed

vuln:
	gcc -O0 -fno-stack-protector control.c -o control

clean:
	rm -rf control

hack:
	./hack.py | ./control

debug:
	edb --run control

edit:
	nano control.c

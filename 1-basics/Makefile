.PHONY: clean vuln hack protect debug edit fixed

vuln:
	gcc -O0 -fno-stack-protector overflow.c -o overflow

protect:
	gcc -O0 overflow.c -o overflow

fixed:
	gcc -O0 fixed.c -o fixed

clean:
	rm -rf overflow fixed

hack:
	./hack.py | ./overflow

debug:
	edb --run overflow

edit:
	nano overflow.c

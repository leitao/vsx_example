all:
	gcc -O0 -g vmx.c -o vec
	gcc -O0 -g vmx.c -DVMX -o vmx

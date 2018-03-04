all:
	gcc -O3 -maltivec -mvsx -g vmx.c -DVMX -o vmx

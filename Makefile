all: shell

shell: parser.c parser.h shell.c
	gcc -g -std=c99 -Wall -fsanitize=address,undefined -o shell parser.c parser.h shell.c

clean:
	rm -f shell
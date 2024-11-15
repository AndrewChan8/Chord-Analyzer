all: main

main: main.c
	gcc -g -o main main.c

clean:
	rm -f main test

test: test.c
	gcc -g -o test test.c

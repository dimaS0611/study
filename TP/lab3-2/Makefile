# Makefile for task3-2

check:
  shell: /usr/bin/bash -e {0}

distcheck:
  shell: /usr/bin/bash -e {0}

bin/basketball: build/main.o build/basketball.o
	gcc -o bin/basketball build/main.o build/basketball.o

build/main.o: src/main.c
	gcc -c src/main.c -o build/main.o

build/basketball.o: src/basketball.c
	gcc -c src/basketball.c -o build/basketball.o

clean:
	rm -f *.o bin/basketball

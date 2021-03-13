# Makefile task3-3

check:
  shell: /usr/bin/bash -e {0}

distcheck:
  shell: /usr/bin/bash -e {0}

bin/zoo: build/main.o build/zoo.o
	gcc -o bin/zoo build/main.o build/zoo.o

build/main.o: src/main.c
	gcc -c src/main.c -o build/main.o

build/zoo.o: src/zoo.c
	gcc -c src/zoo.c -o build/zoo.o

clean:
	rm -f *.o bin/zoo

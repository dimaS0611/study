# Makefile for CarFleet project lab5 group project

bin/CarFleet: build/main.o build/CarFleet.o build/sqlite3.o
	gcc -o bin/CarFleet build/main.o build/CarFleet.o build/sqlite3.o -lpthread -ldl

build/main.o: src/main.c
	gcc -c src/main.c -o build/main.o

build/CarFleet.o: src/CarFleet.c
	gcc -c src/CarFleet.c -o build/CarFleet.o

build/sqlite3.o: src/sqlite3.c
	gcc -c src/sqlite3.c -o build/sqlite3.o -lpthread -ldl

clean:
	rm -f *.o bin/CarFleet

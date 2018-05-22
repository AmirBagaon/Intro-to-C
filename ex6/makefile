#file: makefile

a.out : gadt.o main.o
	gcc gadt.o main.o

main.o : main.c gadt.h
	gcc -c main.c

gadt.o : gadt.c gadt.h
	gcc -c gadt.c
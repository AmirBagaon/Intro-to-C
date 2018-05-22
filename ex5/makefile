#file: makefile

a.out : Mission1.o Mission2.o Mission3.o Mission4.o Mission5.o Mission6.o main.o
	gcc Mission1.o Mission2.o Mission3.o Mission4.o Mission5.o Mission6.o main.o

main.o : main.c Mission1.h Mission2.h Mission3.h Mission4.h Mission5.h Mission6.h
	gcc -c main.c

Mission1.o : Mission1.c Mission1.h
	gcc -c Mission1.c

Mission2.o : Mission2.c Mission2.h
	gcc -c Mission2.c

Mission3.o : Mission3.c Mission3.h
	gcc -c Mission3.c

Mission4.o : Mission4.c Mission4.h
	gcc -c Mission4.c

Mission5.o : Mission5.c Mission5.h
	gcc -c Mission5.c

Mission6.o : Mission6.c Mission6.h
	gcc -c Mission6.c
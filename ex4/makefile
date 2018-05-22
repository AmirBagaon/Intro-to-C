#file: makefile

a.out : Translator.o Calculator.o ex4.o
	gcc Translator.o Calculator.o ex4.o

ex4.o : ex4.c Translator.h Calculator.h
	gcc -c ex4.c

Translator.o : Translator.c Translator.h
	gcc -c Translator.c

Calculator.o : Calculator.c Calculator.h
	gcc -c Calculator.c
CC=gcc -Wall

Assignment1: Assignment1.o Input.o Output.o Translate.o
	$(CC) -o Assignment1 Assignment1.o Input.o Output.o Translate.o

clean:
	rm -f *.o core.* Assignment1

Assignment1.o: Assignment1.c Shared.h
	$(CC) -c Assignment1.c
Input.o: Input.c Input.h
	$(CC) -c Input.c
Output.o: Output.c Output.h
	$(CC) -c Output.c
Translate.o: Translate.c Translate.h
	$(CC) -c Translate.c

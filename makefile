CC = gcc -Wall -pedantic

a.out: proj1.o
	$(CC)  -o a.out proj1.o

proj1.o: proj1.c
	$(CC)  -c proj1.c

clean:
	rm -rf *.o
	rm -rf a.out
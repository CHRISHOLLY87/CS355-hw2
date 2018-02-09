all: threads clean

threads: threads.o
	gcc -lpthread -o threads threads.o -lcheck

threads.o: threads.c
	gcc -c threads.c

clean:
	rm -rf *.o *.gch *.dSYM

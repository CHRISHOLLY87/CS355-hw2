all: mysh threads clean

mysh: mysh.o
	gcc -lpthread -o mysh mysh.o -lcheck

threads: threads.o
	gcc -lpthread -o threads threads.o -lcheck

mysh.o: mysh.c
	gcc -c -Wall mysh.c

threads.o: threads.c
	gcc -c -Wall threads.c

clean:
	rm -rf *.o *.gch *.dSYM mysh\ * threads\ *

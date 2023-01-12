all: main

main: main.o

main.o: main.c

clean:
	rm -f *.o main

.PHONY: all clean

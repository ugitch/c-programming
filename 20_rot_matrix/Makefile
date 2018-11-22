CFLAGS=-std=gnu99 -pedantic -Wall -Werror
rotate.o: rotate.c
	gcc -o rotate.o $(CFLAGS) -c rotate.c
rotate-matrix: read-matrix.o rotate.o
	gcc -o rotate-matrix $(CFLAGS) read-matrix.o rotate.o
.PHONY: clean
clean:
	rm -f rotate.o rotate-matrix output *~

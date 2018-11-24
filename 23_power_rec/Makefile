CFLAGS=-std=gnu99 -pedantic -Wall -Werror
power.o: power.c
	gcc -o power.o $(CFLAGS) -c power.c
test-power: test-power.c power.o
	gcc -o test-power $(CFLAGS) test-power.c power.o

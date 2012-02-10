.PHONY: all clean

all:
	gcc -o cbm main.c

clean:
	rm cbm

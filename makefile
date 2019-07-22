CC=gcc
CFLAGS=-g -Wall

all:	picker

picker:	picker.c
	$(CC) $(CFLAGS) -o picker picker.c

test:
	./picker

clean:
	rm -f *.o all
	rm -f *~ all
	rm -f *# all
	rm -f picker all

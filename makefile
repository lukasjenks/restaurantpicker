CC=gcc
CFLAGS=-g -Wall

all:	picker

picker:	picker.c picker.h
	$(CC) $(CFLAGS) -o $@ $^

test:
	./picker

clean:
	rm -f *.o all
	rm -f *~ all
	rm -f *# all
	rm -f picker all

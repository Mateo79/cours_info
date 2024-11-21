CC=gcc
CFLAGS= -D_REENTRANT

PRGS= fork thread1 thread2 thread3 thread4 thread5

all: $(PRGS)

fork: 
	$(CC) -o fork fork.c

.c: 
	$(CC) $(CFLAGS) -o $@ $@.c -lpthread -Wall

clean:
	rm -f $(PRGS) *~


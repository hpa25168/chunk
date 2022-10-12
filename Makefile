CFLAGS = -g -Wall
CC = gcc
HEADER = chunkFunction.h

# if make followed by no target then will compile 'Hello'
all: chunk

# before the "rm" there is only one white space character: a "TAB".
# If you have any  other white space this Makefile while not work

# before the "${CC}" there is only one white space character: a "TAB".
# If you have any  other white space this makefile while not work

chunk: chunk.o chunkFunction.h
	$(CC) $(CFLAGS) $@.c -o $@
#chunkFunction: chunkFunction.o

# generic
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f core *.o a.out
	rm -f parseargs
	rm -f DIRECTORY.html
	rm -rf *.dSYM
	rm -f chunk
	rm -f chunk2
webclean:
	rm -f DIRECTORY.html

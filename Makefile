# Makefile for tolocal

OBJS	= bmptobin.o replacepic.o changebyte.o

CC	= gcc
CFLAGS	= -O2

all:	bmptobin replacepic changebyte

bmptobin:	bmptobin.o
	$(CC) -o bmptobin bmptobin.o
	strip bmptobin

replacepic:	replacepic.o
	$(CC) -o replacepic replacepic.o
	strip replacepic

changebyte:	changebyte.o
	$(CC) -o changebyte changebyte.o
	strip changebyte


#install:	bmptobin replacepic changebyte
#	cp bmptobin /usr/local/bin
#	cp replacepic /usr/local/bin
#	cp changebyte /usr/local/bin
#	chmod a+x /usr/local/bin/bmptobin
#	chmod a+x /usr/local/bin/replacepic
#	cp bmptobin.1 /usr/local/share/man/man1
#	cp replacepic.1 /usr/local/share/man/man1
#	cp changebyte.1 /usr/local/share/man/man1

.o:
	$(CC) -i -c $@.c

clean:	
	@rm -rf *.o core bmptobin replacepic changebyte

OBJECT		=obj/device.o obj/print.o obj/main.o obj/server.o
CC			=gcc
CFLAGS		=-c -Iinclude -lpthread -w

all: bin/main

bin/main: $(OBJECT)
	$(CC) -o $@ $(OBJECT) -lpthread
obj/main.o: src/main.c include/device.h include/huffman.h
	$(CC) $(CFLAGS) -o $@ $<
obj/server.o: src/server.c include/server.h
	$(CC) $(CFLAGS) -o $@ $<
obj/device.o: src/device.c include/device.h
	$(CC) $(CFLAGS) -o $@ $<
obj/print.o: src/print.c include/print.h 
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm $(OBJECT) -rf
distclean: clean
	rm main -rf

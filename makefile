CC=g++
CFLAGS=-Wall -Werror
DEBUG=-g

build:
	$(CC) $(CFLAGS) main.cpp -o main

.PHONY : clean

clean:
	rm main

debug:
	rm main
	$(CC) $(DEBUG) $(CFLAGS) main.cpp -o main
	valgrind --leak-check=full ./main

run:
	./main
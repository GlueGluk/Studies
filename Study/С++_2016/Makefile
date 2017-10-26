CC=g++

test: main
	./main

clean :
	rm matrix.o
	rm main

matrix.o : matrix.cpp matrix.hpp
	$(CC) -c matrix.cpp -o matrix.o
main: main.cpp matrix.o
	$(CC) main.cpp matrix.o -o main

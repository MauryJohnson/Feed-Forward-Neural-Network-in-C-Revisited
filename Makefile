Matrix: Matrix.c
	gcc -g -Wall -lm -ldl Matrix.c -o Matrix
clean:
	rm Matrix

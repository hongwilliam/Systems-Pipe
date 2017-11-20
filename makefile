all: quick_pipe_maths.c
	gcc quick_pipe_maths.c

run: all
	./a.out

clean:
	rm *.o
	rm *~
	rm a.out

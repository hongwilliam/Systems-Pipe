all: forking.c
	gcc forking.c

run: all
	./a.out

clean:
	rm a.out

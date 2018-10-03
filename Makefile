all: parallel

parallel: parallel.c
	gcc -o parallel parallel.c

run: parallel
	./parallel

clean:
	rm -f parallel

FLAGS = -lpthread -lrt

all: parallel

parallel: parallel.c
	gcc -o parallel parallel.c $(FLAGS)

run: parallel
	./parallel

clean:
	rm -f parallel

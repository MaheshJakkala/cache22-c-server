
flags=-O2 -Wall -std=c2x
all: clean tree cache22

tree: tree.o
	cc ${flags} $^ -o $@ ${ldflags}
tree.o: tree.c
	cc ${flags} -c $^
cache22: cache22.o
	cc ${flags} $^ -o $@ ${ldflags}

cache22.o: cache22.c
	cc ${flags} -c $^

clean:
	rm -f *.o cache22
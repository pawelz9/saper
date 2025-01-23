CC = gcc


# Kompilacja końcowego programu
a.out: saper.o rysuj.o struct.o gra.o
	$(CC) -o a $^

# Reguły dla plików obiektowych
saper.o: saper.c gra.h struct.h rysuj.h
	$(CC)  -c saper.c

rysuj.o: rysuj.c rysuj.h struct.h
	$(CC)  -c rysuj.c

gra.o: gra.c gra.h struct.h rysuj.h
	$(CC)  -c gra.c

struct.o: struct.c struct.h
	$(CC) -c struct.c



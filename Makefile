CC = gcc
a.out: saper.o rysuj.o struct.o gra.o
	$(CC) $^

saper.o: gra.h struct.h
rysuj.o: rysuj.h struct.h
gra.o: gra.h struct.h
struct.o: struct.h

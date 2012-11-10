
build: libconfigiso.a 

libconfigiso.a: src/contextiso.c src/iso9660.h
	g++ -c src/contextiso.c -o contextiso.o
	ar rcs libconfigiso.a contextiso.o
	rm contextiso.o

clean:
	rm libconfigiso.a
	rm example

example: example.c libconfigiso.a
	g++ -o example example.c libconfigiso.a

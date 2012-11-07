
build: libconfigiso.a 

libconfigiso.a: src/contextiso.c
	g++ -c src/contextiso.c -o contextiso.o
	ar rcs libconfigiso.a contextiso.o
	rm contextiso.o

clean:
	rm libconfigiso.a

test: test.c libconfigiso.a
	g++ -o test test.c libconfigiso.a

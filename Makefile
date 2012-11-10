
build: libcontextiso.a 

static: libcontextiso.a

shared: libcontextiso.so.1.0.1

libcontextiso.a: src/contextiso.c src/iso9660.h
	g++ -c src/contextiso.c -o contextiso.o
	ar rcs libcontextiso.a contextiso.o
	rm contextiso.o

libcontextiso.so.1.0.1: src/contextiso.c src/iso9660.h
	g++ -c -fPIC src/contextiso.c -o contextiso.o
	g++ -shared -W1,-soname,libcontextiso.so.1 -o libcontextiso.so.1.0.1 contextiso.o
	ln -s libcontextiso.so.1.0.1 libcontextiso.so
	rm contextiso.o

clean:
	[ -f libcontextiso.a ] && rm libcontextiso.a || true
	[ -f libcontextiso.so.1.0.1 ] && rm libcontextiso.so.1.0.1 || true
	[ -L libcontextiso.so ] && rm libcontextiso.so || true
	[ -f example ] && rm example || true

example: example.c libcontextiso.a
	g++ -o example example.c libcontextiso.a

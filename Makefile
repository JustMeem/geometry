all: bin/geometry_project
hello: build/main.c build/shape.o build/strfuncs.o
	gcc -Wall build/*.o -o bin/geometry_project
build/main.o: main.c
	gcc -c main.c
build/shape.o: shape.c
	gcc -c shape.c
build/strfuncs.o: strfuncs.c
	gcc -c strfuncs.c
clean:
	rm -rf build/*.o
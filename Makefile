all: bin/geometry_project	
build/main.o: src/main.c
	gcc -c src/main.c
build/shape.o: src/shape.c
	gcc -c src/shape.c
build/strfuncs.o: src/strfuncs.c
	gcc -c src/strfuncs.c
bin/geometry_project: build/main.o build/shape.o build/strfuncs.o
	gcc -Wall build/*.o -o bin/geometry_project
clean:
	rm -rf build/*.o

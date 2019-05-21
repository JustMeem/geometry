all: bin/geometry_project	
build/main.o: src/main.c
	gcc -c src/main.c -o build/main.o
build/shape.o: src/shape.c
	gcc -c src/shape.c -o build/shape.o
build/strfuncs.o: src/strfuncs.c
	gcc -c src/strfuncs.c -o build/strfuncs.o
bin/geometry_project: build/main.o build/shape.o build/strfuncs.o
	gcc -Wall build/*.o -o bin/geometry_project -lm
.PHONY: clean
clean:
	rm -rf build/*.o

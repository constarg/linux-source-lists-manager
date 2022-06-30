object_files = ./build/io_m.o ./build/source_m.o 
header_loc = -I include/


all: dir_make ${object_files}
	gcc -Wall -g ${header_loc} ./src/main.c ${object_files} -o ./bin/source_file_manager

dir_make:
	mkdir -p ./bin/
	mkdir -p ./build/

./build/io_m.o: ./src/io_m.c
	gcc -Wall -g ${header_loc} -c ./src/io_m.c -o ./build/io_m.o

./build/source_m.o: ./src/source_m.c
	gcc -Wall -g ${header_loc} -c ./src/source_m.c -o ./build/source_m.o

clean:
	rm -rf ./build/

cleanall:
	rm -rf ./build/
	rm -rf ./bin/

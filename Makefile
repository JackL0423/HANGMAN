all: string_driver

string_driver: main.o my_string.o
	gcc -o string_driver main.o my_string.o


main.o: main.c
	gcc -c main.c


my_string.o: my_string.c
	gcc -c my_string.c


run:
	./string_driver

clean:
	@echo "cleaning all .o files and app"
	rm *.o string_driver

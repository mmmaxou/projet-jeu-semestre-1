all: compil
compil: main.o
	gcc main.o -o game -lm
	@echo Compilation finie
%.o: %.c
	gcc -c -Wall -ansi $<
clean:
	rm -R *.o
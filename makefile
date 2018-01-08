all: compil
compil: main.o
	gcc main.o -o game.exe
	@echo Compilation finie
%.o: %.c
	gcc -c -Wall -ansi $<
clean:
	rm -R *.o
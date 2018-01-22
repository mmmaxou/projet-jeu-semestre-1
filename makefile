# Variables

src_dir = src
obj_dir = obj

_OBJECTS = main.o UListe.o Monde.o Unite.o Affichage.o Utils.o Sauvegarde.o
OBJECTS = $(patsubst %,$(obj_dir)/%,$(_OBJECTS))

# Compiler

all: compil
compil: $(OBJECTS)
	gcc $(OBJECTS) -o game.exe
	@echo Compilation finie
$(obj_dir)/%.o: $(src_dir)/%.c
	gcc -c -Wall -ansi $< -o $@
clean:
	rm -f obj/*.o
# Variables

src_dir = src
obj_dir = obj

_OBJECTS = main.o UListe.o Monde.o Unite.o Affichage.o AffichageMLV.o Utils.o
OBJECTS = $(patsubst %,$(obj_dir)/%,$(_OBJECTS))

CFLAGS = -c -ansi -g -O2 -Wall -Werror `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`


# Compiler

all: compil
compil: $(OBJECTS)
	gcc $(OBJECTS) $(LDLIBS) -o game.exe
	@echo Compilation finie
$(obj_dir)/%.o: $(src_dir)/%.c
	gcc $(CFLAGS) $< -o $@
clean:
	del /S *.o
NAME=ogs
HEADERS=defines.h ogs_fmw.h ogs_window.h ogs_defines.h
OBJFILES=ogs_menu.o ogs_fmw.o ogs_window.o

FLAGS=-std=c99 -Wall -Wextra -pedantic
LIBS=-lSDL -lSDL_gfx

build:$(NAME)
all:$(NAME)

$(NAME):$(OBJFILES)
	gcc $(FLAGS) $(OBJFILES) $(LIBS) -o $(NAME)

$(OBJFILES):$(HEADERS)

ogs_menu.o:ogs_menu.c
	gcc $(FLAGS) ogs_menu.c -c

ogs_fmw.o:ogs_fmw.c
	gcc $(FLAGS) ogs_fmw.c -c

ogs_window.o:ogs_window.c
	gcc $(FLAGS) ogs_window.c -c

clean:
	rm -f $(NAME) $(OBJFILES)

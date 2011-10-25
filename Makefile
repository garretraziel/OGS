NAME=ogs
HEADERS=defines.h ogs_fmw.h ogs_window.h ogs_defines.h ogs_list.h ogs_objects.h ogs_draw.h
OBJFILES=ogs_menu.o ogs_fmw.o ogs_window.o ogs_list.o ogs_objects.o ogs_draw.o

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

ogs_list.o:ogs_list.c
	gcc $(FLAGS) ogs_list.c -c

ogs_objects.o:ogs_objects.c
	gcc $(FLAGS) ogs_objects.c -c

ogs_draw.o:ogs_draw.c
	gcc $(FLAGS) ogs_draw.c -c

clean:
	rm -f $(NAME) $(OBJFILES)

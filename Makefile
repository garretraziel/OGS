NAME=ogs-menu
HEADERS=defines.h ogs/ogs_fmw.h ogs/ogs_defines.h ogs/ogs_list.h ogs/ogs_objects.h ogs/ogs_draw.h
OBJFILES=ogs_menu.o ogs/ogs_fmw.o ogs/ogs_list.o ogs/ogs_objects.o ogs/ogs_draw.o

CFLAGS=-std=c99 -Wall -Wextra -pedantic
DFLAGS=-g
LIBS=-lSDL -lSDL_gfx
CC=gcc

Release:all
Debug:CFLAGS += -g
Debug:all
build:$(NAME)
all:$(NAME)

$(NAME):$(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBS) -o $(NAME)

$(OBJFILES):$(HEADERS)

clean:
	rm -f $(NAME) ogs/$(OBJFILES) ogs_menu.o

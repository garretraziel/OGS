NAME=ogs-menu
HEADERS=defines.h ogs_fmw/ogs_fmw.h ogs_fmw/ogs_defines.h ogs_fmw/ogs_list.h ogs_fmw/ogs_objects.h ogs_fmw/ogs_draw.h ogs_fmw/ogs_input.h
OBJFILES=ogs_menu.o ogs_fmw/ogs_fmw.o ogs_fmw/ogs_list.o ogs_fmw/ogs_objects.o ogs_fmw/ogs_draw.o ogs_fmw/ogs_input.o

CFLAGS=-std=c99 -Wall -Wextra -pedantic -lm
DFLAGS=-g
LIBS=-lSDL -lSDL_gfx -lSDL_image
CC=gcc

Release:all
debug:Debug
Debug:CFLAGS += -g
Debug:all
build:$(NAME)
all:$(NAME)

$(NAME):$(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBS) -o $(NAME)

$(OBJFILES):$(HEADERS)

clean:
	rm -f $(NAME) $(OBJFILES)

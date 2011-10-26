NAME=ogs
HEADERS=defines.h ogs_fmw.h ogs_defines.h ogs_list.h ogs_objects.h ogs_draw.h
OBJFILES=ogs_menu.o ogs_fmw.o ogs_list.o ogs_objects.o ogs_draw.o

CFLAGS=-std=c99 -Wall -Wextra -pedantic
DFLAGS=-std=c99 -Wall -Wextra -pedantic -g
LIBS=-lSDL -lSDL_gfx
CC=llvm-clang

Debug:CFLAGS += -g
Debug:all
Release:all
build:$(NAME)
all:$(NAME)

$(NAME):$(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBS) -o $(NAME)

$(OBJFILES):$(HEADERS)

clean:
	rm -f $(NAME) $(OBJFILES)

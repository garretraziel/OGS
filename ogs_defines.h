#ifndef __OGS_DEFINES_H__
#define __OGS_DEFINES_H__

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

enum {
  OGS_FULLSCREEN, OGS_WINDOWED,
} OGS_WIN_MODES;

enum {
  OGS_ABS, OGS_REL,
} OGS_CONTROL_MODE;

typedef struct {
  int width;
  int height;
} OGS_RES;

enum {
  OGS_OK, OGS_INIT_ERROR, OGS_NOMEM_ERROR, OGS_SDL_ERROR,
} OGS_ERRORS;

enum {
  OGS_WINDOW, OGS_BUTTON, OGS_INPUTF, OGS_INFO, OGS_TEXTARRAY, OGS_PICTURE,
} OGS_OBJECTS;

typedef struct OGS_LIST_ITEM {
  int type;
  OGS_RES position;
  void *item;
  struct OGS_LIST_ITEM *next;
} *OGS_LIST_PITEM;

typedef struct OGS_WINDOW_S {
  OGS_RES position;
  OGS_RES size;
  int pos_type;
  OGS_LIST_PITEM items;
  //...
} *OGS_PWINDOW_S;

typedef struct OGS_BUTTON_S {
  OGS_RES position;
  OGS_RES size;
  OGS_RES caption;
  void *function_execute;
} *OGS_PBUTTON_S;

typedef struct {
  SDL_Surface *screen;
  OGS_LIST_PITEM items;
  OGS_LIST_PITEM top;
  OGS_LIST_PITEM bot;
  OGS_LIST_PITEM act;
} OGS_SCREEN;

#endif

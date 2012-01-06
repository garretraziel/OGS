#ifndef __OGS_DEFINES_H__
#define __OGS_DEFINES_H__

#include <SDL/SDL.h>

enum {
    OGS_FULLSCREEN, OGS_WINDOWED,
} OGS_WIN_MODES; // modes of window - fullscreen or windowed

enum {
    OGS_ABS, OGS_REL,
} OGS_POSITION_MODE; // modes of position - absolute or relative to size

enum {
    OGS_BMP, OGS_PNG, OGS_JPEG,
} OGS_PICTURE_TYPE; // types of picture - bmp, png or jpeg

enum {
    OGS_NOEVENT, OGS_QUIT, OGS_KEYLEFT, OGS_KEYRIGHT,
    OGS_KEYDOWN, OGS_KEYUP, OGS_ENTER,
} OGS_EVENTS; // types of event in ogs

enum {
    OGS_OK, // everything went better than expected
    OGS_INIT_ERROR, // error while init of OGS
    OGS_NOMEM_ERROR, // not enought memory error
    OGS_SDL_ERROR, // error with SDL
    OGS_FILE_ERROR, // error while operating with files
} OGS_ERRORS; // types of error from program

enum {
    OGS_WINDOW, // window object
    OGS_BUTTON, // button object
    OGS_INPUTF, // input field object
    OGS_INFO, // info message object
    OGS_TEXTARRAY, // text object
    OGS_PICTURE, // picture object
} OGS_OBJECTS; // objects usable on screen

typedef struct {
    int width;
    int height;
} OGS_RES; // structure for x and y coordinates

typedef struct OGS_LIST_ITEM {
    int type; // type of item from OGS_OBJECTS
    void *item; // pointer to struct of this object
    struct OGS_LIST_ITEM *next; // next object in list
    struct OGS_LIST_ITEM *up; // object that is up from this object
    struct OGS_LIST_ITEM *down; // object that is down from this object
    struct OGS_LIST_ITEM *left; // object that is left from this object
    struct OGS_LIST_ITEM *right; // object that is right from this object
} *OGS_LIST_PITEM; // abstract one item of list

typedef struct OGS_LIST {
    OGS_LIST_PITEM top; // top of list
    OGS_LIST_PITEM bot; // bottom of list
    OGS_LIST_PITEM act; // actual item in list
} *OGS_PLIST;

typedef struct OGS_WINDOW_S {
    OGS_RES position; // position of window
    OGS_RES size; // size of window
    int pos_type; // position type inside window (ABS or REL)
    int fullscreen; // if is window covering whole screen
    OGS_PLIST items; // list of items in this window
    //...
} *OGS_PWINDOW_S; // object of main window

typedef struct OGS_BUTTON_S {
    OGS_RES position; // position of button
    OGS_RES size; // size of button
    char *caption; // what is written on that button
    void (*function_execute)(void); // pointer to function that must be executed while is button clicked
    int enabled; // if is button enabled
    int clicked; // if was button clicked
} *OGS_PBUTTON_S; // object of button

typedef struct OGS_INPUTF_S {
    OGS_RES position; // position of input field
    OGS_RES size; // trololo
    char *text; // text in input field
    int textsize; // size of text
    int font; // font of text
    int enabled; // is inputfield enabled
} *OGS_PINPUTF_S; // object of input field

typedef struct OGS_INFO_S {
    OGS_RES position; // position of info message
    OGS_RES size; // size of info message
    char *text; // text in info message
    int covers_all; // if info message covers whole screen
    int text_size; // size of text
    int font; // font used for text
} *OGS_PINFO_S; // object of info message

typedef struct OGS_TEXTARRAY_S {
    OGS_RES position; // position of text array
    OGS_RES size; // trololo
    char *text; // text in text array
    int textsize; // size of text
    int font; // font of text
} *OGS_PTEXTARRAY_S; // object of text array

typedef struct OGS_GENERIC_ITEM_S { // generic type for getting position
    OGS_RES position; // position of item
    OGS_RES size; // size of item
} * OGS_PGENERIC_ITEM_S;

typedef struct OGS_PICTURE_S {
    OGS_RES position; // position of picture
    OGS_RES size; // size of picture
    int type; // type of picture (BMP, JPEG, PNG...)
    SDL_Surface *image; // picture itself
} *OGS_PPICTURE_S; // object of picture

typedef struct OGS_SCREEN{
    SDL_Surface *screen; // SDL surface
    OGS_RES resolution; // resolution of screen
    OGS_PLIST list; // list of windows
} *OGS_PSCREEN; // object representing whole screen

// COLORS:

#define WHITE 0xffffffff
#define RED 0xff0000ff
#define BLACK 0x00000000
#define YELLOW 0xffff00ff
#define PURPLE 0xff00ffff
#define BLUE 0x00ffffff
#define DARKBLUE 0x0000ffff
#define LIGHTBLUE 0x57c4ffff
#define GREEN 0x00ff00ff
#define WINDOW_C 0xdcdcf0ff
#define SILVER 0xd8e2e7ff


#endif

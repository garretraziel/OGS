#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    srand(time(NULL));

    SDL_Surface *screen = SDL_SetVideoMode(800,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    if (screen == NULL) return -1;

    atexit(SDL_Quit);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x38, 0x1a, 0x0e));

    printf("%x\n",SDL_MapRGBA(screen->format, 0x61, 0xc6, 0xd0, 0xff));

    boxRGBA(screen, 100, 100, 500, 500, 0x61, 0xc6, 0xd0, 0xff);

    for (int i = 0; i<2; i++) {
        rectangleRGBA(screen, 100+i,100+i, 500-i, 500-i, 0x00,0x00,0x00,0xdd-(rand()%3));
    }

    /* for (int i = 0; i<10; i++) { */
    /*     rectangleRGBA(screen,102+i,102+i,498-i,498-i,0x00,0x00,0x00,0xaa); */
    /* } */

    /* for (int i = 0; i<30; i++) { */
    /*     rectangleRGBA(screen,102+i+rand()%2,102+i+rand()%2,498-i-rand()%2,498-i-rand()%2,0x00,0x00,0x00,abs(0x5a-(3*i+rand()%2))); */
    /* } */
    
    SDL_Flip(screen);

    getchar();
    return 0;
}

#include "SDL2\SDL.h"
#include <iostream>
#include <string.h>

using namespace std;

int Random_Range(int min, int max) {
    return min + rand() % (max+1 - min);
}

int main( int argc, char* args[] ) {
    const int ScreenWidth = 800;//1920;
    const int ScreenHeight = 600;//1080;
    const bool FullScreen = false; // set to true for full screen madness!
    SDL_Event event;

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Conway's Game of Life (SDL2)", 50, 50, ScreenWidth, ScreenHeight, 0);

    if (FullScreen) {
        Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
        bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
        SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
        SDL_ShowCursor(IsFullscreen);
    }

    //Create SDL2 stuff
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, ScreenWidth, ScreenHeight);
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_PixelFormat* myPixelFormat = surface->format;

    //Two pixel arrays for working and new screen
    Uint32* pixels_a = new Uint32[ScreenWidth * ScreenHeight];
    Uint32* pixels_b = new Uint32[ScreenWidth * ScreenHeight];

    // Alive pixel and dead pixel constants
    const Uint32 ALIVE = SDL_MapRGB(myPixelFormat, 128, 255, 128); //Color for live cells (lime green)
    const Uint32 DEAD = 0; //Black - dead cells, note: this needs to be 0 or the math won't work

    // Initialize arrays with DEAD
    memset(pixels_a, DEAD, ScreenWidth * ScreenHeight * sizeof(Uint32));
    memset(pixels_b, DEAD, ScreenWidth * ScreenHeight * sizeof(Uint32));

    //Pandom pixels across entire screen
    for(int i=0;i < ScreenWidth * ScreenHeight; i++)
        if (Random_Range(0,2) == 1)
            pixels_b[i] = ALIVE;

    bool Graphing = true;
    while (Graphing) {
        //Swap old frame to new frame and clear
        memcpy(pixels_a, pixels_b, ScreenWidth * ScreenHeight * sizeof(Uint32)); // copy pixels_b --> pixels_a
        memset(pixels_b, DEAD, ScreenWidth * ScreenHeight * sizeof(Uint32)); // clear pixels_b

        //SDL presentation calls
        SDL_UpdateTexture(texture, NULL, pixels_a, ScreenWidth * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        //Apply life rules
        for(int x=1;x<=ScreenWidth-2;x++)
            for(int y=1;y<=ScreenHeight-2;y++) {
                //Add up all the pixel's neighbors. x & y coordinate converted with offsets for 1 dimensional pixel array
                int NeighborCount = (pixels_a[(y-1) * ScreenWidth + (x-1)] +
                                     pixels_a[(y-1) * ScreenWidth + x] +
                                     pixels_a[(y-1) * ScreenWidth + (x+1)] +

                                     pixels_a[y * ScreenWidth + (x-1)] +
                                     pixels_a[y * ScreenWidth + (x+1)] +

                                     pixels_a[(y+1) * ScreenWidth + (x-1)] +
                                     pixels_a[(y+1) * ScreenWidth + x] +
                                     pixels_a[(y+1) * ScreenWidth + (x+1)]) / ALIVE;
                //DO THE RULES!----------------------------------------------------------
                //if the pixel is currently alive
                if (pixels_a[y * ScreenWidth + x] == ALIVE) {
                    //the pixel neighbor count is 2 or 3 then it stays alive
                    if (NeighborCount == 2 || NeighborCount == 3)
                        pixels_b[y * ScreenWidth + x] = ALIVE;
                    //otherwise it is death by loneliness or overcrowding
                    else
                        pixels_b[y * ScreenWidth + x] = DEAD;
                }
                //the current pixel must be dead, so ...
                //  if there are 3 neighbors a new life is born!
                else if (NeighborCount==3)
                    pixels_b[y * ScreenWidth + x] = ALIVE;
            }

        //Check for Escape Pressed
        while(SDL_PollEvent(&event) != 0)
            if (event.key.keysym.sym == SDLK_ESCAPE)
                Graphing = false;
    } //while(Graphing)

    //Clean up, clean up, everybody clean up!
    delete[] pixels_a;
    delete[] pixels_b;

    SDL_ShowCursor(SDL_ENABLE);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

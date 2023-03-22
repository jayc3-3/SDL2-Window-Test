#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int main(void)
{
    SDL_Event SDLEvent;

    SDL_Color White;

    SDL_Surface *TextSurface;
    SDL_Surface *BackgroundSurface;

    SDL_Texture *TextTexture;
    SDL_Texture *BackgroundTexture;

    SDL_Rect TextRect;
    SDL_Rect BackgroundRect;

    TTF_Font *Arial;

    int Running = 1;
    const int ScreenWidth = 1280;
    const int ScreenHeight = 720;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    SDL_Window *Window = SDL_CreateWindow("C & SDL2 Window Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                            ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
                                            
    SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_RenderSetLogicalSize(Renderer, ScreenWidth, ScreenHeight);

    White = (SDL_Color){255, 255, 255};

    Arial = TTF_OpenFont("Arial.TTF", 50);

    TextSurface = TTF_RenderText_Solid(Arial, "This was made with SDL2 in C!", White);
    BackgroundSurface = IMG_Load("background.png");

    TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
    BackgroundTexture = SDL_CreateTextureFromSurface(Renderer, BackgroundSurface);

    TextRect.x = ((ScreenWidth / 2) - (TextSurface->w / 2));
    TextRect.y = ((ScreenHeight / 2) - (TextSurface->h / 2));
    TextRect.w = TextSurface->w;
    TextRect.h = TextSurface->h;

    BackgroundRect.w = BackgroundSurface->w;
    BackgroundRect.h = BackgroundSurface->h;
    
    while(Running)
    {
        while(SDL_PollEvent(&SDLEvent))
        {
            if(SDLEvent.type == SDL_QUIT)
            {
                Running = 0;
                break;
            }
        }

        SDL_RenderClear(Renderer);

        SDL_RenderCopy(Renderer, BackgroundTexture, NULL, &BackgroundRect);
        SDL_RenderCopy(Renderer, TextTexture, NULL, &TextRect);

        SDL_RenderPresent(Renderer);
    }

    TTF_CloseFont(Arial);

    SDL_FreeSurface(TextSurface);
    SDL_FreeSurface(BackgroundSurface);

    SDL_DestroyTexture(TextTexture);
    SDL_DestroyTexture(BackgroundTexture);

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

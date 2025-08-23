#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Ex-1.2.1",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0, 255, 255, 0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 18, 166, 18, 0x00);
    SDL_Rect chao = {0, 100, 500, 100};
    SDL_RenderFillRect(ren, &chao);
    SDL_SetRenderDrawColor(ren, 000, 000, 255, 0x00);
    SDL_Rect place_holder = {70, 60, 40, 40};
    SDL_RenderFillRect(ren, &place_holder);
    SDL_SetRenderDrawColor(ren, 255, 255, 0, 0x00);
    SDL_Rect sol = {450, 0, 50, 50};
    SDL_RenderFillRect(ren, &sol);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

#include <assert.h>
#include <SDL2/SDL.h>
#include <stdio.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Contando o Tempo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r1 = { 40,20, 10,10 };
    SDL_Rect r2 = { 50, 30, 10, 10};
    SDL_Rect r3 = { 80, 90, 10, 10};
    int espera = 500;
    int quit = 0;
    int x, y;
    Uint32 btos;

    while (quit == 0) {

        //printf("posição do mouse X %d", x);
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r1);
        SDL_RenderPresent(ren);
        SDL_SetRenderDrawColor(ren, 255, 000, 000, 000);
        SDL_RenderFillRect(ren, &r2);
        SDL_RenderPresent(ren);
        SDL_SetRenderDrawColor(ren, 000, 255, 000, 000);
        SDL_RenderFillRect(ren, &r3);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, espera);
        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) {
                espera = 0;
            }
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        r2.y -= 5;
                        break;
                    case SDLK_DOWN:
                        r2.y += 5;
                        break;
                    case SDLK_LEFT:
                        r2.x -= 5;
                        break;
                    case SDLK_RIGHT:
                        r2.x += 5;
                        break;
                    //aperte esc para sair
                    case SDLK_ESCAPE:
                        quit++;
                        break;
                }
            }

            btos = SDL_GetMouseState(&x, &y);
            if (btos & SDL_BUTTON_LMASK) {
                    r3.x = x;
                    r3.y = y;
                }

        } else {
            espera = 500;
            r1.x += 2;
            r1.y += 2;
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

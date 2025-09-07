#include <SDL2/SDL.h>
#include <stdio.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao Simples",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUCAO */
    int stop = 0;
    SDL_Rect r = { 0,0, 10,10 };
    SDL_Rect b = { 50, 50, 10, 10};
    int espera = 500;
    int contador = 0;
    while (stop == 0) {

        SDL_Event sair;
        Uint32 antes = SDL_GetTicks();


        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00,0x00);
        SDL_RenderFillRect(ren, &b);
        SDL_RenderPresent(ren);

        int isevt = SDL_WaitEventTimeout(&sair, espera);
        if(isevt){
            espera -= (SDL_GetTicks() - antes);
            if(sair.type == SDL_KEYDOWN){
                switch(sair.key.keysym.sym){

                    case SDLK_UP:
                        r.y -= 10;
                        break;

                    case SDLK_DOWN:
                        r.y += 10;
                        break;

                    case SDLK_LEFT:
                        r.x -= 10;
                        break;

                    case SDLK_RIGHT:
                        r.x += 10;
                        break;

                    default:
                        stop++;
                        break;
                }
            }

            if(SDL_HasIntersection(&r, &b)){
                contador++;
                printf("\n%d\n", contador);
            }
        }
        else{
            espera = 500;
            //r.x += 10;
            //r.y += 10;
        }

    }
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}

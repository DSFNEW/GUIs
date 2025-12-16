#include <assert.h>
#include <SDL2/SDL.h>

int main(int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Contando o Tempo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r = { 0, 0, 10, 10 };  // Começa no canto superior esquerdo
    int espera = 100;  // 100ms = 10 pixels por segundo (100ms * 10 = 1000ms = 1 segundo)
    int direcao = 0;   // 0=baixo-direita, 1=baixo-esquerda, 2=cima-esquerda, 3=cima-direita

    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, &r);
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
                        r.y -= 5;
                        break;
                    case SDLK_DOWN:
                        r.y += 5;
                        break;
                    case SDLK_LEFT:
                        r.x -= 5;
                        break;
                    case SDLK_RIGHT:
                        r.x += 5;
                        break;
                }
            } else if (evt.type == SDL_QUIT) {
                break;
            }
        } else {
            // Movimento automático: 10 pixels por segundo
            // Como espera = 100ms, movemos 1 pixel a cada ciclo
            switch (direcao) {
                case 0: // Baixo-direita
                    r.x += 1;
                    r.y += 1;
                    break;
                case 1: // Baixo-esquerda
                    r.x -= 1;
                    r.y += 1;
                    break;
                case 2: // Cima-esquerda
                    r.x -= 1;
                    r.y -= 1;
                    break;
                case 3: // Cima-direita
                    r.x += 1;
                    r.y -= 1;
                    break;
            }

            // Verifica limites e muda direção
            if (r.x >= 190) {  // Limite direito (200 - 10)
                if (direcao == 0) direcao = 1;
                if (direcao == 3) direcao = 2;
            }
            if (r.x <= 0) {    // Limite esquerdo
                if (direcao == 1) direcao = 0;
                if (direcao == 2) direcao = 3;
            }
            if (r.y >= 90) {   // Limite inferior (100 - 10)
                if (direcao == 0) direcao = 3;
                if (direcao == 1) direcao = 2;
            }
            if (r.y <= 0) {    // Limite superior
                if (direcao == 2) direcao = 1;
                if (direcao == 3) direcao = 0;
            }

            espera = 100;  // Mantém o tempo constante para movimento de 10px/segundo
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

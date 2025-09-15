#include <assert.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char* args[]) {
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* win = SDL_CreateWindow("Contando o Tempo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         800, 200, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* Variáveis de texto */
    TTF_Font* fnt = NULL;
    SDL_Texture* txt = NULL;
    int texto_visivel = 0;
    Uint32 tempo_chegada = 0;
    int reiniciar = 0;

    /* Posições iniciais */
    SDL_Rect r1_inicial = {40, 20, 10, 10};
    SDL_Rect r2_inicial = {50, 30, 10, 10};
    SDL_Rect r3_inicial = {80, 90, 10, 10};
    SDL_Rect chegada = {700, 0, 100, 200};

    /* EXECUÇÃO */
    SDL_Rect r1 = r1_inicial;
    SDL_Rect r2 = r2_inicial;
    SDL_Rect r3 = r3_inicial;
    int espera = 500;
    int quit = 0;

    while (!quit) {
        /* Processa eventos */
        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, espera);

        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) espera = 0;

            if (evt.type == SDL_QUIT) {
                quit = 1;
            }
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {

                    case SDLK_LEFT: r2.x -= 5; break;
                    case SDLK_RIGHT: r2.x += 5; break;
                    case SDLK_ESCAPE: quit = 1; break;
                    case SDLK_r: // Tecla R para reiniciar manualmente
                        reiniciar = 1;
                        break;
                }
            }
            if (evt.type == SDL_MOUSEMOTION) {
                // Move o bloco verde com o mouse
                r3.x = evt.motion.x;
            }
        } else {
            espera = 500;
            r1.x += 10;
        }

        /* Verifica colisões - se qualquer bloco encostar na chegada */
        if (SDL_HasIntersection(&r1, &chegada) ||
            SDL_HasIntersection(&r2, &chegada) ||
            SDL_HasIntersection(&r3, &chegada)) {
            if (!texto_visivel) {
                fnt = TTF_OpenFont("tiny.ttf", 20);
                if (fnt) {
                    SDL_Color clr = {0xFF, 0x00, 0x00, 0xFF};
                    SDL_Surface* sfc = TTF_RenderText_Blended(fnt, "Chegou! Reiniciando...", clr);
                    txt = SDL_CreateTextureFromSurface(ren, sfc);
                    SDL_FreeSurface(sfc);
                    texto_visivel = 1;
                    tempo_chegada = SDL_GetTicks();
                }
            }
        }

        /* Reinicia o jogo após 2 segundos */
        if (texto_visivel && (SDL_GetTicks() - tempo_chegada > 2000)) {
            reiniciar = 1;
        }

        /* Reinicia o jogo */
        if (reiniciar) {
            // Reseta as posições dos blocos
            r1 = r1_inicial;
            r2 = r2_inicial;
            r3 = r3_inicial;

            // Limpa o texto
            if (txt) {
                SDL_DestroyTexture(txt);
                txt = NULL;
            }
            if (fnt) {
                TTF_CloseFont(fnt);
                fnt = NULL;
            }
            texto_visivel = 0;
            reiniciar = 0;
        }

        /* Renderização */
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);

        // Desenha a linha de chegada (retângulo preto)
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        SDL_RenderFillRect(ren, &chegada);

        // Desenha os blocos
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, &r1);

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
        SDL_RenderFillRect(ren, &r2);

        SDL_SetRenderDrawColor(ren, 0, 255, 0, 0);
        SDL_RenderFillRect(ren, &r3);

        /* Desenha texto se visível */
        if (texto_visivel) {
            SDL_Rect text_rect = {300, 80, 200, 40};
            SDL_RenderCopy(ren, txt, NULL, &text_rect);
        }

        SDL_RenderPresent(ren);
    }

    /* FINALIZACAO */
    if (txt) SDL_DestroyTexture(txt);
    if (fnt) TTF_CloseFont(fnt);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

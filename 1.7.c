#include <SDL2/SDL.h>
#include <stdio.h>

int AUX_WaitEventTimeout(SDL_Event* evt, Uint32* ms) {
    Uint32 start = SDL_GetTicks();
    int ret = SDL_WaitEventTimeout(evt, *ms);
    Uint32 elapsed = SDL_GetTicks() - start;

    if (elapsed >= *ms) {
        *ms = 0;
    } else {
        *ms -= elapsed;
    }

    return ret;
}

int main(int argc, char* args[]) {
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao com Spritesheet",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 300, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* CARREGAMENTO DA IMAGEM */
    SDL_Surface* surface = SDL_LoadBMP("spritesheet.bmp");
    if (!surface) {
        printf("Erro ao carregar spritesheet.bmp: %s\n", SDL_GetError());
        // Criando uma superfície de fallback (tirinha colorida)
        surface = SDL_CreateRGBSurface(0, 320, 40, 32, 0, 0, 0, 0);
        if (surface) {
            // Preenche com quadrados coloridos (8 frames)
            for (int i = 0; i < 8; i++) {
                SDL_Rect rect = {i * 40, 0, 40, 40};
                Uint32 color;
                switch (i % 4) {
                    case 0: color = SDL_MapRGB(surface->format, 255, 0, 0); break;   // Vermelho
                    case 1: color = SDL_MapRGB(surface->format, 0, 255, 0); break;   // Verde
                    case 2: color = SDL_MapRGB(surface->format, 0, 0, 255); break;   // Azul
                    case 3: color = SDL_MapRGB(surface->format, 255, 255, 0); break; // Amarelo
                }
                SDL_FillRect(surface, &rect, color);
            }
        }
    }

    SDL_Texture* spriteSheet = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);

    if (!spriteSheet) {
        printf("Erro ao criar textura: %s\n", SDL_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    /* EXECUCAO */
    int stop = 0;
    int frameWidth = 40;   // Largura de cada frame
    int frameHeight = 40;  // Altura de cada frame
    int totalFrames = 8;   // Total de frames na spritesheet
    int currentFrame = 0;  // Frame atual

    SDL_Rect srcRect = {0, 0, frameWidth, frameHeight}; // Recorte da spritesheet
    SDL_Rect destRect = {100, 100, frameWidth * 2, frameHeight * 2}; // Posição e escala na tela

    SDL_Rect obstacle = {200, 150, 30, 30}; // Obstáculo

    Uint32 loopDelay = 20;   // Loop principal rápido (20ms = 50 FPS)
    Uint32 animationDelay = 100; // Animação lenta (100ms = 10 FPS)
    Uint32 lastAnimationTime = 0; // Último tempo de atualização da animação
    Uint32 currentTime;

    int contador = 0;

    while (stop == 0) {
        currentTime = SDL_GetTicks();

        /* ATUALIZAÇÃO DA ANIMAÇÃO (mais lenta) */
        if (currentTime - lastAnimationTime >= animationDelay) {
            currentFrame = (currentFrame + 1) % totalFrames;
            srcRect.x = currentFrame * frameWidth;
            lastAnimationTime = currentTime;
        }

        /* PROCESSAMENTO DE EVENTOS */
        SDL_Event event;
        Uint32 waitTime = loopDelay;

        // Usa nossa função auxiliar para espera
        while (AUX_WaitEventTimeout(&event, &waitTime)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        destRect.y -= 10;
                        break;
                    case SDLK_DOWN:
                        destRect.y += 10;
                        break;
                    case SDLK_LEFT:
                        destRect.x -= 10;
                        break;
                    case SDLK_RIGHT:
                        destRect.x += 10;
                        break;
                    case SDLK_ESCAPE:
                        stop = 1;
                        break;
                }

                // Verifica colisão
                if (SDL_HasIntersection(&destRect, &obstacle)) {
                    contador++;
                    printf("Colisoes: %d\n", contador);
                }
            } else if (event.type == SDL_QUIT) {
                stop = 1;
            }
        }

        /* RENDERIZAÇÃO (executada a cada loop rápido) */
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);

        // Desenha o sprite animado
        SDL_RenderCopy(ren, spriteSheet, &srcRect, &destRect);

        // Desenha o obstáculo
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(ren, &obstacle);

        // Desenha informações na tela
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);
        SDL_Rect infoBg = {10, 10, 200, 60};
        SDL_RenderFillRect(ren, &infoBg);

        SDL_RenderPresent(ren);
    }

    /* FINALIZACAO */
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

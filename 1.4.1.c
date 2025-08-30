#include <SDL2/SDL.h>

#define MAX_RECTS 10

int main(int argc, char* argv[]) {
    // Inicialização
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Retângulos", 100, 100, 400, 300, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    // Variáveis
    SDL_Rect r = { 180, 120, 40, 40 }; // Retângulo móvel
    SDL_Rect fixos[MAX_RECTS];          // Retângulos fixos
    int qtd = 0;                        // Quantidade de retângulos
    SDL_Event e;

    // Loop principal
    while (1) {
        // Renderização
        SDL_SetRenderDrawColor(ren, 240, 240, 240, 255);
        SDL_RenderClear(ren);

        // Desenha retângulos fixos (vermelhos)
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        for (int i = 0; i < qtd; i++) {
            SDL_RenderFillRect(ren, &fixos[i]);
        }

        // Desenha retângulo móvel (azul)
        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        SDL_RenderFillRect(ren, &r);

        SDL_RenderPresent(ren);

        // Eventos
        SDL_WaitEvent(&e);
        if (e.type == SDL_QUIT) break;

        if (e.type == SDL_MOUSEBUTTONDOWN && qtd < MAX_RECTS) {
            fixos[qtd].x = e.button.x - 15;
            fixos[qtd].y = e.button.y - 15;
            fixos[qtd].w = 30;
            fixos[qtd].h = 30;
            qtd++;
        }

        if (e.type == SDL_KEYDOWN) {
            // Movimento
            if (e.key.keysym.sym == SDLK_UP) r.y -= 10;
            if (e.key.keysym.sym == SDLK_DOWN) r.y += 10;
            if (e.key.keysym.sym == SDLK_LEFT) r.x -= 10;
            if (e.key.keysym.sym == SDLK_RIGHT) r.x += 10;

            // Limites da tela
            if (r.x < 0) r.x = 0;
            if (r.y < 0) r.y = 0;
            if (r.x > 400 - r.w) r.x = 400 - r.w;
            if (r.y > 300 - r.h) r.y = 300 - r.h;
        }
    }

    // Finalização
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

int AUX_WaitEventTimeout(SDL_Event* evt, Uint32* ms) {
    // Guarda o tempo inicial antes de esperar
    Uint32 start = SDL_GetTicks();
    
    // Chama a função original com o tempo restante atual
    int ret = SDL_WaitEventTimeout(evt, *ms);
    
    // Calcula quanto tempo passou desde o início
    Uint32 elapsed = SDL_GetTicks() - start;
    
    // Atualiza o tempo restante (evitando underflow)
    if (elapsed >= *ms) {
        *ms = 0;
    } else {
        *ms -= elapsed;
    }
    
    // Retorna o mesmo valor da função original
    return ret;
}

/* Nomes dos integrantes
Lucas Akio Funada Tsukamoto, RA: 10425346
Luiz Filipe de Almeida Tannus, RA: 10418230
Tiago Silveira Lopes, RA: 10417600
Vitor Alves Pereira, RA: 10410862
*/

//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

enum constants
  {
    WINDOW_WIDTH = 640,
    WINDOW_HEIGHT = 480,
    WINDOW_TITLE_MAX_LENGTH = 64,
  };

//------------------------------------------------------------------------------
SDL_Texture *carregar_imagem(const char *file, SDL_Renderer *renderer) {

  SDL_Texture *texture = IMG_LoadTexture(renderer, file);

  if(!texture) {
    SDL_Log("Erro ao carregar a imagem '%s': %s", file, SDL_GetError());
    return NULL;
  }

  return texture;
}

//------------------------------------------------------------------------------
void shutdown(void)
{
  SDL_Log("shutdown()");
  SDL_Quit();
}

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  //Variáveis locais ------------------------------
  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;
  const char* WINDOW_TITLE = "Hello, SDL_image";
  //-----------------------------------------------
  //Comandos de inicialização ---------------------

  if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
    &window, &renderer))
  {
    SDL_Log("Erro ao criar a janela e/ou renderizador: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  if (argc < 2) {
        printf("Formatacao de entrada deve ser: programa caminho_da_imagem.ext\n");
        SDL_Quit();
        return 1;
    }

    char *file = argv[1];

    //printf("%s\n", caminho);


  atexit(shutdown);

  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("Erro ao iniciar a SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  //-----------------------------------------------

  //Carregamento da imagem -----------------------
  SDL_Texture *texture = carregar_imagem(file, renderer);

  if(texture == NULL) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  //-----------------------------------------------

  SDL_Event event;
  char windowTitle[WINDOW_TITLE_MAX_LENGTH] = { 0 };

  bool isRunning = true;
  while(isRunning) {
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_EVENT_QUIT:
          isRunning = false;
          break;

        case SDL_EVENT_MOUSE_MOTION:
          snprintf(windowTitle, WINDOW_TITLE_MAX_LENGTH,
            "%s (%.0f, %.0f)", WINDOW_TITLE, event.motion.x, event.motion.y);
          SDL_SetWindowTitle(window, windowTitle);
          break;
    }
    }
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  //Finalizar programa
  SDL_DestroyTexture(texture);
  texture = NULL;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;

  

  return 0;
}

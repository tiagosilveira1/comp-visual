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
/*Estrutura de dados utilizada do repositório do professor
Disponível em: https://github.com/profkishimoto/CompVis262/blob/main/src/05-filter_image/main.c
*/
typedef struct MyImage MyImage;
struct MyImage
{
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_FRect rect;
};

//------------------------------------------------------------------------------
MyImage *carregar_imagem(const char *file, SDL_Renderer *renderer) {

  SDL_Texture *texture = IMG_LoadTexture(renderer, file);

  MyImage *image = malloc(sizeof(MyImage));

  if (!image) {
    SDL_Log("Erro ao alocar memória para MyImage.");
    SDL_DestroyTexture(texture);
    return NULL;
}

  if(!texture) {
    SDL_Log("Erro ao carregar a imagem '%s': %s", file, SDL_GetError());
    SDL_DestroyTexture(texture);
    return NULL;
  }

  image->texture = texture;

  SDL_Surface *surface = IMG_Load(file);

  SDL_Surface *surface_aux = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

  SDL_DestroySurface(surface);

  if (!surface_aux)
  {
    SDL_DestroyTexture(texture);
    return NULL;
  }

  image->surface = surface_aux;

  image->rect.x = 0.0f;
  image->rect.y = 0.0f;
  image->rect.w = image->surface->w;
  image->rect.h = image->surface->h;

  return image;
}

//------------------------------------------------------------------------------
//Funções para conversão em escala de cinza
//Primeiro ver se a imagem já se encontra em escala de cinza (quando r == g == b)
//Se caso contrário, converter cada valor r,g,b dos pixels para cinza com a fórmula:
//0.2125 * r + 0.7154 * g + 0.0721 * b
bool imagem_esta_cinza(MyImage *image) {

  for (int row = 0; row < image->surface->h; ++row)
  {
    Uint32 *linha = (Uint32 *)((Uint8 *)image->surface->pixels + row * image->surface->pitch);
    for (int col = 0; col < image->surface->w; ++col)
    {
      Uint32 pixel = linha[col];

      Uint8 r, g, b;

      SDL_GetRGB(pixel,SDL_GetPixelFormatDetails(image->surface->format),SDL_GetSurfacePalette(image->surface),&r,&g,&b);

      if (r != g || g != b)
      {
        return false;
      }
    }

  }

  return true;
}

void conversao_escala_de_cinza(MyImage *image, SDL_Renderer *renderer) {

  if(!imagem_esta_cinza(image)) {

  for (int row = 0; row < image->surface->h; ++row)
  {
    Uint32 *linha = (Uint32 *)((Uint8 *)image->surface->pixels + row * image->surface->pitch);
    for (int col = 0; col < image->surface->w; ++col)
    {
      Uint32 pixel = linha[col];

      Uint8 r, g, b;

      SDL_GetRGB(pixel,SDL_GetPixelFormatDetails(image->surface->format),SDL_GetSurfacePalette(image->surface),&r,&g,&b);

      //Fórmula de conversão exigida pelo professor
      Uint8 gray = (Uint8)(0.2125 * r + 0.7154 * g + 0.0721 * b);

      linha[col] = SDL_MapSurfaceRGBA(image->surface, gray, gray, gray, 255);
    }

  }

  SDL_DestroyTexture(image->texture);

  image->texture = SDL_CreateTextureFromSurface(renderer, image->surface);

  SDL_Log("\tImagem convertida para escala de cinza.");
  return;
  }

  SDL_Log("\tImagem já está em escala de cinza...");
  return;

}

//------------------------------------------------------------------------------
/*Função utilizada do repositório do professor
Disponível em: https://github.com/profkishimoto/CompVis262/blob/main/src/05-filter_image/main.c
*/
void MyImage_destroy(MyImage *image)
{
  if (!image)
  {
    SDL_Log("\t*** Erro: Imagem inválida (image == NULL).");
    return;
  }

  if (image->texture)
  {
    SDL_Log("\tDestruindo MyImage->texture...");
    SDL_DestroyTexture(image->texture);
    image->texture = NULL;
  }

  if (image->surface)
  {
    SDL_Log("\tDestruindo MyImage->surface...");
    SDL_DestroySurface(image->surface);
    image->surface = NULL;
  }

  SDL_Log("\tRedefinindo MyImage->rect...");
  image->rect.x = image->rect.y = image->rect.w = image->rect.h = 0.0f;

  free(image);

  SDL_Log("<<< MyImage_destroy()");
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

  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("Erro ao iniciar a SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  atexit(shutdown);

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

  //-----------------------------------------------
  //Carregamento da imagem -----------------------
  MyImage *image = carregar_imagem(file, renderer);

  if(image == NULL) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    free(image);
    SDL_Quit();
    return 1;
  }

  //-----------------------------------------------
  //Converter imagem para escala de cinza ---------
  conversao_escala_de_cinza(image, renderer);
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
    SDL_RenderTexture(renderer, image->texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  //Finalizar programa
  MyImage_destroy(image);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;

  

  return 0;
}

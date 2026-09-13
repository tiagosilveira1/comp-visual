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
#include <SDL3_ttf/SDL_ttf.h>
#include <math.h>

/*
Constantes para a janela (1024x768)
Janela secundária com 320x200
*/
enum constants
  {
    WINDOW_WIDTH = 1024,
    WINDOW_HEIGHT = 768,
    INFO_WINDOW_WIDTH = 320,
    INFO_WINDOW_HEIGHT = 200,
    WINDOW_TITLE_MAX_LENGTH = 64,
  };

//------------------------------------------------------------------------------
/*Estruturas de dados utilizada do repositório do professor
Disponível em: https://github.com/profkishimoto/CompVis262/blob/main/src/05-filter_image/main.c
*/
typedef struct MyImage MyImage;
struct MyImage
{
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_FRect rect;
};

typedef struct MyWindow MyWindow;
struct MyWindow
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_FRect rect;
};

//Estrutura histograma
typedef struct Histograma Histograma;
struct Histograma
{
  int valores[256];

  double media;
  double desvio_padrao;

  const char *classificacao_brilho;
  const char *classificacao_contraste;
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
//gy = 0.2125 * r + 0.7154 * g + 0.0721 * b
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

bool MyWindow_initialize(MyWindow *window, const char *title, int width, int height, SDL_WindowFlags window_flags)
{
  SDL_Log("\tMyWindow_initialize(%s, %d, %d)", title, width, height);

  if (!window)
  {
    SDL_Log("\t\t*** Erro: Janela/renderizador inválidos (window == NULL).");
    return false;
  }

  return SDL_CreateWindowAndRenderer(title, width, height, window_flags, &window->window, &window->renderer);
}
//------------------------------------------------------------------------------

bool MyWindow_initialize_child(MyWindow *child, const char *title, int width, int height, SDL_Window *parent)
{
  SDL_Log("\tMyWindow_initialize_child(%s, %d, %d)", title, width, height);

  if (!child)
  {
    SDL_Log("\t\t*** Erro: Janela inválida (child == NULL).");
    return false;
  }

  if (!parent)
  {
    SDL_Log("\t\t*** Erro: Janela pai inválida (parent == NULL).");
    return false;
  }

  child->window = SDL_CreatePopupWindow(parent,0,0,width,height,SDL_WINDOW_POPUP_MENU);

  if (!child->window)
  {
    SDL_Log("\t\t*** Erro ao criar janela secundária: %s",SDL_GetError());
    return false;
  }

  SDL_SetWindowTitle(child->window, title);

  child->renderer = SDL_CreateRenderer(child->window, NULL);

  if (!child->renderer)
  {
    SDL_Log("\t\t*** Erro ao criar renderer da janela secundária: %s",SDL_GetError());

    SDL_DestroyWindow(child->window);
    child->window = NULL;

    return false;
  }

  child->rect.x = 0.0f;
  child->rect.y = 0.0f;
  child->rect.w = width;
  child->rect.h = height;

  return true;
}

//------------------------------------------------------------------------------
//Etapa 4: Gerar histograma da imagem
/*
Incrementa o histograma de acordo com a intensidade de cada pixel da imagem (já covertida para escala de cinza).
*/

Histograma *gerar_histograma(MyImage *image) {

  Histograma *histograma = malloc(sizeof(Histograma));

  if (!histograma)
  {
    SDL_Log("Erro ao alocar memoria para o histograma.");
    return NULL;
  }

  for (int i = 0; i < 256; ++i)
  {
    histograma->valores[i] = 0;
  }

  int total_pixels = image->surface->w * image->surface->h;

  /*
  Inicializa o histograma com a frequência dos níveis de intensidade 
  */
  for (int row = 0; row < image->surface->h; ++row)
  {
    Uint32 *linha = (Uint32 *)((Uint8 *)image->surface->pixels + row * image->surface->pitch);

    for (int col = 0; col < image->surface->w; ++col)
    {
      Uint32 pixel = linha[col];

      Uint8 r, g, b;

      SDL_GetRGB(pixel,SDL_GetPixelFormatDetails(image->surface->format),SDL_GetSurfacePalette(image->surface),&r,&g,&b);

      histograma->valores[r]++;
    }
  }

  /*
  Calcular média em seguida
  */
  double soma = 0.0;

  for (int intensidade = 0;intensidade < 256;++intensidade)
  {
    soma += intensidade * histograma->valores[intensidade];
  }

  histograma->media = soma / total_pixels;

  /*
  Classificar a imagem com base na média de brilho
  */
  if (histograma->media < 85.0)
  {
    histograma->classificacao_brilho = "escura";
  }
  else if (histograma->media < 170.0)
  {
    histograma->classificacao_brilho = "media";
  }
  else
  {
    histograma->classificacao_brilho = "clara";
  }

  /*
  Calcular desvio padrão (sub etapa final)
  */
  double soma_quadrados = 0.0;

  for (int intensidade = 0;intensidade < 256;++intensidade)
  {
    double diferenca =
        intensidade - histograma->media;

    soma_quadrados += (diferenca * diferenca) * histograma->valores[intensidade];
  }

  double variancia = soma_quadrados / total_pixels;

  histograma->desvio_padrao = sqrt(variancia);

  if (histograma->desvio_padrao < 50.0)
  {
    histograma->classificacao_contraste = "baixo";
  }
  else if (histograma->desvio_padrao < 100.0)
  {
    histograma->classificacao_contraste = "medio";
  }
  else
  {
    histograma->classificacao_contraste = "alto";
  }

  return histograma;
}

/*
Desenha o histograma na janela secundária
*/

void desenhar_histograma(SDL_Renderer *renderer, Histograma *histograma)
{
  const float grafico_x = 10.0f;
  const float grafico_y = 10.0f;
  const float grafico_w = 300.0f;
  const float grafico_h = 100.0f;

  // Fundo branco
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  int maior_valor = 0;

  // Encontrar o maior valor do histograma
  for (int i = 0; i < 256; ++i)
  {
    if (histograma->valores[i] > maior_valor)
    {
      maior_valor = histograma->valores[i];
    }
  }

  if (maior_valor == 0)
  {
    return;
  }

  // Cor preta para as barras
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  float largura_barra = grafico_w / 256.0f;

  for (int i = 0; i < 256; ++i)
  {
    if (histograma->valores[i] == 0)
    {
      continue;
    }

    float altura =
        ((float)histograma->valores[i] /
         (float)maior_valor) *
        grafico_h;

    SDL_FRect barra;

    barra.x = grafico_x + i * largura_barra;
    barra.y = grafico_y + grafico_h - altura;
    barra.w = largura_barra + 1.0f;
    barra.h = altura;

    SDL_RenderFillRect(renderer, &barra);
  }
}

/*
Por fim, printa a média das intensidades e o desvio padrão na janela secundária, informando se é imagem clara, média ou escura
*/

void desenhar_informacoes(SDL_Renderer *renderer, TTF_Font *fonte, Histograma *histograma)
{
    SDL_Color preto = {0, 0, 0, 255};

    char texto[128];

    // -----------------------------------------
    // Média de intensidade
    // -----------------------------------------

    snprintf(texto,sizeof(texto),"Media: %.2f - imagem %s",histograma->media,histograma->classificacao_brilho);

    SDL_Surface *surface_texto = TTF_RenderText_Blended(fonte,texto,0,preto);

    if (surface_texto)
    {
        SDL_Texture *texture_texto = SDL_CreateTextureFromSurface(renderer,surface_texto);
        SDL_FRect rect;

        rect.x = 10.0f;
        rect.y = 115.0f;
        rect.w = (float)surface_texto->w;
        rect.h = (float)surface_texto->h;

        SDL_DestroySurface(surface_texto);

        if (texture_texto)
        {
            SDL_RenderTexture(renderer,texture_texto,NULL,&rect);
            SDL_DestroyTexture(texture_texto);
        }
    }

    // -----------------------------------------
    // Desvio padrão
    // -----------------------------------------

    snprintf(texto,sizeof(texto),"Desvio padrao: %.2f - contraste %s",histograma->desvio_padrao,histograma->classificacao_contraste);

    surface_texto = TTF_RenderText_Blended(fonte,texto,0,preto);

    if (surface_texto)
    {
        SDL_Texture *texture_texto = SDL_CreateTextureFromSurface(renderer,surface_texto);
        SDL_FRect rect;

        rect.x = 10.0f;
        rect.y = 135.0f;
        rect.w = (float)surface_texto->w;
        rect.h = (float)surface_texto->h;

        SDL_DestroySurface(surface_texto);

        if (texture_texto)
        {
            SDL_RenderTexture(renderer,texture_texto,NULL,&rect);
            SDL_DestroyTexture(texture_texto);
        }
    }
}

//------------------------------------------------------------------------------
/*Função utilizada do repositório do professor
Disponível em: https://github.com/profkishimoto/CompVis262/blob/main/src/05-filter_image/main.c
*/
void MyWindow_destroy(MyWindow *window)
{
  SDL_Log(">>> MyWindow_destroy()");

  if (!window)
  {
    SDL_Log("\t*** Erro: Janela/renderizador inválidos (window == NULL).");
    SDL_Log("<<< MyWindow_destroy()");
    return;
  }

  SDL_Log("\tDestruindo MyWindow->renderer...");
  SDL_DestroyRenderer(window->renderer);
  window->renderer = NULL;

  SDL_Log("\tDestruindo MyWindow->window...");
  SDL_DestroyWindow(window->window);
  window->window = NULL;

  SDL_Log("<<< MyWindow_destroy()");
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
void loop(MyWindow *window, MyWindow *infoWindow, MyImage *image, Histograma *histograma, TTF_Font *fonte)
{
  SDL_Event event;

  char windowTitle[WINDOW_TITLE_MAX_LENGTH] = {0};

  bool isRunning = true;

  while (isRunning)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_EVENT_QUIT:
          isRunning = false;
          break;

        case SDL_EVENT_MOUSE_MOTION:

          snprintf(windowTitle, WINDOW_TITLE_MAX_LENGTH, "%s (%.0f, %.0f)", "Hello, SDL_image", event.motion.x, event.motion.y);
          SDL_SetWindowTitle(window->window, windowTitle);
          break;
      }
    }

    //---------------------------------------------
    // Renderizar janela principal ----------------

    SDL_RenderClear(window->renderer);

    SDL_RenderTexture(window->renderer, image->texture, NULL, NULL);

    SDL_RenderPresent(window->renderer);

    //---------------------------------------------
    // Renderizar janela secundária

    SDL_RenderClear(infoWindow->renderer);

    desenhar_histograma(infoWindow->renderer,histograma);

    desenhar_informacoes(infoWindow->renderer,fonte,histograma);

    SDL_RenderPresent(infoWindow->renderer);
  }
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
  // Variáveis locais ------------------------------

  MyWindow window;
  MyWindow infoWindow;

  const char *WINDOW_TITLE = "Hello, SDL_image";
  const char *INFO_WINDOW_TITLE = "Hello, secondary window";

  //-----------------------------------------------
  /*
  Inicializar as estruturas
  */
  window.window = NULL;
  window.renderer = NULL;

  window.rect.x = 0.0f;
  window.rect.y = 0.0f;
  window.rect.w = 0.0f;
  window.rect.h = 0.0f;

  infoWindow.window = NULL;
  infoWindow.renderer = NULL;

  infoWindow.rect.x = 0.0f;
  infoWindow.rect.y = 0.0f;
  infoWindow.rect.w = 0.0f;
  infoWindow.rect.h = 0.0f;

  //-----------------------------------------------
  // Inicialização da SDL -------------------------

  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("Erro ao iniciar a SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  atexit(shutdown);

  //-----------------------------------------------
  // Inicialização do ttf -------------------------

  if (!TTF_Init())
{
    SDL_Log("Erro ao iniciar SDL_ttf: %s", SDL_GetError());
    SDL_Quit();
    return SDL_APP_FAILURE;
}

  //-----------------------------------------------
  // Verificar argumento da imagem ----------------

  if (argc < 2)
  {
    printf("Formatacao de entrada deve ser: programa caminho_da_imagem.ext\n");

    SDL_Quit();
    return 1;
  }

  char *file = argv[1];

  //-----------------------------------------------
  // Criar janela principal -----------------------

  if (!MyWindow_initialize(&window, WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT,0))
  {
    SDL_Log("\t*** Erro ao criar a janela e/ou renderizador: %s",SDL_GetError());
    MyWindow_destroy(&window);
    SDL_Quit();
    return 1;
  }

  //-----------------------------------------------
  // Criar janela secundária ----------------------

  if (!MyWindow_initialize_child(&infoWindow, INFO_WINDOW_TITLE, INFO_WINDOW_WIDTH, INFO_WINDOW_HEIGHT, window.window))
  {
    SDL_Log("\t*** Erro ao criar a janela secundária: %s",SDL_GetError());
    MyWindow_destroy(&window);
    MyWindow_destroy(&infoWindow);
    SDL_Quit();
    return 1;
  }

  //-----------------------------------------------
  //Carregar fonte --------------------------------
  TTF_Font *fonte = TTF_OpenFont("assets/DejaVuSans.ttf", 8);

  if (!fonte)
{
    SDL_Log("Erro ao carregar fonte: %s", SDL_GetError());

    MyWindow_destroy(&infoWindow);
    MyWindow_destroy(&window);
    TTF_Quit();
    SDL_Quit();

    return 1;
}

  //-----------------------------------------------
  // Carregamento da imagem -----------------------

  MyImage *image = carregar_imagem(file, window.renderer);

  if (image == NULL)
  {
    MyWindow_destroy(&window);
    MyWindow_destroy(&infoWindow);

    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  //-----------------------------------------------
  // Converter imagem para escala de cinza --------

  conversao_escala_de_cinza(image, window.renderer);

  //-----------------------------------------------
  // Histograma da imagem -------------------
  Histograma *histograma = gerar_histograma(image);

  if (!histograma)
  {
  SDL_Log("\t*** Erro ao criar o histograma da imagem.");
  MyImage_destroy(image);
  MyWindow_destroy(&infoWindow);
  MyWindow_destroy(&window);

  TTF_Quit();
  SDL_Quit();
  return 1;
}

  // Loop principal -------------------------------

  loop(&window, &infoWindow, image, histograma, fonte);

  //-----------------------------------------------
  // Finalização -----------------------------------

  MyImage_destroy(image);

  MyWindow_destroy(&infoWindow);
  MyWindow_destroy(&window);

  TTF_CloseFont(fonte);
  TTF_Quit();

  SDL_Log("\t*** Liberando memória ...");
  free(histograma);

  return 0;
}
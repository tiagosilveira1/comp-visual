# Projeto 1 - Relatorio de Analise Final (Etapa 2)

Universidade Presbiteriana Mackenzie - Faculdade de Computacao e Informatica
Disciplina: Computacao Visual - Prof. Andre Kishimoto

## 1. Integrantes do grupo

- Lucas Akio Funada Tsukamoto, RA: 10425346
- Luiz Filipe de Almeida Tannus, RA: 10418230
- Tiago Silveira Lopes, RA: 10417600
- Vitor Alves Pereira, RA: 10410862

## 2. Link do repositorio

<https://github.com/tiagosilveira1/comp-visual>

## 3. Fonte utilizada nos textos do programa

Foi utilizada a familia **DejaVu Sans** (arquivo `DejaVuSans.ttf`, em
`assets/fonts/`), por ser uma fonte livre, com licenca permissiva e
disponivel para qualquer sistema operacional. O carregamento e feito
via `SDL_GetBasePath()` na funcao `carregar_fonte`, garantindo que o
caminho da fonte seja resolvido corretamente independente do diretorio
a partir do qual o executavel e chamado.

> Se o grupo trocou de fonte, atualizar este item e a constante
> `FONT_RELATIVE_PATH` no codigo.

## 4. Refatoracoes no codigo-fonte original

O ponto de partida do grupo foi o projeto de exemplo `05-filter_image`
do repositorio da disciplina, do qual foram reaproveitados:

- A estrutura `MyImage` (agrupando `SDL_Surface`, `SDL_Texture` e o
  `SDL_FRect` de destino).
- A funcao `MyImage_destroy`, que libera corretamente textura e
  surface antes de desalocar a struct.

Sobre essa base, o grupo escreveu as funcoes `carregar_imagem`,
`imagem_esta_cinza` e `conversao_escala_de_cinza` para os itens 1 e 2
do escopo (carregamento com tratamento de erro e conversao para
escala de cinza pela formula `Y = 0.2125R + 0.7154G + 0.0721B`, usando
`SDL_GetRGB`/`SDL_GetPixelFormatDetails`/`SDL_MapSurfaceRGBA` para ler
e escrever pixels).

Para completar os itens restantes do escopo (3 a 8), o codigo foi
estendido mantendo o mesmo padrao de acesso a pixels e a mesma
convencao de nomes em portugues, adicionando:

- **`AppState`**: struct que centraliza as duas janelas/renderers, as
  duas versoes da imagem (`img_cinza` e `img_equalizado`), a fonte, o
  histograma atual e os dois botoes - em vez de espalhar essas
  variaveis soltas pelo `main`, facilitando passar o estado para as
  funcoes de evento/desenho.
- **`Histograma` + `calcular_histograma`/`classificar_brilho`/
  `classificar_contraste`/`desenhar_histograma`** (item 4): calculo de
  media/desvio padrao a partir da contagem de intensidades e desenho
  das barras com primitivas SDL.
- **`equalizar_histograma`** (item 5): gera uma nova `MyImage` a partir
  da distribuicao acumulada (CDF) do histograma, reaproveitando o
  mesmo `MyImage` para poder alternar com `MyImage_destroy` sem
  duplicar logica de liberacao de memoria.
- **`Botao` + funcoes `criar_botao`/`botao_mouse_move`/
  `botao_mouse_down`/`botao_mouse_up`/`desenhar_botao`** (itens 5 e 6):
  maquina de estados neutro/hover/clicado, desenhada com
  `SDL_RenderFillRect`/`SDL_RenderRect` e texto via `SDL_ttf`.
- **Janela secundaria filha da principal** (item 3): criada com
  `SDL_CreateWindow` + `SDL_SetWindowParent` + `SDL_SetWindowPosition(0,0)`.
- **`reposicionar_janela_principal`** (itens 3 e 6): centraliza a
  janela principal no monitor primario ou a posiciona em (0,0) quando
  as dimensoes excedem a resolucao atual do sistema.
- **`salvar_imagem_atual`** (item 7): salva via `IMG_SavePNG` a imagem
  atualmente exibida (considerando tanto o estado de equalizacao
  quanto o de resolucao), diferenciando "criado" de "sobrescrito".
- **`carregar_fonte`** (item 8): localizacao da fonte independente de
  SO via `SDL_GetBasePath()`.

Duas pequenas mudancas de comportamento tambem foram feitas em relacao
a primeira versao do `main`:
- A checagem de `argc < 2` foi movida para **antes** da criacao da
  janela (evita abrir uma janela quando nenhuma imagem foi informada).
- Foi adicionado um `default: break;` no `switch` de eventos, para
  evitar avisos do compilador com `-Wall -Wextra` (o `switch` cobria
  apenas alguns dos varios valores de `SDL_EventType`).

## 5. Problemas encontrados durante o desenvolvimento

> **PREENCHER**: quais erros de compilacao, comportamentos
> inesperados da API do SDL3, diferencas entre as maquinas do grupo
> (Windows/Linux, versoes de compilador/bibliotecas) ou outras
> dificuldades reais o grupo enfrentou ao integrar o codigo? Como cada
> uma foi resolvida?
>
> Alguns pontos onde e comum aparecer atrito, para ajudar a lembrar:
> - Falta do arquivo `DejaVuSans.ttf` em `assets/fonts/` (o programa
>   roda, mas sem texto nos botoes/histograma).
> - Falta da flag de linkagem `-lSDL3_ttf` (e `-lm`) no comando de
>   compilacao/Makefile, causando erro de "undefined reference".
> - Diferencas de versao do SDL3 entre as maquinas do grupo mudando
>   pequenos detalhes de assinatura de funcao.

## 6. Itens que pareciam faceis mas exigiram pesquisa extra / IA

> **PREENCHER**: comparando com o que a Etapa 1 do grupo apontou como
> "resolviamos so com o material da disciplina", algum desses itens
> (por exemplo, carregamento de imagem ou deteccao de cor/cinza)
> acabou exigindo pesquisa adicional na pratica? Por que?

## 7. Itens que o grupo previu como dificeis: as duvidas foram resolvidas?

> **PREENCHER**: pelos itens que sobraram do escopo original (janela
> filha, histograma, equalizacao, botoes com estado, salvar imagem,
> fonte multiplataforma), comentem se, depois de ver a implementacao
> funcionando, o grupo sente que entendeu de fato os temas (por
> exemplo, o que e e como funciona a equalizacao de histograma, como
> SDL3 gerencia pixels via `SDL_PixelFormatDetails`) ou se ainda restam
> duvidas.

## 8. Como a IA generativa ajudou no desenvolvimento

O grupo implementou por conta propria os itens 1 e 2 do escopo
(carregamento de imagem e conversao para escala de cinza). A partir
dessa base, foi usada a IA generativa **Claude (Anthropic)** para
implementar os itens 3 a 8, que ainda nao existiam no codigo do grupo:

- Levantamento das assinaturas corretas de funcoes do SDL3, SDL3_image
  e SDL3_ttf que mudaram em relacao ao SDL2 (documentacao oficial
  consultada em tempo real) - por exemplo, `SDL_SetWindowParent` para
  criar a janela filha, `SDL_GetPrimaryDisplay`/`SDL_GetDisplayBounds`
  para centralizar/posicionar a janela principal, `SDL_ScaleSurface`
  para redimensionar a imagem, e `TTF_RenderText_Blended` para
  desenhar texto.
- Geracao do codigo das structs e funcoes novas (`Histograma`,
  `Botao`, `AppState` e as funcoes associadas), seguindo o mesmo
  estilo do codigo ja existente do grupo (nomes em portugues, mesmo
  padrao de acesso a pixels via `SDL_GetRGB`/`SDL_MapSurfaceRGBA`).
- Revisao do gerenciamento de memoria das novas estruturas (por
  exemplo, reaproveitar `MyImage_destroy` para a imagem equalizada, e
  destruir a textura/superficie temporarias usadas ao redimensionar
  para salvar ou exibir a imagem).

> **O grupo deve confirmar/ajustar este item**: o que foi revisado
> manualmente, o que foi testado e o que eventualmente foi alterado
> depois de rodar o programa pela primeira vez.

## 9. Assuntos que o grupo acha que precisa estudar/praticar mais

> **PREENCHER**: por exemplo, manipulacao de pixels em baixo nivel,
> processamento digital de imagens em geral, gerenciamento de
> multiplas janelas em SDL, matematica por tras da equalizacao de
> histograma, etc.

## 10. Funcionalidades futuras (usabilidade / qualidade de vida)

O enunciado pede pelo menos (numero de integrantes x 2) itens. Para um
grupo de 4 pessoas, isso significa pelo menos **8 itens**:

1. **Arrastar e soltar (drag and drop)** de um arquivo de imagem sobre
   a janela para carrega-lo, sem precisar reiniciar o programa pelo
   terminal.
2. **Desfazer/refazer (undo/redo)** para as operacoes aplicadas
   (conversao para cinza, equalizacao, redimensionamento).
3. **Escolher o nome/local do arquivo de saida** ao salvar (em vez de
   sempre `output_image.png`), com uma caixa de dialogo do sistema
   operacional.
4. **Filtros adicionais** alem da conversao para cinza e equalizacao
   (desfoque, nitidez, deteccao de bordas), com preview antes de
   aplicar.
5. **Zoom e pan** na imagem exibida, util para imagens muito grandes
   ou muito pequenas.
6. **Comparacao lado a lado (antes/depois)** entre a imagem original e
   a imagem processada.
7. **Historico de arquivos recentes**, permitindo reabrir rapidamente
   as ultimas imagens processadas.
8. **Suporte a multiplas imagens na mesma execucao** (por exemplo, em
   abas), evitando ter que reiniciar o programa para cada arquivo.

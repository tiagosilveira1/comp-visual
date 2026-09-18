# Projeto 1 - Relatório da Análise Final (Etapa 2)

**Universidade Presbiteriana Mackenzie** – Faculdade de Computação e Informática
**Disciplina:** Computação Visual – Prof. André Kishimoto

## 1. Integrantes do grupo

- Lucas Akio Funada Tsukamoto, RA: 10425346
- Luiz Filipe de Almeida Tannus, RA: 10418230
- Tiago Silveira Lopes, RA: 10417600
- Vitor Alves Pereira, RA: 10410862

## 2. Link do repositório

[https://github.com/tiagosilveira1/comp-visual](https://github.com/tiagosilveira1/comp-visual)

## 3. Fonte utilizada nos textos do programa

*Qual (ou quais) fonte ou família de fonte foi escolhida para ser usada nos textos do programa.*

Utilizamos SDL.ttf com a fonte/família DejaVu Sans (arquivo `DejaVuSans.ttf`, em `assets/fonts/`), por ser uma fonte livre, com licença permissiva e disponível para qualquer sistema operacional. O carregamento é feito via `SDL_GetBasePath()` na função `carregar_fonte`, garantindo que o caminho da fonte seja resolvido corretamente independente do diretório a partir do qual o executável é chamado.

## 4. Refatorações no código-fonte original

*Alguma parte do código-fonte original foi refatorado? Se sim, descreva e justifique as refatorações.*

Sim. O ponto de partida do grupo foi o projeto de exemplo `05-filter_image` do repositório da disciplina, do qual foram reaproveitados:

- A estrutura `MyImage` (agrupando `SDL_Surface`, `SDL_Texture` e o `SDL_FRect` de destino), pois facilita a implementação ao agrupar em um struct.
- A estrutura `MyWindow` para guardar window com sua respectiva renderer, facilitando muito a implementação de funções posteriores.
- A função `MyImage_destroy`, que libera corretamente textura e surface antes de desalocar a struct, para facilitar o uso da struct.
- A função `MyWindow_destroy` para destruir a janela e sua renderização (coloca ponteiros como NULL), também voltado para facilitar o uso da struct.
- A função `MyWindow_initialize` para carregar window e renderer, facilitando o uso da struct na main.
- Outras funções de `05-filter_image`, como `shutdown()`, `initialize()` e o `loop()`, também foram utilizadas como base para facilitar posterior expansão do código.

## 5. Problemas encontrados durante o desenvolvimento

*Quais problemas foram encontrados durante o desenvolvimento? Como foram solucionados pelo grupo?*

Os problemas dos itens 1 e 2 conseguimos implementar e solucionar pelo código-base, principalmente com ajuda de suas funções e estruturas, bem como funções SDL desse código-base. O item 3 exigiu pesquisa por IA para achar a função `SDL_CreatePopupWindow()` para criar janela filha. Já o item 4 necessitamos também da ajuda da IA apenas para exibir o histograma, pois a leitura dos pixels não foi muito difícil a implementação, com exceção em descobrir algumas funções como `SDL_GetRGB()`. Na parte de exibição, a dificuldade ficou na parte de como manipular as coordenadas da janela secundária para exibição do histograma, enquanto a parte de exibição dos textos foi de menor dificuldade, pois conseguimos incluir a biblioteca SDL.ttf com sucesso, apenas necessitando posteriormente saber os comandos para escrever os textos e manipular as coordenadas.

Já o item 5 foi o mais difícil desse projeto, pois necessitamos pesquisar com e sem IA como equalizar o histograma e como devemos modificar a imagem de exibição para mostrar a versão equalizada, podendo voltar ao estado original (criamos uma cópia de surface nesse caso). O item 6 não foi muito difícil por ser semelhante à exibição do histograma, porém um pouco trabalhoso. Nesse caso, utilizamos IA no loop do código para detecção de clicks, bem como gerar as estruturas dos botões. Porém conseguimos criar e posicionar os botões como o enunciado exigiu. Já os itens 7 e 8 foram muito simples. Não apresentamos dificuldades.

## 6. Itens que pareciam fáceis mas exigiram pesquisa extra / IA

*Sobre os itens do "Escopo e funcionalidades obrigatórias" que o grupo identificou que conseguia resolver consultando e adaptando somente o material da disciplina e a documentação da SDL (análise inicial): o grupo teve que consultar referências extras e/ou usar IA generativa para resolver algum item? Se sim, quais itens e por quê?*

Sim. Nesse caso apenas para o item 3, sobre exibição da janela secundária como janela filha da principal. O resto dos itens mencionados na primeira etapa que pareciam fáceis conseguimos implementar.

## 7. Itens que o grupo previu como difíceis: as dúvidas foram resolvidas?

*Sobre os itens do "Escopo e funcionalidades obrigatórias" que o grupo reconheceu que precisaria pesquisar mais a fundo ou usar a ajuda de uma IA generativa (análise inicial): as soluções encontradas ajudaram a entender melhor os temas abordados por cada item?*

Sim. Esclareceram grande parte das dúvidas: como manipular pixels, como exibir o histograma, textos e botões e como equalizar o histograma.

## 8. Como a IA generativa ajudou no desenvolvimento

*Como a IA generativa ajudou no desenvolvimento do software, caso o grupo tenha usado?*

Não apresentamos problemas para implementar e entender os itens 1 e 2, conseguimos implementar pelo código-base. O item 3 exigiu pesquisa por IA para achar a função `SDL_CreatePopupWindow()` para criar janela filha. Já o item 4 necessitamos também da ajuda da IA apenas para exibir o histograma, pois entendemos como gerá-lo. A equalização do histograma também foi feita com IA, pois tivemos dificuldade em entendê-la. Já o item 6 foi mais fácil, porém trabalhoso comparado aos anteriores; utilizamos IA nesse caso apenas para entender a lógica de status do loop para detectar clicks e mouse sobreposto no botão (a IA sugeriu utilizarmos a estrutura de dados `Botao` desse projeto). Já os itens 7 e 8 não necessitamos, são etapas muito simples, sendo que a última nem exigiu implementações.

## 9. Assuntos que o grupo acha que precisa estudar/praticar mais

*Quais assuntos o grupo acha que precisa estudar e praticar mais?*

O assunto principal que achamos necessitar de mais estudos é sobre a equalização de histograma, pois achamos que foi a parte mais difícil de entender. Também necessitamos ver mais aprofundado sobre as funções básicas da biblioteca SDL, pois necessitamos pesquisar uma parte considerável dessas funções.

## 10. Funcionalidades futuras (usabilidade / qualidade de vida)

*Analisando o software desenvolvido, descreva pelo menos (quantidade de integrantes do grupo × 2) funcionalidades que seriam importantes implementar do ponto de vista do usuário (pensar em usabilidade e qualidade de vida).*

Para um grupo de 4 pessoas, listam-se as 8 funcionalidades a seguir:

1. Arrastar e soltar (drag and drop) de um arquivo de imagem sobre a janela para carregá-lo, sem precisar reiniciar o programa pelo terminal.
2. Desfazer/refazer (undo/redo) para as operações aplicadas (conversão para cinza, equalização, redimensionamento).
3. Escolher o nome/local do arquivo de saída ao salvar (em vez de sempre `output_image.png`), com uma caixa de diálogo do sistema operacional.
4. Filtros adicionais além da conversão para cinza e equalização (desfoque, nitidez, detecção de bordas), com preview antes de aplicar.
5. Zoom na imagem exibida, útil para imagens muito grandes ou muito pequenas.
6. Comparação lado a lado (antes/depois) entre a imagem original e a imagem processada.
7. Histórico de comandos, permitindo abrir uma aba para visualizar os últimos comandos do usuário.
8. Suporte a múltiplas imagens na mesma execução (por exemplo, em abas), evitando ter que reiniciar o programa para cada arquivo.

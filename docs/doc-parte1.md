# Etapa 1: Relatório e análise inicial

# Nomes dos integrantes
- Lucas Akio Funada Tsukamoto, RA: 10425346
- Luiz Filipe, RA: 10418230
- Tiago Silveira Lopes, RA: 10417600
- Vitor Alves Pereira, RA: 10410862

# Perguntas exigidas no relatório

- **Para que o projeto seja desenvolvido usando as versões mais recentes e estáveis das bibliotecas, o que
mudará em relação aos vídeos/repositório da disciplina?**

A versão mais recente do SDL baixada no site é a 3.4.14, enquanto a versão apresentada pelo professor na vídeo aula é a 3.4.0. Dessa forma, ao acessar o changelog no github do SDL (https://github.com/libsdl-org/SDL/releases) pode-se notar que a grande maioria das modificações se resumem a bug fixes. Enquanto a biblioteca SDL_Image apresentou em seus changelogs de 2026 diversas funcionalidades novas voltadas ao carregamento e salvamento de imagens/animações, bem como diversos crashes e bugfixes. Disponível em https://github.com/libsdl-org/SDL_image/releases. Dessa forma, não mudará quase nada, exceto se, por ventura, alguma dessas funções novas da biblioteca SDL_Image possuir alguma utilidade prática para o desenvolvimento do projeto.

- **O processo de build usado pelo grupo é o mesmo dos vídeos/repositório da disciplina? Se for diferente,
descreva brevemente o processo adotado pelo grupo.**

Sim. Seguimos os vídeos tutoriais pelo professor disponibilizados no moodle, de forma a configurar as bibliotecas SDL/SDL_Image no VSCode com o gcc como compilador e conseguimos rodar os códigos de exemplo do repositório do professor em nossas máquinas.

- **O grupo usará mais de um sistema operacional, compilador e/ou editor diferente? Por exemplo,
Windows e Linux, Windows e Mac, GCC e Clang, GCC e MSVC, vscode e Visual Studio, XCode e
vscode, vim e Notepad++, etc.**

Não, todos nós planejamos utilizar apenas Windows (SO), GCC (compilador) e VSCode (editor) para o desenvolvimento desse projeto.

- **Considerando que os integrantes do grupo usarão diferentes SOs, compiladores e/ou editores, descreva
quais potenciais problemas/dificuldades o grupo acha que poderá encontrar durante o desenvolvimento.
Caso todos os integrantes usem a mesma configuração, desconsidere este item.**

- **Quais itens do "Escopo e funcionalidades obrigatórias" o grupo identificou que consegue resolver
consultando e adaptando somente o material da disciplina e a documentação da SDL?**
1. Carregamento de imagens: por ser simples e objetivo. Os materiais devem ser o suficiente para esse item.
2. Analise e conversão para escala de cinza: Possível de implementação somente utilizando os materiais. No entanto, devemos pesquisar ainda sobre a função para detectar se uma imagem é colorida ou está em escala de cinza.
3. Interface gráfica de usuário (GUI) com duas janelas: A exibição de imagem com determinado width/height não apresentamos dificuldade ao consultar o material do git do professor. Mas a parte de janela secundária/filha ainda precisamos ver mais a fundo como fazer.
7. Salvar imagem: olhando inicialmente parece ser um tema não muito complicado.
8. Exibição de textos (informações no histograma e botões): Uma vez que aprendermos como manipular histogramas e botões acreditamos que esse item deve não apresentar dificuldades.

- **Quais itens do "Escopo e funcionalidades obrigatórias" o grupo reconhece que precisará pesquisar
mais a fundo ou usará a ajuda de uma IA generativa? Por quê?**
Os itens:
4. Análise e exibição do histograma
5. Equalização do histograma
6. Exibição da imagem
  Justificativa: pois intuitivamente pensamos que estes itens possuem maior teor de detalhes e na lógica de implementação. Portanto, necessitando de mais pesquisas e formas para auxiliar no desenvolvimento. O uso de IA generativa será tratada como último recurso.


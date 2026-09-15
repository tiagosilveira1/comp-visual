Este repositório é destinado para projetos envolvendo a disciplina de Computação Visual da FCI (Faculdade de Computação e Informática) Mackenzie (UPM) 2026/2.

# Sistema de Processamento de Imagens

## 1. Sobre o projeto

Este projeto consiste no desenvolvimento de um software de processamento
de imagens em linguagem C, utilizando as bibliotecas SDL3, SDL3_Image e SDL.ttf.

O programa recebe o caminho de uma imagem como argumento de linha de
comando, carrega a imagem e permite realizar operações de processamento
e análise por meio de uma janela principal e uma janela secundária.

O projeto foi desenvolvido a partir de um código-fonte-base fornecido
pelo professor, que foi posteriormente adaptado e ampliado para atender
aos requisitos propostos na atividade.

- [Link do repositório do professor](https://github.com/profkishimoto/CompVis262)
- [Link do código-base](https://github.com/profkishimoto/CompVis262/blob/main/src/05-filter_image/main.c)

---

## 2. Como o projeto funciona

O programa recebe uma imagem através da linha de comando:

```text
programa caminho_da_imagem.ext
```

Após a execução, a imagem é carregada e convertida para escala de cinza.
O programa apresenta a imagem em uma janela principal e as informações
de processamento em uma janela secundária.

A janela secundária apresenta o histograma da imagem, além da média e do
desvio padrão dos níveis de intensidade. A partir dessas informações, a
imagem também é classificada de acordo com seu brilho e contraste.

A partir disso, o usuário pode equalizar a imagem por meio de um botão interativo na
janela secundária do programa, bem como voltar ao estado anterior. Uma imagem nova
é mostrada na tela (equalizada), com seu histograma, média e desvio padrão correspondentes
na janela secundária.

Há também um segundo botão interativo em que o usuário pode alternar entre a resolução padrão do
projeto (1024x768) e as dimensões originais da imagem. E por fim, o usuário pode salvar a imagem atual
exibida na janela principal ao pressionar a tecla 'S' do teclado, criando ou sobrescrevendo **output_image.png**.

O programa possui as seguintes funcionalidades:

- Carregamento de imagens;
- Conversão da imagem para escala de cinza;
- Verificação se a imagem já está em escala de cinza;
- Geração e exibição do histograma;
- Cálculo da média dos níveis de intensidade;
- Cálculo do desvio padrão;
- Classificação do brilho da imagem;
- Classificação do contraste da imagem;
- Equalização do histograma;
- Restauração da imagem original em escala de cinza;
- Alternância entre a resolução original e 1024x768;
- Redimensionamento e centralização da janela principal;
- Salvamento da imagem atualmente exibida em output_image.png.

### Controles
| Ação | Comando |
| :----: | :----: |
|    Equalizar histograma    |    Clique no botão "Equalizar"    |
|    Restaurar imagem    |    Clique no botão "Ver original"    |
|   Alternar resolução    |    Clique no botão de resolução    |
|   Salvar Imagem    |   Tecla **S**    |

## 3. Estrutura do projeto
| Arquivo (ou pasta) | Função |
| :----: | :----: |
|    main.c    |    O código-fonte principal do programa    |
|    makefile    |    Arquivo para processo de compilação    |
|    assets/   |    arquivos utilizados pelo programa, como a fonte utilizada
na interface    |
|    README.md   |   Documentação do projeto    |
|    doc-parte1.md   |   Documentação exigida da primeira entrega    |
|    doc-parte2.md   |   Documentação exigida da segunda entrega    |
|  .gitignore   |   Arquivo de configuração do Git que informa quais arquivos não devem ser enviados para o repositório.  |
|  .vscode/   |  Contém arquivos específicos para processos de compilação desse projeto   |

## 4. Contribuições do grupo

- Lucas Akio Funada Tsukamoto, RA: 10425346
Implementação do histograma e da sua equalização.

- Luiz Filipe de Almeida Tannus, RA: 10418230
Documentações do projeto, como doc-parte1.md e doc-parte2.md.

- Tiago Silveira Lopes, RA: 10417600
Etapas iniciais como carregamento de imagens e conversão para escala de cinza.

- Vitor Alves Pereira, RA: 10410862
Implementação da janela secundária, funcionalidades dos botões e salvamento de imagens.

# Sistema de Processamento de Imagens

## Nomes e RAs dos integrantes
Lucas Akio Funada Tsukamoto, RA: 10425346

Luiz Filipe de Almeida Tannus, RA: 10418230

Tiago Silveira Lopes, RA: 10417600

Vitor Alves Pereira, RA: 10410862

Projeto acadêmico desenvolvido para a disciplina de Computação Visual
da Faculdade de Computação e Informática (FCI) da Universidade
Presbiteriana Mackenzie (UPM), no semestre 2026/2.

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

Documentações inicial e final do projeto: doc-parte1.md e doc-parte2.md.

- Tiago Silveira Lopes, RA: 10417600

Organizador do repositório; Etapas iniciais como carregamento de imagens e conversão para escala de cinza.

- Vitor Alves Pereira, RA: 10410862

Implementação da janela secundária, funcionalidades dos botões, etapa de exibição de imagem e salvamento de imagens.

## 5. Ambiente de desenvolvimento
| Componente | Versão |
| :----: | :----: |
| Sistema operacional | Windows 10 |
| Compilador | gcc-v14.2.0 |
| SDL3 | 3.4.14 |
| SDL3_image | 3.4.6 |
| SDL3_ttf | 3.2.2 |

## 6. Dependências
Para compilar e executar o projeto, são necessárias:

GCC;
SDL3;
SDL3_image;
SDL3_ttf;
arquivo de fonte DejaVuSans.ttf.

As bibliotecas SDL3, SDL3_image e SDL3_ttf devem estar instaladas
e disponíveis nos caminhos configurados no Makefile, bem como possuírem as versões especificadas no item anterior.

## 7. Compilação
Para compilar o projeto, utilize o **makefile**.
Na pasta principal do projeto, execute:
```text
make
```
O comando compila o arquivo main.c utilizando o compilador GCC e
as bibliotecas SDL3, SDL3_image e SDL3_ttf.

Obs: garanta que você tenha instalado as bibliotecas necessárias nas pastas de include e bin destacadas no makefile e nas versões especificadas desse projeto.

## 8. Execução

Após a compilação, o programa deve ser executado passando o caminho
da imagem como argumento:

```text
.\programa caminho_da_imagem.ext
```

A imagem deve ser fornecida como argumento na linha de comando para que
o programa possa carregá-la.

## 9.Código-base e adaptações
O desenvolvimento foi iniciado a partir do código-base fornecido pelo
professor, disponível no [repositório da disciplina](https://github.com/profkishimoto/CompVis262).

Durante o desenvolvimento, o código original foi adaptado para atender
aos requisitos da atividade.

Entre as principais adaptações estão:

- Ampliação da estrutura MyImage para armazenar a imagem original;
- Implementação da conversão para escala de cinza;
- Implementação da geração e análise do histograma;
- Implementação da equalização do histograma;
- Implementação da restauração da imagem original;
- Criação da estrutura responsável pelos botões;
- Implementação dos estados dos botões;
- Implementação da alteração da resolução da janela;
- Implementação do salvamento da imagem;
- Organização das funcionalidades em funções específicas.

## 10. Licença

Projeto desenvolvido para fins acadêmicos na disciplina de Computação
Visual da Faculdade de Computação e Informática da Universidade
Presbiteriana Mackenzie.

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

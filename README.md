# Simulador de Cubo Mágico 2x2x2 com IA

Simulador de cubo mágico 2x2x2 com modo manual e resolução automática por IA
(Busca em Largura, Busca em Profundidade Limitada Iterativa e A*).

## Status atual

- Modo manual (jogar com teclado, visualização 3D): funcionando
- Buscas (Largura, Profundidade Iterativa, A*): em desenvolvimento

## Pré-requisitos

Você precisa de um compilador C/C++ (g++) e da biblioteca GLFW instalada.

### macOS

Instale o Homebrew (se ainda não tiver) e depois rode:

    brew install glfw

### Windows

Instale o MSYS2 (https://www.msys2.org) e, no terminal UCRT64 dele, rode:

    pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-glfw mingw-w64-ucrt-x86_64-pkgconf

Use sempre o terminal UCRT64 do MSYS2 pra compilar, não o cmd ou PowerShell puro.

### Linux (Ubuntu/Debian)

    sudo apt install build-essential libglfw3-dev libgl1-mesa-dev

## Como rodar

Na primeira vez (e sempre que o código mudar), compile com:

    make

Depois rode o programa:

    ./simulador

No Windows, o executável gerado se chama `simulador.exe`, então rode:

    ./simulador.exe

Se quiser recompilar do zero (apagando os arquivos gerados antes):

    make clean
    make
# Simulador de Cubo Mágico 2x2x2 com IA

Simulador de cubo mágico 2x2x2 com modo de jogo manual (visualização 3D) e
resolução automática por três algoritmos de busca de Inteligência Artificial:
**Busca em Largura (BFS)**, **Busca em Profundidade Limitada Iterativa (IDDFS)**
e **Busca A\*** com heurística.

Projeto acadêmico (PUC-Campinas, disciplina de IA, grupo T1) desenvolvido em
C (lógica do cubo e buscas) e C++ (interface 3D com OpenGL/GLFW).

## Status

- Modo manual (jogar com teclado, visualização 3D): funcionando
- Busca em Largura (BFS): funcionando
- Busca em Profundidade Limitada Iterativa (IDDFS): funcionando
- Busca A\* com heurística: funcionando

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

## Como usar

O menu principal oferece 5 opções:

1. **Jogo Manual** — abre a visualização 3D e permite girar o cubo pelo teclado.
2. **Busca em Largura** — pede uma seed, embaralha o cubo e resolve com BFS.
3. **Busca em Profundidade Limitada Iterativa** — mesma coisa, com IDDFS.
4. **Busca Heurística (A\*)** — mesma coisa, com A\*.
5. **Sair**

Nas opções 2, 3 e 4, o programa pede uma **seed** de embaralhamento. Usar a
mesma seed sempre gera o mesmo embaralhamento, o que permite comparar as três
buscas resolvendo exatamente o mesmo cubo. Ao final, o programa mostra:

- se encontrou solução;
- a quantidade de estados analisados durante a busca;
- a sequência de movimentos da solução;
- uma animação 3D do cubo embaralhando e depois se resolvendo.

### Controles do modo manual

| Tecla | Ação |
|---|---|
| `R` / `Shift+R` | Gira face Direita (e sentido contrário) |
| `E` / `Shift+E` | Gira face Esquerda (e sentido contrário) |
| `F` / `Shift+F` | Gira face Superior (e sentido contrário) |
| `D` / `Shift+D` | Gira face Inferior (e sentido contrário) |
| `C` / `Shift+C` | Gira face Frontal (e sentido contrário) |
| `V` / `Shift+V` | Gira face Posterior (e sentido contrário) |
| `B` | Embaralha o cubo automaticamente |
| Mouse (arrastar) | Gira a câmera |
| `ESC` | Volta ao menu |

## Como os algoritmos funcionam

As três buscas compartilham o **mesmo laço genérico** (`src/laco_generico.c`),
que não muda independente do algoritmo usado:

```
Adicionar estado inicial na estrutura
Enquanto a estrutura não estiver vazia:
    Remover próximo estado da estrutura
    Avaliar estado
    Se estado final -> mostrar solução e encerrar
    Gerar estados sucessores e adicionar na estrutura
Retornar "Sem solução"
```

O que muda entre BFS, IDDFS e A\* é só a estrutura de dados usada e a forma
de inserir/remover dela, através de uma interface de ponteiros de função
(`InterfaceEstrutura`):

- **BFS** usa uma **fila** (`src/busca_bfs.c`).
- **IDDFS** usa uma **pilha**, repetindo a busca com limites de profundidade
  crescentes (`src/busca_iddfs.c`).
- **A\*** usa uma **fila de prioridade** ordenada por `f = profundidade + heurística`
  (`src/busca_astar.c`).

### Estado e função sucessora

O estado do cubo (`EstadoCubo`, em `include/cubo_estado.h`) guarda os 8 cantos
do cubo: a posição de cada peça (`pecas[8]`) e sua orientação (`orientacao[8]`,
0 a 2). O cubo está resolvido quando `pecas[i] == i` e `orientacao[i] == 0`
para todo `i`. A função sucessora (`estado_gerar_sucessores`) aplica os 12
movimentos possíveis (`MOV_DIR`, `MOV_DIR_INV`, `MOV_ESQ`, ...) e gera os 12
estados filhos de cada estado.

### Heurística do A\*

```c
static int heuristica(const EstadoCubo *estado)
{
    int errado = 0;
    for (int i = 0; i < 8; i++)
        if (estado->pecas[i] != i || estado->orientacao[i] != 0)
            errado++;
    return (errado + 3) / 4; // ceil(errado / 4)
}
```

Conta quantos cantos estão fora do lugar (posição ou orientação erradas) e
divide por 4, arredondando pra cima. Como cada movimento gira uma face inteira
e mexe em exatamente 4 cantos ao mesmo tempo, nenhum movimento corrige mais de
4 peças de uma vez — logo, `ceil(errado / 4)` nunca superestima quantos
movimentos realmente faltam. Isso torna a heurística **admissível**, o que
garante que o A\* sempre encontre a solução ótima (o menor número de
movimentos possível).

## Estrutura do projeto

```
├── cubo.cpp                     # Interface 3D (C++, OpenGL/GLFW): jogo manual e visualização das soluções
├── cubo_visual.h                # Funções compartilhadas entre o menu (C) e a interface 3D (C++)
├── menu.c                       # Menu principal, embaralhamento e integração com as buscas
├── include/
│   ├── cubo_estado.h            # Estado do cubo, movimentos e função sucessora
│   ├── biblioteca_fila_pilha.h  # Fila, pilha e fila de prioridade usadas pelas buscas
│   ├── laco_generico.h          # Laço genérico de busca (comum às 3 buscas)
│   └── busca_bfs.h / busca_iddfs.h / busca_astar.h
├── src/
│   ├── cubo_estado.c            # Implementação do estado, movimentos e sucessora
│   ├── laco_generico.c          # Laço genérico e reconstrução do caminho da solução
│   └── busca_bfs.c / busca_iddfs.c / busca_astar.c
└── tests/                       # Testes automatizados (ver abaixo)
```

## Testes automatizados

A pasta `tests/` tem programas separados que verificam se partes do código
funcionam como esperado, sem precisar testar tudo manualmente pelo menu.
Cada um compila e roda sozinho:

    gcc -Iinclude tests/teste_estado.c src/cubo_estado.c -o teste_estado
    ./teste_estado

    gcc -Iinclude tests/teste_bfs.c src/cubo_estado.c src/laco_generico.c src/busca_bfs.c -o teste_bfs
    ./teste_bfs

    gcc -Iinclude tests/teste_iddfs.c src/cubo_estado.c src/laco_generico.c src/busca_iddfs.c -o teste_iddfs
    ./teste_iddfs
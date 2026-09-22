SIMULADOR = simulador
ifeq ($(OS),Windows_NT)
    SIMULADOR = simulador.exe
endif

# -Iinclude: fala pro compilador procurar os headers (.h) dentro da pasta include/
# sem isso, qualquer #include "busca_bfs.h" (ou qualquer header que esta em include/) nao compila
CXXFLAGS = -std=c++17 -Iinclude $(shell pkg-config --cflags glfw3)
CFLAGS = -Iinclude

ifeq ($(OS),Windows_NT)
    LIBS = $(shell pkg-config --libs glfw3) -lopengl32 -lgdi32
else ifeq ($(shell uname -s),Darwin)
    LIBS = $(shell pkg-config --libs glfw3) -framework OpenGL
else
    LIBS = $(shell pkg-config --libs glfw3) -lGL -ldl -lpthread -lX11
endif

# lista de todos os .o que o executavel final precisa
# cada busca (bfs, iddfs, e depois a*) mais o laco generico e o estado do cubo
# viram um .o separado, e no final o g++ linka tudo junto
OBJS = menu.o cubo.o laco_generico.o \
       cubo_estado.o busca_bfs.o \
       busca_iddfs.o busca_astar.o

all: $(SIMULADOR)

$(SIMULADOR): $(OBJS)
	g++ $(OBJS) -o $(SIMULADOR) $(LIBS)

menu.o: menu.c cubo_visual.h
	gcc $(CFLAGS) -c menu.c -o menu.o

cubo.o: cubo.cpp cubo_visual.h
	g++ $(CXXFLAGS) -c cubo.cpp -o cubo.o

laco_generico.o: src/laco_generico.c include/laco_generico.h
	gcc $(CFLAGS) -c src/laco_generico.c -o laco_generico.o

cubo_estado.o: src/cubo_estado.c include/cubo_estado.h
	gcc $(CFLAGS) -c src/cubo_estado.c -o cubo_estado.o

busca_bfs.o: src/busca_bfs.c include/busca_bfs.h
	gcc $(CFLAGS) -c src/busca_bfs.c -o busca_bfs.o

busca_iddfs.o: src/busca_iddfs.c include/busca_iddfs.h
	gcc $(CFLAGS) -c src/busca_iddfs.c -o busca_iddfs.o

busca_astar.o: src/busca_astar.c include/busca_astar.h
	gcc $(CFLAGS) -c src/busca_astar.c -o busca_astar.o

clean:
	rm -f *.o $(SIMULADOR)

.PHONY: all clean
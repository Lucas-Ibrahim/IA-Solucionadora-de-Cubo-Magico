SIMULADOR = simulador
ifeq ($(OS),Windows_NT)
    SIMULADOR = simulador.exe
endif

CXXFLAGS = -std=c++17 $(shell pkg-config --cflags glfw3)

ifeq ($(OS),Windows_NT)
    LIBS = $(shell pkg-config --libs glfw3) -lopengl32 -lgdi32
else ifeq ($(shell uname -s),Darwin)
    LIBS = $(shell pkg-config --libs glfw3) -framework OpenGL
else
    LIBS = $(shell pkg-config --libs glfw3) -lGL -ldl -lpthread -lX11
endif

all: $(SIMULADOR)

$(SIMULADOR): menu.o cubo.o
	g++ menu.o cubo.o -o $(SIMULADOR) $(LIBS)

menu.o: menu.c cubo_visual.h
	gcc -c menu.c -o menu.o

cubo.o: cubo.cpp cubo_visual.h
	g++ $(CXXFLAGS) -c cubo.cpp -o cubo.o

clean:
	rm -f *.o $(SIMULADOR)

.PHONY: all clean
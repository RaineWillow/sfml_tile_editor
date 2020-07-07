CXX=g++
CFLAGS=
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

SOURCES=src/main.cpp
CORE=src/core/window.cpp src/core/resource_manager.cpp
SCENE=src/scene/tile_editor.cpp
GUI=src/gui/gui_manager.cpp
UTILS=src/utils/controller.cpp

all:
	$(CXX) $(CFLAGS) -o game.exe $(SOURCES) $(CORE) $(SCENE) $(GUI) $(UTILS) $(LIBS)

.PHONY: run
run:
	./game.exe
.PHONY: crun
crun: all
	./game.exe
.PHONY: clean
clean:
	rm -f game.exe

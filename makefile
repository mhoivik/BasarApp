CXX = g++
FILES = include/imgui/imgui.cpp include/imgui/imgui.h  include/imgui/imgui_demo.cpp include/imgui/imgui_draw.cpp include/imgui/imgui_tables.cpp include/imgui/imgui_widgets.cpp include/imgui/backends/imgui_impl_glfw.cpp include/imgui/backends/imgui_impl_opengl3.cpp
INCLUDE = -Iinclude -Iinclude/imgui -Iinclude/imgui/backends
LIBS = -Llibs -lglfw3 -lopengl32 -lgdi32
SRC = src/main.cpp

DEBUG = -o bin/debug/main -Wall -Wextra -g
RELEASE = -o bin/release/main -Wall -Wextra -Ofast
DIST = -o bin/dist/main -DNDEBUG -Ofast -s

debug:
	$(CXX) $(SRC) $(FILES) $(DEBUG) $(INCLUDE) $(LIBS) && .\bin\debug\main.exe

release:
	$(CXX) $(SRC) $(FILES) $(RELEASE) $(INCLUDE) $(LIBS) && .\bin\release\main.exe

dist:
	$(CXX) $(SRC) $(FILES) $(DIST) $(INCLUDE) $(LIBS) && .\bin\dist\main.exe

clean:
	rm -rf bin/debug/main
	rm -rf bin/release/main
	rm -rf bin/dist/main

setup:
	mkdir -p bin
	mkdir -p bin/debug
	mkdir -p bin/release
	mkdir -p bin/dist


CXX = g++
INCLUDE = -Iinclude/imgui/*.cpp -Iinclude/imgui/*.h -Iinlude/imgui/backends/*.cpp -Iinlude/imgui/backends/*.cpp -Iinclude
CXXLIBS = -lglfw
SRC = src/main.cpp

DEBUG = -o bin/debug/main -Wall -Wextra -g
RELEASE =  -o bin/release/main -Wall -Wextra -Ofast
DIST = -o bin/dist/main -DNDEBUG -Ofast -s

debug:
	$(CXX) $(SRC) $(INCLUDE) $(DEBUG) $(CXXLIBS)
	./bin/debug/main

release:
	$(CXX) $(SRC) $(INCLUDE) $(RELEASE) $(CXXLIBS)
	./bin/release/main

dist:
	$(CXX) $(SRC) $(INCLUDE) $(DIST) $(CXXLIBS)
	./bin/dist/main

clean:
	rm -rf bin/debug/main
	rm -rf bin/release/main
	rm -rf bin/dist/main

setup:
	mkdir -p bin
	mkdir -p bin/debug
	mkdir -p bin/release
	mkdir -p bin/dist

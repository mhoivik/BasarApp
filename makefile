CXX = g++

SRC = src/main.cpp

DEBUG = -o bin/debug/main -Wall -Wextra -g
RELEASE =  -o bin/release/main -Wall -Wextra -Ofast
DIST = -o bin/dist/main -DNDEBUG -Ofast -s

debug:
	$(CXX) $(CXXLIBS) $(SRC) $(DEBUG)
	./bin/debug/main
release:
	$(CXX) $(CXXLIBS) $(SRC) $(RELEASE)
	./bin/release/main
dist:
	$(CXX) $(CXXLIBS) $(SRC) $(DIST)
	./bin/dist/main
clean:
	rm -rf bin/debug/main
	rm -rf bin/release/main
	rm -rf bin/dist/main

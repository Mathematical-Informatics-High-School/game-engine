CC := g++
CFLAGS := -Wall
LIBS := -lglfw -lGLEW -lGL -lSOIL
INCLUDE := -Iinclude

SRC := $(wildcard src/*.cpp)
INC := $(wildcard include/*.cpp)
OBJ := $(patsubst src/%.cpp, build/%.o, $(SRC)) $(patsubst include/%.cpp, build/%.o, $(INC))



all: build/nostalgia3D

build/nostalgia3D: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

build/%.o: src/%.cpp
	$(CC) -c $< $(CFLAGS) $(LIBS) -o $@ $(INCLUDE)

build/%.o: include/%.cpp
	$(CC) -c $< $(CFLAGS) $(LIBS) -o $@

clean:
	rm -f build/*.o

.PHONY: clean

run: build/nostalgia3D
	./build/nostalgia3D

.PHONY: run
DEBUG=no
CC=g++

ifeq ($(DEBUG), yes)
	CFLAGS=-std=c++20 -Wall -W -pthread -fstack-protector-all
else
	CFLAGS=-std=c++20 -O2 -pthread -fstack-protector-all
endif

LDFLAGS=-lGL -lGLEW -lglfw -lstb -lassimp -lpthread

OBJECT := $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard src/Core/*.cpp)) $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard src/Render/*.cpp)) $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard src/Manager/*.cpp)) $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard src/Debug/*.cpp)) $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard src/Input/*.cpp)) $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard src/Window/*.cpp)) $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard src/Scene/*.cpp)) $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard src/Scene/Camera/*.cpp)) $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard src/Loader/*.cpp)) $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard vendor/imgui/*.cpp)) $(patsubst %.cpp, obj/$(notdir %.o), $(wildcard src/UI/*.cpp))
OBJECTPATH = $(notdir $(OBJECT))

.PHONY: clean

# Standard
bin/app.out: obj/main.o $(OBJECT)
	$(CC) $(addprefix obj/, $(OBJECTPATH)) obj/main.o -o $@ $(LDFLAGS)

run:
	__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia ./bin/app.out

obj/main.o: src/main.cpp src/Core/Application.hpp
	$(CC) $(CFLAGS) -c $<
	mv *.o obj/

obj/%.o : %.cpp %.hpp
	$(CC) $(CFLAGS) -c $<
	mv *.o obj/

# Clean
clean:
	rm -r obj/*.o bin/app.out
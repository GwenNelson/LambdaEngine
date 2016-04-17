CC      = gcc
CFLAGS  = -g -O2 -Wall -fPIC `sdl2-config --cflags`
LDFLAGS = 
LIBS    = -lphysfs -ldl
O       = build

ENGINE_OBJS        = $(O)/engine/vfs_pak.o \
                     $(O)/engine/vfs_init.o \
                     $(O)/engine/vfs_io.o \
                     $(O)/engine/lib_tools.o \
                     $(O)/engine/lib_cache.o
LAMBDA_VIDEO_OBJS  = $(O)/lambda_video/v_init.o
LAMBDA_RENDER_OBJS = $(O)/soil/image_helper.o \
                     $(O)/soil/stb_image_aug.o \
                     $(O)/soil/image_DXT.o \
                     $(O)/soil/SOIL.o \
                     $(O)/lambda_render/r_init.o \
                     $(O)/lambda_render/r_primitives.o

CORE01_LIBS        = build/core01/libs/lambda_video.so \
                     build/core01/libs/lambda_render.so

dist/bin/lambda: $(ENGINE_OBJS) $(O)/engine/l_main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(ENGINE_OBJS) $(O)/engine/l_main.o -o $@ $(LIBS)

build/core01/libs/lambda_video.so: $(LAMBDA_VIDEO_OBJS)
	$(CC) -shared -o $(O)/core01/libs/lambda_video.so -framework OpenGL `sdl2-config --libs` $(LAMBDA_VIDEO_OBJS)

build/core01/libs/lambda_render.so: $(LAMBDA_RENDER_OBJS)
	$(CC) -shared -o $(O)/core01/libs/lambda_render.so -framework OpenGL  $(LAMBDA_RENDER_OBJS)

dist/data/core01.pak: $(CORE01_LIBS) textures/logo.png
	cp -rv textures build/core01/
	cd build/core01/libs; ../../../tools/build_md5sums.sh
	cd build/core01; zip -r ../../dist/data/core01.pak *

dist/data/core02.pak: sample/gameinfo.def
	cp sample/gameinfo.def build/core02/
	cd build/core02/libs; ../../../tools/build_md5sums.sh
	cd build/core02; zip ../../dist/data/core02.pak *

enginebin: dist/bin/lambda

corepaks: dist/data/core01.pak dist/data/core02.pak

all: enginebin corepaks

clean:
	rm -f dist/bin/*
	rm -f dist/data/*
	rm -f build/core01/libs/*
	rm -f build/core02/gameinfo.def
	rm -f build/engine/*.o

$(O)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Please set dir for temp header files
#HEADERS_DIR=include
HEADERS_DIR=${HOME}/download/include

INCLUDE=-I. -Icommon -Imodule -Ifile -Iparse -Iutopia -I$(HEADERS_DIR) -Iprime -Ichars
#PKGCFLAGS=`pkg-config --cflags freetype2`
#PKGLIBS=`pkg-config --libs glu` `pkg-config --libs glfw3` `pkg-config --libs freetype2` -lglut -lGLEW
CFLAGS=-Wall -g -D_DEBUG ${INCLUDE} ${PKGCFLAGS}
LDLIBS=-lm ${PKGLIBS}
MOD_H=$(shell find $(SOURCEDIR) -name '*.mod.h')
OBJECTS_H=$(MOD_H:%.mod.h=%.h)

# Uncomment next string (remove '#') after mod_to_h compile
include $(OBJECTS_H)

%.h: %.mod.h
	mod_to_h/mod_to_h $^ $(HEADERS_DIR)/


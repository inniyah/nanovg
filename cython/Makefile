#!/usr/bin/make -f

# sudo apt install pkg-config cython3 libpython3-dev libsdl2-dev libsdl2-image-dev libglew-dev

PACKAGES= python3-embed sdl2 SDL2_image gl glu glew

NUM_CPUS ?= $(shell grep -c '^processor' /proc/cpuinfo)

ARCH_NAME := $(shell '$(TRGT)gcc' -dumpmachine)

# See: https://peps.python.org/pep-3149/
PYMOD_SOABI := $(shell python3 -c "import sysconfig; print(sysconfig.get_config_var('SOABI'));")
PYMOD_SUFFIX := $(shell python3 -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'));")

TRGT=

CC   = $(TRGT)gcc
CXX  = $(TRGT)g++
AS   = $(TRGT)gcc -x assembler-with-cpp

LD   = $(TRGT)g++
AR   = $(TRGT)ar rvc

RM= rm --force --verbose

PYTHON= python3
CYTHON= cython3

PKGCONFIG= pkg-config

ifndef PACKAGES
PKG_CONFIG_CFLAGS=
PKG_CONFIG_LDFLAGS=
PKG_CONFIG_LIBS=
else
PKG_CONFIG_CFLAGS=`pkg-config --cflags $(PACKAGES)`
PKG_CONFIG_LDFLAGS=`pkg-config --libs-only-L $(PACKAGES)`
PKG_CONFIG_LIBS=`pkg-config --libs-only-l $(PACKAGES)`
endif

CFLAGS= \
	-Wall \
	-fwrapv \
	-fstack-protector-strong \
	-Wall \
	-Wformat \
	-Werror=format-security \
	-Wdate-time \
	-D_FORTIFY_SOURCE=2 \
	-fPIC

LDFLAGS= \
	-Wl,-O1 \
	-Wl,-Bsymbolic-functions \
	-Wl,-z,relro \
	-Wl,--as-needed \
	-Wl,--no-undefined \
	-Wl,--no-allow-shlib-undefined \
	-Wl,-Bsymbolic-functions \
	-Wl,--dynamic-list-cpp-new \
	-Wl,--dynamic-list-cpp-typeinfo

CYFLAGS= \
	-3 \
	--cplus \
	-X language_level=3 \
	-X boundscheck=False

CSTD=-std=gnu17
CPPSTD=-std=gnu++17

OPTS= -O2 -g

DEFS= \
	-DNDEBUG \
	-D_LARGEFILE64_SOURCE \
	-D_FILE_OFFSET_BITS=64 \
	-DGL_GLEXT_PROTOTYPES

INCS= \
	-I../src

CYINCS= \
	-I.

LIBS= \

PYX_NAMES= $(subst .pyx,,$(foreach F,$(shell find . -name *.pyx),$(lastword $(subst /, ,$F))))

PYX_SRCS= $(PYX_NAMES:%=./%.pyx)
PYX_CPPS= $(subst .pyx,.cpp,$(PYX_SRCS))
PYX_OBJS= $(subst .pyx,.o,$(PYX_SRCS))

all: libs nanovg$(PYMOD_SUFFIX)

libs: nanovg.$(ARCH_NAME).so

NANOVG_OBJS= \
	nanovg/nanovg.o \
	nanovg/android.o \
	nanovg/nanovg_gl2.o \
	nanovg/nanovg_gl2_utils.o \
	nanovg/nanovg_gl3.o \
	nanovg/nanovg_gl3_utils.o \
	nanovg/nanovg_gles2.o \
	nanovg/nanovg_gles2_utils.o \
	nanovg/nanovg_gles3.o \
	nanovg/nanovg_gles3_utils.o \
	nanovg/nanosvg.o \
	nanovg/nanosvgrast.o \
	nanovg/oui.o \
	nanovg/blendish.o

nanovg.$(ARCH_NAME).so: $(NANOVG_OBJS)
	$(LD) -shared $(CPPSTD) $(CSTD) $(LDFLAGS) $(PKG_CONFIG_LDFLAGS) -o $@ $^ $(LIBS) $(PKG_CONFIG_LIBS)

nanovg$(PYMOD_SUFFIX): nanovg.o


%.bin:
	$(LD) $(CPPSTD) $(CSTD) $(LDFLAGS) $(PKG_CONFIG_LDFLAGS) -o $@ $^ $(LIBS) $(PKG_CONFIG_LIBS)

%$(PYMOD_SUFFIX):
	$(LD) -shared $(CPPSTD) $(CSTD) $(LDFLAGS) $(PKG_CONFIG_LDFLAGS) -o $@ $^ $(LIBS) $(PKG_CONFIG_LIBS)

%.$(ARCH_NAME).so:
	$(LD) -shared -Wl,-soname,$@ $(CPPSTD) $(CSTD) $(LDFLAGS) $(PKG_CONFIG_LDFLAGS) -o $@ $^ $(LIBS) $(PKG_CONFIG_LIBS)

lib%.so:
	$(LD) -shared $(CPPSTD) $(CSTD) $(LDFLAGS) $(PKG_CONFIG_LDFLAGS) -o $@ $^ $(LIBS) $(PKG_CONFIG_LIBS)

%.a:
	$(AR) $@ $^

%.o: %.cpp
	$(CXX) $(CPPSTD) $(OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

%.o: %.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

%.cpp %.h %_api.h: %.pyx
	$(CYTHON) $(CYFLAGS) $(CYINCS) -o $*.cpp $<

nanovg/nanovg_gl2.o: ../src/nanovg_gl.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) -DNANOVG_GL2 -DNANOVG_USE_GLEW $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

nanovg/nanovg_gl2_utils.o: ../src/nanovg_gl_utils.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) -DNANOVG_GL2 -DNANOVG_USE_GLEW $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

nanovg/nanovg_gl3.o: ../src/nanovg_gl.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) -DNANOVG_GL3 -DNANOVG_USE_GLEW $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

nanovg/nanovg_gl3_utils.o: ../src/nanovg_gl_utils.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) -DNANOVG_GL3 -DNANOVG_USE_GLEW $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

nanovg/nanovg_gles2.o: ../src/nanovg_gl.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) -DNANOVG_GLES2 $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

nanovg/nanovg_gles2_utils.o: ../src/nanovg_gl_utils.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) -DNANOVG_GLES2 $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

nanovg/nanovg_gles3.o: ../src/nanovg_gl.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) -DNANOVG_GLES3 $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

nanovg/nanovg_gles3_utils.o: ../src/nanovg_gl_utils.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) -DNANOVG_GLES3 $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

nanovg/%.o: ../src/%.cpp
	$(CXX) $(CPPSTD) $(OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

nanovg/%.o: ../src/%.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)


info:
	@echo PYX_NAMES: $(PYX_NAMES)
	@echo PYX_SRCS:  $(PYX_SRCS)
	@echo PYX_OBJS:  $(PYX_OBJS)

clean:
	$(RM) $(PYX_OBJS) $(HUB_OBJS) $(SHADERS_OBJS) $(TMX_OBJS)
	$(RM) $(subst .pyx,.cpp,$(PYX_SRCS))
	$(RM) $(subst .pyx,_api.cpp,$(PYX_SRCS))
	$(RM) $(subst .pyx,.h,$(PYX_SRCS))
	$(RM) $(subst .pyx,_api.h,$(PYX_SRCS))
	@find . -name '*.o' -exec $(RM) {} +
	@find . -name '*.a' -exec $(RM) {} +
	@find . -name '*.so' -exec $(RM) {} +
	@find . -name '*.pyc' -exec $(RM) {} +
	@find . -name '*.pyo' -exec $(RM) {} +
	@find . -name '*.bak' -exec $(RM) {} +
	@find . -name '*~' -exec $(RM) {} +
	@$(RM) core

.PHONY: all clean info

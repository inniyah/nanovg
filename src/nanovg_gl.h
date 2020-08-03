//
// Copyright (c) 2009-2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef NANOVG_GL_H_F380EF20_CDA3_11EA_AF55_D3B6DB88CFCC
#define NANOVG_GL_H_F380EF20_CDA3_11EA_AF55_D3B6DB88CFCC

#include "nanovg.h"

#ifdef __cplusplus
extern "C" {
#endif

// Create flags

enum NVGcreateFlags {
	// Flag indicating if geometry based anti-aliasing is used (may not be needed when using MSAA).
	NVG_ANTIALIAS = 1<<0,
	// Flag indicating if strokes should be drawn using stencil buffer. The rendering will be a little
	// slower, but path overlaps (i.e. self-intersecting or sharp turns) will be drawn just once.
	NVG_STENCIL_STROKES = 1<<1,
	// Flag indicating that additional debug checks are done.
	NVG_DEBUG = 1<<2,
};

// Define VTable with pointers to the functions for a each OpenGL (ES) version.

typedef struct {
	const char *name;
	NVGcontext* (*createContext)(int flags);
	void (*deleteContext) (NVGcontext* ctx);
	int (*createImageFromHandle) (NVGcontext* ctx, unsigned int textureId, int w, int h, int flags);
	unsigned int (*getImageHandle) (NVGcontext* ctx, int image);
} NanoVG_GL_Functions_VTable;

// Create NanoVG contexts for different OpenGL (ES) versions.

NVGcontext* nvgCreateGL2(int flags);
void nvgDeleteGL2(NVGcontext* ctx);

int nvglCreateImageFromHandleGL2(NVGcontext* ctx, GLuint textureId, int w, int h, int flags);
GLuint nvglImageHandleGL2(NVGcontext* ctx, int image);

NVGcontext* nvgCreateGL3(int flags);
void nvgDeleteGL3(NVGcontext* ctx);

int nvglCreateImageFromHandleGL3(NVGcontext* ctx, GLuint textureId, int w, int h, int flags);
GLuint nvglImageHandleGL3(NVGcontext* ctx, int image);

NVGcontext* nvgCreateGLES2(int flags);
void nvgDeleteGLES2(NVGcontext* ctx);

int nvglCreateImageFromHandleGLES2(NVGcontext* ctx, GLuint textureId, int w, int h, int flags);
GLuint nvglImageHandleGLES2(NVGcontext* ctx, int image);

NVGcontext* nvgCreateGLES3(int flags);
void nvgDeleteGLES3(NVGcontext* ctx);

int nvglCreateImageFromHandleGLES3(NVGcontext* ctx, GLuint textureId, int w, int h, int flags);
GLuint nvglImageHandleGLES3(NVGcontext* ctx, int image);

// These are additional flags on top of NVGimageFlags.
enum NVGimageFlagsGL {
	NVG_IMAGE_NODELETE = 1<<16, // Do not delete GL texture handle.
};

// Create VTables for different OpenGL (ES) versions.

extern const NanoVG_GL_Functions_VTable NanoVG_GL2_Functions_VTable;
extern const NanoVG_GL_Functions_VTable NanoVG_GL3_Functions_VTable;
extern const NanoVG_GL_Functions_VTable NanoVG_GLES2_Functions_VTable;
extern const NanoVG_GL_Functions_VTable NanoVG_GLES3_Functions_VTable;

#ifdef __cplusplus
}
#endif

#endif // NANOVG_GL_H_F380EF20_CDA3_11EA_AF55_D3B6DB88CFCC

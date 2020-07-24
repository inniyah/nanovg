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

#include "nanovg_gl.h"

#ifndef NANOVG_GL_UTILS_H_F380EE76_CDA3_11EA_AF54_FB2296181D7D
#define NANOVG_GL_UTILS_H_F380EE76_CDA3_11EA_AF54_FB2296181D7D

#ifdef __cplusplus
extern "C" {
#endif

struct NVGLUframebuffer {
	NVGcontext* ctx;
	GLuint fbo;
	GLuint rbo;
	GLuint texture;
	int image;
};
typedef struct NVGLUframebuffer NVGLUframebuffer;

// Helper function to create GL frame buffers for different OpenGL (ES) versions.

void nvgluBindFramebufferGL2(NVGLUframebuffer* fb);
NVGLUframebuffer* nvgluCreateFramebufferGL2(NVGcontext* ctx, int w, int h, int imageFlags);
void nvgluDeleteFramebufferGL2(NVGLUframebuffer* fb);

void nvgluBindFramebufferGL3(NVGLUframebuffer* fb);
NVGLUframebuffer* nvgluCreateFramebufferGL3(NVGcontext* ctx, int w, int h, int imageFlags);
void nvgluDeleteFramebufferGL3(NVGLUframebuffer* fb);

void nvgluBindFramebufferGLES2(NVGLUframebuffer* fb);
NVGLUframebuffer* nvgluCreateFramebufferGLES2(NVGcontext* ctx, int w, int h, int imageFlags);
void nvgluDeleteFramebufferGLES2(NVGLUframebuffer* fb);

void nvgluBindFramebufferGLES3(NVGLUframebuffer* fb);
NVGLUframebuffer* nvgluCreateFramebufferGLES3(NVGcontext* ctx, int w, int h, int imageFlags);
void nvgluDeleteFramebufferGLES3(NVGLUframebuffer* fb);

#ifdef __cplusplus
}
#endif

#endif // NANOVG_GL_UTILS_H_F380EE76_CDA3_11EA_AF54_FB2296181D7D

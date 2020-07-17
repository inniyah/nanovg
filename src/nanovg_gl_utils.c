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

#ifdef NANOVG_GLEW
#  include <GL/glew.h>
#endif

#ifdef NANOVG_GLES2
#  include <GLES2/gl2.h>
#  include <GLES2/gl2ext.h>
#endif

#ifdef NANOVG_GLES3
#  include <GLES3/gl3.h>
#endif

#include <GL/gl.h>

#include "nanovg_gl_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#if defined(NANOVG_GL3) || defined(NANOVG_GLES2) || defined(NANOVG_GLES3)
// FBO is core in OpenGL 3>.
#	define NANOVG_FBO_VALID 1
#elif defined(NANOVG_GL2)
// On OS X including glext defines FBO on GL2 too.
#	ifdef __APPLE__
#		include <OpenGL/glext.h>
#		define NANOVG_FBO_VALID 1
#	endif
#endif

static GLint defaultFBO = -1;

#if defined NANOVG_GL2
NVGLUframebuffer* nvgluCreateFramebufferGL2(NVGcontext* ctx, int w, int h, int imageFlags)
#elif defined NANOVG_GL3
NVGLUframebuffer* nvgluCreateFramebufferGL3(NVGcontext* ctx, int w, int h, int imageFlags)
#elif defined NANOVG_GLES2
NVGLUframebuffer* nvgluCreateFramebufferGLES2(NVGcontext* ctx, int w, int h, int imageFlags)
#elif defined NANOVG_GLES3
NVGLUframebuffer* nvgluCreateFramebufferGLES3(NVGcontext* ctx, int w, int h, int imageFlags)
#endif
{
#ifdef NANOVG_FBO_VALID
	GLint defaultFBO;
	GLint defaultRBO;
	NVGLUframebuffer* fb = NULL;

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
	glGetIntegerv(GL_RENDERBUFFER_BINDING, &defaultRBO);

	fb = (NVGLUframebuffer*)malloc(sizeof(NVGLUframebuffer));
	if (fb == NULL) goto error;
	memset(fb, 0, sizeof(NVGLUframebuffer));

	fb->image = nvgCreateImageRGBA(ctx, w, h, imageFlags | NVG_IMAGE_FLIPY | NVG_IMAGE_PREMULTIPLIED, NULL);

#if defined NANOVG_GL2
	fb->texture = nvglImageHandleGL2(ctx, fb->image);
#elif defined NANOVG_GL3
	fb->texture = nvglImageHandleGL3(ctx, fb->image);
#elif defined NANOVG_GLES2
	fb->texture = nvglImageHandleGLES2(ctx, fb->image);
#elif defined NANOVG_GLES3
	fb->texture = nvglImageHandleGLES3(ctx, fb->image);
#endif

	fb->ctx = ctx;

	// frame buffer object
	glGenFramebuffers(1, &fb->fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fb->fbo);

	// render buffer object
	glGenRenderbuffers(1, &fb->rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, fb->rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, w, h);

	// combine all
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb->texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fb->rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
#ifdef GL_DEPTH24_STENCIL8
		// If GL_STENCIL_INDEX8 is not supported, try GL_DEPTH24_STENCIL8 as a fallback.
		// Some graphics cards require a depth buffer along with a stencil.
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb->texture, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fb->rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
#endif // GL_DEPTH24_STENCIL8
			goto error;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, defaultRBO);
	return fb;
error:
	glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, defaultRBO);

#if defined NANOVG_GL2
	nvgluDeleteFramebufferGL2(fb);
#elif defined NANOVG_GL3
	nvgluDeleteFramebufferGL3(fb);
#elif defined NANOVG_GLES2
	nvgluDeleteFramebufferGLES2(fb);
#elif defined NANOVG_GLES3
	nvgluDeleteFramebufferGLES3(fb);
#endif

	return NULL;
#else
	NVG_NOTUSED(ctx);
	NVG_NOTUSED(w);
	NVG_NOTUSED(h);
	NVG_NOTUSED(imageFlags);
	return NULL;
#endif
}

#if defined NANOVG_GL2
void nvgluBindFramebufferGL2(NVGLUframebuffer* fb)
#elif defined NANOVG_GL3
void nvgluBindFramebufferGL3(NVGLUframebuffer* fb)
#elif defined NANOVG_GLES2
void nvgluBindFramebufferGLES2(NVGLUframebuffer* fb)
#elif defined NANOVG_GLES3
void nvgluBindFramebufferGLES3(NVGLUframebuffer* fb)
#endif
{
#ifdef NANOVG_FBO_VALID
	if (defaultFBO == -1) glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, fb != NULL ? fb->fbo : defaultFBO);
#else
	NVG_NOTUSED(fb);
#endif
}


#if defined NANOVG_GL2
void nvgluDeleteFramebufferGL2(NVGLUframebuffer* fb)
#elif defined NANOVG_GL3
void nvgluDeleteFramebufferGL3(NVGLUframebuffer* fb)
#elif defined NANOVG_GLES2
void nvgluDeleteFramebufferGLES2(NVGLUframebuffer* fb)
#elif defined NANOVG_GLES3
void nvgluDeleteFramebufferGLES3(NVGLUframebuffer* fb)
#endif
{
#ifdef NANOVG_FBO_VALID
	if (fb == NULL) return;
	if (fb->fbo != 0)
		glDeleteFramebuffers(1, &fb->fbo);
	if (fb->rbo != 0)
		glDeleteRenderbuffers(1, &fb->rbo);
	if (fb->image >= 0)
		nvgDeleteImage(fb->ctx, fb->image);
	fb->ctx = NULL;
	fb->fbo = 0;
	fb->rbo = 0;
	fb->texture = 0;
	fb->image = -1;
	free(fb);
#else
	NVG_NOTUSED(fb);
#endif
}

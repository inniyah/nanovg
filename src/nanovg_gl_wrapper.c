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
#include "nanovg_gl_wrapper.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static const NanoVG_GL_Functions_VTable NanoVG_GL2_Functions_VTable = {
	.name = "GL2",
	.createContext = &nvgCreateGL2,
	.deleteContext = &nvgDeleteGL2,
	.createImageFromHandle = &nvglCreateImageFromHandleGL2,
	.getImageHandle = &nvglImageHandleGL2,
};

static const NanoVG_GL_Functions_VTable NanoVG_GL3_Functions_VTable = {
	.name = "GL3",
	.createContext = &nvgCreateGL3,
	.deleteContext = &nvgDeleteGL3,
	.createImageFromHandle = &nvglCreateImageFromHandleGL3,
	.getImageHandle = &nvglImageHandleGL3,
};

static const NanoVG_GL_Functions_VTable NanoVG_GLES2_Functions_VTable = {
	.name = "GLES2",
	.createContext = &nvgCreateGLES2,
	.deleteContext = &nvgDeleteGLES2,
	.createImageFromHandle = &nvglCreateImageFromHandleGLES2,
	.getImageHandle = &nvglImageHandleGLES2,
};

static const NanoVG_GL_Functions_VTable NanoVG_GLES3_Functions_VTable = {
	.name = "GLES2",
	.createContext = &nvgCreateGLES3,
	.deleteContext = &nvgDeleteGLES3,
	.createImageFromHandle = &nvglCreateImageFromHandleGLES3,
	.getImageHandle = &nvglImageHandleGLES3,
};

const NanoVG_GL_Functions_VTable NanoVG_GL_Functions[] = {
	NanoVG_GL2_Functions_VTable,
	NanoVG_GL3_Functions_VTable,
	NanoVG_GLES2_Functions_VTable,
	NanoVG_GLES3_Functions_VTable,
};

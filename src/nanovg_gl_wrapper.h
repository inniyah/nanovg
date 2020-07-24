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

#include "nanovg.h"
#include "nanovg_gl.h"

#ifndef NANOVG_GL_WRAPPER_H_F380F2D6_CDA3_11EA_AF59_B71CDC8E1A6A
#define NANOVG_GL_WRAPPER_H_F380F2D6_CDA3_11EA_AF59_B71CDC8E1A6A

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	NANOVG_GL2,
	NANOVG_GL3,
	NANOVG_GLES2,
	NANOVG_GLES3
} NanoVG_GL_API;

typedef struct {
	const char *name;
	NVGcontext* (*createContext)(int flags);
	void (*deleteContext) (NVGcontext* ctx);
	int (*createImageFromHandle) (NVGcontext* ctx, GLuint textureId, int w, int h, int flags);
	GLuint (*getImageHandle) (NVGcontext* ctx, int image);
} NanoVG_GL_Functions_VTable;

extern const NanoVG_GL_Functions_VTable NanoVG_GL_Functions[];

#ifdef __cplusplus
}
#endif

#endif // NANOVG_GL_WRAPPER_H_F380F2D6_CDA3_11EA_AF59_B71CDC8E1A6A

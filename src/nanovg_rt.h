//
// NanoRT(Software raytracer) backend for NanoVG.
//
// Copyright (c) 2015 Syoyo Fujita.
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

//
// nanovg_rt.h is based on nanovg_gl2.h
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
#ifndef NANOVG_RT_H_427F8D24_A468_11EC_A916_43AAE542C791
#define NANOVG_RT_H_427F8D24_A468_11EC_A916_43AAE542C791

#include "nanovg.h"
#include "nanort.h"

#ifdef __cplusplus
extern "C" {
#endif

// Create flags

enum NVGcreateFlags {
  // Flag indicating if geometry based anti-aliasing is used (may not be needed
  // when using MSAA).
  NVG_ANTIALIAS = 1 << 0,
  // Flag indicating if strokes should be drawn using stencil buffer. The
  // rendering will be a little
  // slower, but path overlaps (i.e. self-intersecting or sharp turns) will be
  // drawn just once.
  NVG_STENCIL_STROKES = 1 << 1,
  // Flag indicating that additional debug checks are done.
  NVG_DEBUG = 1 << 2,
};

NVGcontext *nvgCreateRT(int flags, int w, int h);
void nvgDeleteRT(NVGcontext *ctx);
void nvgClearBackgroundRT(NVGcontext *ctx, float r, float g, float b, float a); // Clear background.
unsigned char *nvgReadPixelsRT(NVGcontext *ctx); // Returns RGBA8 pixel data.

// These are additional flags on top of NVGimageFlags.
enum NVGimageFlagsRT {
  NVG_IMAGE_NODELETE = 1 << 16, // Do not delete RT texture handle.
};

int nvrtCreateImageFromHandle(NVGcontext *ctx, unsigned int textureId, int w,
                              int h, int flags);
unsigned int nvrtImageHandle(NVGcontext *ctx, int image);

#ifdef __cplusplus
}
#endif

#endif // NANOVG_RT_H_427F8D24_A468_11EC_A916_43AAE542C791

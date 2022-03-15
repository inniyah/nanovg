#include <stdio.h>
#include "nanovg.h"
#define NANOVG_RT_IMPLEMENTATION
#define NANORT_IMPLEMENTATION
#include "nanovg_rt.h"
#include "demo.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#ifdef __cplusplus
}
#endif

int main() {
  NVGcontext *vg = NULL;
  DemoData data;

  int winWidth = 1024;
  int winHeight = 1024;

  vg = nvgCreateRT(NVG_DEBUG, winWidth, winHeight);
  if (vg == NULL) {
    printf("Could not init nanovg.\n");
    return -1;
  }

  if (loadDemoData(vg, &data) == -1)
    return -1;

  float pxRatio = 1.0f;

  nvgClearBackgroundRT(vg, 0.3f, 0.3f, 0.32f, 1.0f);

  nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

  renderDemo(vg, 0, 0, winWidth, winHeight, 15.0f, 0.0f, &data);

  nvgEndFrame(vg);

  freeDemoData(vg, &data);

  unsigned char *rgba = nvgReadPixelsRT(vg);
  stbi_write_png("render.png", winWidth, winHeight, 4, rgba, winWidth * 4);

  nvgDeleteRT(vg);

  return 0;
}

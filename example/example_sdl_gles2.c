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

#include <stdio.h>
#include <stdlib.h>

#include <GLES2/gl2.h>

#include <SDL2/SDL.h>

#define NANOVG_GLES2
#include <nanovg/nanovg.h>
#include <nanovg/nanovg_gl.h>
#include <nanovg/nanovg_gl_utils.h>

int main(int argc, char **argv) {
    int flags = SDL_INIT_EVERYTHING & ~(SDL_INIT_TIMER | SDL_INIT_HAPTIC);
    if (SDL_Init(flags) < 0) {
        printf("ERROR: SDL_Init failed: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Try with these GL attributes
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    SDL_Window *window = SDL_CreateWindow("NanoVG Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 800,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

    if (!window) { // If it fails, try with more conservative options
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);

        window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 800,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

        if (!window) { // We were not able to create the window
            printf("ERROR: SDL_CreateWindow failed: %s", SDL_GetError());
            return EXIT_FAILURE;
        }
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    NVGcontext* vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (vg == NULL) {
        printf("ERROR: NanoVG init failed");
        return EXIT_FAILURE;
    }

    int winWidth = 0, winHeight = 0;
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    int fbWidth = winWidth;
    int fbHeight = winHeight;
    float fbRatio = (float)fbWidth / (float)winWidth;

    int quit=0;
    SDL_Event event;

    while (!quit) {
        SDL_PollEvent(&event);

        switch(event.type) {
            case SDL_QUIT:
                quit=1;
                break;
        }

        nvgBeginFrame(vg, winWidth, winHeight, fbRatio);
        nvgBeginPath(vg);
        nvgRect(vg, 100, 100, 100, 100);
        nvgFillColor(vg, nvgRGBA(192, 192, 192, 255));
        nvgFill(vg);
        nvgEndFrame(vg);

        SDL_GL_SwapWindow(window);
    }

    return EXIT_SUCCESS;
}

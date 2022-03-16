#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <nanovg.h>
#include <nanovg_gl.h>
#include <nanovg_gl_utils.h>

int main(int argc, char **argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return EXIT_FAILURE;
	}

	SDL_GLContext context;
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,          1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,    1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,    8);

	SDL_Window *window = SDL_CreateWindow(
		"SDL2/OpenGL/NanoVG",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1024,
		800,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
	);

	if (!window) {
		SDL_Log("fallback");
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
		window = SDL_CreateWindow(
			"SDL2/OpenGL/NanoVG",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, 1024, 800,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
		);

		if (!window) {
			return EXIT_FAILURE;
		}
	}

	context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, context);

	NVGcontext *vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
	if (vg == NULL) {
		return EXIT_FAILURE;
	}

	int winWidth, winHeight;
	int fbWidth, fbHeight;
	float pxRatio;

	SDL_GetWindowSize(window, &winWidth, &winHeight);
	fbWidth=winWidth; fbHeight=winHeight;

	pxRatio = (float)fbWidth / (float)winWidth;

	SDL_Event event;

	int running=1;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running =0;
			}
			if (event.type == SDL_MOUSEMOTION) {
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_RIGHT) {
				}
				if (event.button.button == SDL_BUTTON_MIDDLE) {
				}
				if (event.button.button == SDL_BUTTON_LEFT) {
					break;
				}
			}
			if (event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym ) {
					case SDLK_ESCAPE:
						running = 0;
						break;
					case SDLK_r:
					case SDLK_BACKSPACE:
						break;
					case SDLK_p:
					case SDLK_SPACE:
						break;
					default:
						break;
				}
			}
		}

		nvgBeginFrame(vg, winWidth, winHeight, pxRatio);
			nvgBeginPath(vg);
			nvgRect(vg, 300, 100, 120, 30);
			nvgFillColor(vg, nvgRGBA(255, 192, 0, 255));
			nvgFill(vg);
		nvgEndFrame(vg);

		SDL_GL_SwapWindow(window);
	}

	return EXIT_SUCCESS;
}

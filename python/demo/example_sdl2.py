#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os, sys
MY_PATH = os.path.normpath(os.path.abspath(os.path.dirname(__file__)))
sys.path.append(os.path.abspath(os.path.join(MY_PATH, '..')))

import ctypes

from OpenGL import GL

from NanoVG import *
from demo_data import DemoData
from perf import PerfGraph

import sdl2

def main():
    if sdl2.SDL_Init(sdl2.SDL_INIT_VIDEO) != 0:
        print(sdl2.SDL_GetError())
        return -1

    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_STENCIL_SIZE, 8)

    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_MAJOR_VERSION, 2)
    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_MINOR_VERSION, 0)
    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_PROFILE_MASK,  sdl2.SDL_GL_CONTEXT_PROFILE_CORE)

    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_DOUBLEBUFFER,          1)
    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_MULTISAMPLEBUFFERS,    1)
    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_MULTISAMPLESAMPLES,    8)

    window = sdl2.SDL_CreateWindow(b"SDL2 demo",
                                   sdl2.SDL_WINDOWPOS_UNDEFINED,
                                   sdl2.SDL_WINDOWPOS_UNDEFINED,
                                   1000, 600,
                                   sdl2.SDL_WINDOW_OPENGL | sdl2.SDL_WINDOW_RESIZABLE | sdl2.SDL_WINDOW_SHOWN | sdl2.SDL_WINDOW_ALLOW_HIGHDPI)

    if not window:
        sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_MULTISAMPLEBUFFERS, 0)
        sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_MULTISAMPLESAMPLES, 0)
        window = sdl2.SDL_CreateWindow(b"SDL2 demo",
                                       sdl2.SDL_WINDOWPOS_UNDEFINED,
                                       sdl2.SDL_WINDOWPOS_UNDEFINED,
                                       1000, 600,
                                       sdl2.SDL_WINDOW_OPENGL | sdl2.SDL_WINDOW_RESIZABLE | sdl2.SDL_WINDOW_SHOWN | sdl2.SDL_WINDOW_ALLOW_HIGHDPI)

    if not window:
        print(sdl2.SDL_GetError())
        return -1

    context = sdl2.SDL_GL_CreateContext(window);
    sdl2.SDL_GL_MakeCurrent(window, context);

    NanoVG.load_nanovg_library('libnanovg.so.0', output_error = True)

    vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG)
    if vg == None:
        print("Could not init nanovg.")
        exit()

    data = DemoData()
    if data.load(vg) == -1:
        exit()
    fps = PerfGraph(PerfGraph.GRAPH_RENDER_FPS, "Frame Time")

    fb_width = ctypes.c_int()
    fb_height = ctypes.c_int()

    mx = ctypes.c_int()
    my = ctypes.c_int()

    prevt = sdl2.SDL_GetTicks() / 1000.0
    fps.update(1.0 / 1000.0)

    running = True
    event = sdl2.SDL_Event()

    try:
        while running:
            t = sdl2.SDL_GetTicks() / 1000.0
            dt = t - prevt
            prevt = t
            fps.update(dt)

            sdl2.SDL_GetMouseState(ctypes.byref(mx), ctypes.byref(my))
            sdl2.SDL_GetWindowSize(window, ctypes.byref(fb_width), ctypes.byref(fb_height))
            ratio = fb_width.value / fb_height.value

            GL.glViewport(0, 0, fb_width.value, fb_height.value)
            GL.glClearColor(0.3, 0.3, 0.32, 1.0)
            GL.glClear(GL.GL_COLOR_BUFFER_BIT)

            nvgBeginFrame(vg, float(fb_width.value), float(fb_height.value), ratio)
            data.render(vg, mx.value, my.value, fb_width.value, fb_height.value, t, False)
            fps.render(vg, 5, 5)
            nvgEndFrame(vg)

            sdl2.SDL_GL_SwapWindow(window)

            while sdl2.SDL_PollEvent(ctypes.byref(event)) != 0:
                if event.type == sdl2.SDL_QUIT:
                    running = False
                elif event.type == sdl2.SDL_WINDOWEVENT:
                    if event.window.event == sdl2.SDL_WINDOWEVENT_RESIZED:
                        width = event.window.data1
                        height = event.window.data2
                        print(f"resize: {width}x{height}")
                        GL.glViewport(0, 0, width, height)
                    elif event.window.event == sdl2.SDL_WINDOWEVENT_CLOSE:
                        running = False

    finally:
        data.free(vg)
        nvgDeleteGL2(vg)

        sdl2.SDL_GL_DeleteContext(context)
        sdl2.SDL_DestroyWindow(window)
        sdl2.SDL_Quit()


if __name__ == '__main__':
    main()

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

# https://github.com/vaiorabbit/python-glfw
import GLFW
from GLFW import *

def key_callback_fn(window_handle, key, scancode, action, mods):
    if key == GLFW_KEY_ESCAPE and action == GLFW_PRESS:
        glfwSetWindowShouldClose(window_handle, 1)
key_callback = GLFWkeyfun(key_callback_fn)


def main():
    GLFW.load_glfw_library('libglfw.so.3')
    glfwInit()

    win = glfwCreateWindow(1000, 600, b"Python NanoVG/GLFW", None, None)
    glfwMakeContextCurrent(win)

    NanoVG.load_nanovg_library('libnanovg.so.0', output_error = True)

    vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG)
    if vg == None:
        print("Could not init nanovg.")
        exit()

    data = DemoData()
    if data.load(vg) == -1:
        exit()
    fps = PerfGraph(PerfGraph.GRAPH_RENDER_FPS, "Frame Time")

    glfwSetKeyCallback(win, key_callback)

    fb_width = ctypes.c_int()
    fb_height = ctypes.c_int()
    mx = ctypes.c_double()
    my = ctypes.c_double()

    glfwSwapInterval(0)
    glfwSetTime(0)

    prevt = glfwGetTime()

    try:
        while glfwWindowShouldClose(win) == 0:
            t = glfwGetTime()
            dt = t - prevt
            prevt = t
            fps.update(dt)

            glfwGetCursorPos(win, mx, my)
            glfwGetFramebufferSize(win, fb_width, fb_height)
            ratio = fb_width.value / fb_height.value

            GL.glViewport(0, 0, fb_width.value, fb_height.value)
            GL.glClearColor(0.3, 0.3, 0.32, 1.0)
            GL.glClear(GL.GL_COLOR_BUFFER_BIT)

            nvgBeginFrame(vg, float(fb_width.value), float(fb_height.value), ratio)
            data.render(vg, mx.value, my.value, fb_width.value, fb_height.value, t, False)
            fps.render(vg, 5, 5)
            nvgEndFrame(vg)

            glfwSwapBuffers(win)
            glfwPollEvents()
    finally:
        data.free(vg)
        nvgDeleteGL2(vg)

        glfwDestroyWindow(win)
        glfwTerminate()


if __name__ == '__main__':
    main()

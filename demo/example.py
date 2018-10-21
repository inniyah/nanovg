# For local/library development:
# import sys, os
# sys.path.append(os.pardir)
# sys.path.append('../../python-glfw_private')

import ctypes

import OpenGL.GL

# https://github.com/vaiorabbit/python-glfw
import GLFW
from GLFW import *

from NanoVG import *
from demo_data import DemoData
from perf import PerfGraph


def key_callback_fn(window_handle, key, scancode, action, mods):
    if key == GLFW_KEY_ESCAPE and action == GLFW_PRESS:
        glfwSetWindowShouldClose(window_handle, 1)
key_callback = GLFWkeyfun(key_callback_fn)


def main():
    GLFW.load_glfw_library('libglfw.dylib')
    glfwInit()

    win = glfwCreateWindow(1000, 600, b"Python NanoVG/GLFW", None, None)
    glfwMakeContextCurrent(win)

    NanoVG.load_nanovg_library('libnanovg_gl2.dylib', render_backend = 'gl2', output_error = True)
    nvgSetupGL2()
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

            OpenGL.GL.glViewport(0, 0, fb_width.value, fb_height.value)
            OpenGL.GL.glClearColor(0.3, 0.3, 0.32, 1.0)
            OpenGL.GL.glClear(OpenGL.GL.GL_COLOR_BUFFER_BIT)

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

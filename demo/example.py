import sys, os
sys.path.append(os.pardir)
sys.path.append('../../python-glfw_private')

import ctypes

from math import sin, cos, sqrt

import OpenGL.GL
import GLFW
from GLFW import *

from NanoVG import *

def key_callback_fn(window_handle, key, scancode, action, mods):
    if key == GLFW_KEY_ESCAPE and action == GLFW_PRESS:
        glfwSetWindowShouldClose(window_handle, 1)
key_callback = GLFWkeyfun(key_callback_fn)

def draw_eyes(vg, x, y, w, h, mx, my, t):
    gloss = NVGpaint()
    bg = NVGpaint()
    ex = w * 0.23
    ey = h * 0.5
    lx = x + ex
    ly = y + ey
    rx = x + w - ex
    ry = y + ey
    br = (ex if ex < ey else ey) * 0.5
    blink = 1 - (sin(t*0.5) ** 200)*0.8

    bg = nvgLinearGradient(vg, x,y+h*0.5,x+w*0.1,y+h, nvgRGBA(0,0,0,32), nvgRGBA(0,0,0,16))
    nvgBeginPath(vg)
    nvgEllipse(vg, lx+3.0,ly+16.0, ex,ey)
    nvgEllipse(vg, rx+3.0,ry+16.0, ex,ey)
    nvgFillPaint(vg, bg)
    nvgFill(vg)

    bg = nvgLinearGradient(vg, x,y+h*0.25,x+w*0.1,y+h, nvgRGBA(220,220,220,255), nvgRGBA(128,128,128,255))
    nvgBeginPath(vg)
    nvgEllipse(vg, lx,ly, ex,ey)
    nvgEllipse(vg, rx,ry, ex,ey)
    nvgFillPaint(vg, bg)
    nvgFill(vg)

    dx = (mx - rx) / (ex * 10)
    dy = (my - ry) / (ey * 10)
    d = sqrt(dx*dx+dy*dy)
    if d > 1.0:
        dx /= d
        dy /= d

    dx *= ex*0.4
    dy *= ey*0.5
    nvgBeginPath(vg)
    nvgEllipse(vg, lx+dx,ly+dy+ey*0.25*(1-blink), br,br*blink)
    nvgFillColor(vg, nvgRGBA(32,32,32,255))
    nvgFill(vg)

    dx = (mx - rx) / (ex * 10)
    dy = (my - ry) / (ey * 10)
    d = sqrt(dx*dx+dy*dy)
    if d > 1.0:
        dx /= d
        dy /= d

    dx *= ex*0.4
    dy *= ey*0.5
    nvgBeginPath(vg)
    nvgEllipse(vg, rx+dx,ry+dy+ey*0.25*(1-blink), br,br*blink)
    nvgFillColor(vg, nvgRGBA(32,32,32,255))
    nvgFill(vg)

    gloss = nvgRadialGradient(vg, lx-ex*0.25,ly-ey*0.5, ex*0.1,ex*0.75, nvgRGBA(255,255,255,128), nvgRGBA(255,255,255,0))
    nvgBeginPath(vg)
    nvgEllipse(vg, lx,ly, ex,ey)
    nvgFillPaint(vg, gloss)
    nvgFill(vg)

    gloss = nvgRadialGradient(vg, rx-ex*0.25,ry-ey*0.5, ex*0.1,ex*0.75, nvgRGBA(255,255,255,128), nvgRGBA(255,255,255,0))
    nvgBeginPath(vg)
    nvgEllipse(vg, rx,ry, ex,ey)
    nvgFillPaint(vg, gloss)
    nvgFill(vg)

def draw_lines(vg, x, y, w, h, t):
    pad = 5.0
    s = w/9.0 - pad*2
    pts = [0.0] * (4*2)
    joins = [NVG_MITER, NVG_ROUND, NVG_BEVEL]
    caps = [NVG_BUTT, NVG_ROUND, NVG_SQUARE]

    nvgSave(vg)
    pts[0] = -s*0.25 + cos(t*0.3) * s*0.5
    pts[1] = sin(t*0.3) * s*0.5
    pts[2] = -s*0.25
    pts[3] = 0
    pts[4] = s*0.25
    pts[5] = 0
    pts[6] = s*0.25 + cos(-t*0.3) * s*0.5
    pts[7] = sin(-t*0.3) * s*0.5

    for i in range(0, 3):
        for j in range(0, 3):
            fx = x + s*0.5 + (i*3+j)/9.0*w + pad
            fy = y - s*0.5 + pad

            nvgLineCap(vg, caps[i])
            nvgLineJoin(vg, joins[j])

            nvgStrokeWidth(vg, s*0.3)
            nvgStrokeColor(vg, nvgRGBA(0,0,0,160))
            nvgBeginPath(vg)
            nvgMoveTo(vg, fx+pts[0], fy+pts[1])
            nvgLineTo(vg, fx+pts[2], fy+pts[3])
            nvgLineTo(vg, fx+pts[4], fy+pts[5])
            nvgLineTo(vg, fx+pts[6], fy+pts[7])
            nvgStroke(vg)

            nvgLineCap(vg, NVG_BUTT)
            nvgLineJoin(vg, NVG_BEVEL)

            nvgStrokeWidth(vg, 1.0)
            nvgStrokeColor(vg, nvgRGBA(0,192,255,255))
            nvgBeginPath(vg)
            nvgMoveTo(vg, fx+pts[0], fy+pts[1])
            nvgLineTo(vg, fx+pts[2], fy+pts[3])
            nvgLineTo(vg, fx+pts[4], fy+pts[5])
            nvgLineTo(vg, fx+pts[6], fy+pts[7])
            nvgStroke(vg)

    nvgRestore(vg)


def draw_widths(vg, x, y, width):
    nvgSave(vg)
    c = nvgRGBA(255,255,0,255)
    nvgStrokeColor(vg, c)
    for i in range(0, 20):
        w = (i+0.5)*0.1
        nvgStrokeWidth(vg, w)
        nvgBeginPath(vg)
        nvgMoveTo(vg, x,y)
        nvgLineTo(vg, x+width,y+width*0.3)
        nvgStroke(vg)
        y += 10
    nvgRestore(vg)

def draw_caps(vg, x, y, width):
    caps = [NVG_BUTT, NVG_ROUND, NVG_SQUARE]
    lineWidth = 8.0

    nvgSave(vg)

    nvgBeginPath(vg)
    nvgRect(vg, x-lineWidth/2, y, width+lineWidth, 40)
    nvgFillColor(vg, nvgRGBA(255,255,255,32))
    nvgFill(vg)

    nvgBeginPath(vg)
    nvgRect(vg, x, y, width, 40)
    nvgFillColor(vg, nvgRGBA(255,255,255,32))
    nvgFill(vg)

    nvgStrokeWidth(vg, lineWidth)
    for i in range(0, 3):
        nvgLineCap(vg, caps[i])
        nvgStrokeColor(vg, nvgRGBA(0,0,0,255))
        nvgBeginPath(vg)
        nvgMoveTo(vg, x, y + i*10 + 5)
        nvgLineTo(vg, x+width, y + i*10 + 5)
        nvgStroke(vg)

    nvgRestore(vg)


def main():
    GLFW.load_glfw_library('libglfw.dylib')
    glfwInit()

    win = glfwCreateWindow(640, 480, b"Python NanoVG/GLFW", None, None)
    glfwMakeContextCurrent(win)

    NanoVG.load_nanovg_library('libnanovg_gl2.dylib', render_backend = 'gl2', output_error = True)
    nvgSetupGL2()
    vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG)
    if vg == None:
        print("Could not init nanovg.")
        exit()

    glfwSetKeyCallback(win, key_callback)

    fb_width = ctypes.c_int()
    fb_height = ctypes.c_int()
    mx = ctypes.c_double()
    my = ctypes.c_double()

    try:
        while glfwWindowShouldClose(win) == 0:
            t = glfwGetTime()
            glfwGetCursorPos(win, mx, my)
            glfwGetFramebufferSize(win, fb_width, fb_height)
            ratio = fb_width.value / fb_height.value

            OpenGL.GL.glViewport(0, 0, fb_width.value, fb_height.value)
            OpenGL.GL.glClearColor(0.3, 0.3, 0.32, 1.0)
            OpenGL.GL.glClear(OpenGL.GL.GL_COLOR_BUFFER_BIT)

            nvgBeginFrame(vg, fb_width.value, fb_height.value, ratio)
            draw_eyes(vg, fb_width.value - 250, 50, 150, 100, mx.value, my.value, t)
            draw_lines(vg, 120, fb_height.value-50, 600, 50, t)
            draw_widths(vg, 10, 50, 30)
            draw_caps(vg, 10, 300, 30)
            nvgEndFrame(vg)

            glfwSwapBuffers(win)
            glfwPollEvents()
    finally:
        nvgDeleteGL2(vg)
        glfwDestroyWindow(win)
        glfwTerminate()


if __name__ == '__main__':
    main()

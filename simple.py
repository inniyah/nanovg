# Ref.: https://github.com/vaiorabbit/ruby-opengl/blob/master/sample/simple.rb
from ctypes import *
from OpenGL.GL import *
import GLFW
from GLFW import *

def key_callback_fn(window_handle, key, scancode, action, mods):
    if key == GLFW_KEY_ESCAPE and action == GLFW_PRESS:
        glfwSetWindowShouldClose(window_handle, 1)
key_callback = GLFWkeyfun(key_callback_fn)

def main():
    GLFW.load_glfw_library('libglfw.dylib')
    glfwInit()

    major = c_int()
    minor = c_int()
    rev = c_int()
    glfwGetVersion(byref(major), byref(minor), byref(rev))
    print(major.value, minor.value, rev.value)

    verstr = glfwGetVersionString()
    print(verstr)

    win = glfwCreateWindow(640, 480, b"Python GLFW", None, None)
    glfwMakeContextCurrent(win)

    primary_monitor = glfwGetPrimaryMonitor()
    monitor_name = glfwGetMonitorName(primary_monitor)
    print(monitor_name)

    vidmode_ptr = glfwGetVideoMode(primary_monitor)
    vidmode = cast(vidmode_ptr, POINTER(GLFWvidmode)).contents
    print(vidmode.width, vidmode.height, vidmode.refreshRate)

    glfwSetKeyCallback(win, key_callback)

    fb_width = c_int()
    fb_height = c_int()

    try:
        while glfwWindowShouldClose(win) == 0:
            glfwGetFramebufferSize(win, fb_width, fb_height)
            ratio = fb_width.value / fb_height.value

            glViewport(0, 0, fb_width.value, fb_height.value)
            glClear(GL_COLOR_BUFFER_BIT)
            glMatrixMode(GL_PROJECTION)
            glLoadIdentity()
            glOrtho(-ratio, ratio, -1.0, 1.0, 1.0, -1.0)
            glMatrixMode(GL_MODELVIEW)

            glLoadIdentity()
            glRotatef(glfwGetTime() * 50.0, 0.0, 0.0, 1.0)

            glBegin(GL_TRIANGLES)
            glColor3f(1.0, 0.0, 0.0)
            glVertex3f(-0.6, -0.4, 0.0)
            glColor3f(0.0, 1.0, 0.0)
            glVertex3f(0.6, -0.4, 0.0)
            glColor3f(0.0, 0.0, 1.0)
            glVertex3f(0.0, 0.6, 0.0)
            glEnd()

            glfwSwapBuffers(win)
            glfwPollEvents()
    finally:
        glfwDestroyWindow(win)
        glfwTerminate()


if __name__ == '__main__':
    main()

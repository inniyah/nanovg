import sys
import ctypes

from OpenGL.GLUT import *
from OpenGL.GL import *

from NanoVG import *
from demo_data import DemoData
from perf import PerfGraph

class App:
    def __init__(self):
        self.width = 1000.0
        self.height = 600.0
        self.mx = 0.0
        self.my = 0.0
        self.crnt_t = 0.0
        self.prev_t = 0.0

        self.vg = None
        self.data = None
        self.fps = None

app = App()

def display():
    app.crnt_t = glutGet(GLUT_ELAPSED_TIME) / 1000.0
    dt = app.crnt_t - app.prev_t
    app.prev_t = app.crnt_t
    app.fps.update(dt)

    ratio = float(app.width) / float(app.height)
    glClearColor(0.3, 0.3, 0.32, 1.0)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    nvgBeginFrame(app.vg, app.width, app.height, ratio)
    app.data.render(app.vg, app.mx, app.my, app.width, app.height, app.crnt_t, False)
    app.fps.render(app.vg, 5, 5)
    nvgEndFrame(app.vg)
    glutSwapBuffers()

def reshape(width, height):
    app.width = width
    app.height = height
    glViewport(0, 0, width, height)

def keyboard(key, x, y):
    c = key.decode('utf-8')
    if c == chr(27): # ESC
        exit()

def motion(x, y):
    app.mx = x
    app.my = y

def timer(value):
    glutTimerFunc(0, timer, value)
    glutPostRedisplay()

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL)
    glutInitWindowSize(1000, 600)
    glutCreateWindow(b"Python NanoVG/GLFW")

    NanoVG.load_nanovg_library('libnanovg_gl2.dylib', render_backend = 'gl2', output_error = True)
    nvgSetupGL2()
    app.vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG)
    if app.vg == None:
        print("Could not init nanovg.")
        exit()

    app.data = DemoData()
    if app.data.load(app.vg) == -1:
        exit()
    app.fps = PerfGraph(PerfGraph.GRAPH_RENDER_FPS, "Frame Time")

    app.fps.update(1.0 / 1000.0)
    app.prev_t = glutGet(GLUT_ELAPSED_TIME) / 1000.0

    glutDisplayFunc(display)
    glutReshapeFunc(reshape)
    glutKeyboardFunc(keyboard)
    glutPassiveMotionFunc(motion)
    glutTimerFunc(0, timer, 0)

    glutMainLoop()

if __name__ == '__main__':
    main()

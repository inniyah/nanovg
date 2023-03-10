#!/usr/bin/env python3

import os, sys
MY_PATH = os.path.normpath(os.path.abspath(os.path.dirname(__file__)))

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

if 'LD_LIBRARY_PATH' not in os.environ:
    os.environ['LD_LIBRARY_PATH'] = MY_PATH
    try:
        os.execv(sys.argv[0], sys.argv)
    except Exception as e:
        print(f"Failed to re-exec - {type(e).__name__}: {e}")
        sys.exit(1)

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

import argparse
import faulthandler
import logging
import os
import sys

from datetime import datetime
from pprint import pprint

MY_PATH = os.path.normpath(os.path.abspath(os.path.dirname(__file__)))
sys.path.append(os.path.abspath(os.path.join(MY_PATH, 'python')))

logging.basicConfig(level=logging.INFO)

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

import sys
import ctypes

from OpenGL import GL, GLU
import sdl2
import nvg

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

def draw1(vg):
    vg.BeginPath()
    vg.Rect(300, 100, 120, 30)
    vg.FillColor(nvg.RGBA(255, 192, 0, 255))
    vg.Fill()
    vg.ClosePath()

def draw2(vg): # Rectangle
    vg.BeginPath()
    vg.Rect(100,100,300,150)
    vg.FillColor(nvg.RGBAf(1, 0, 0, 0.5))
    vg.Fill()
    vg.ClosePath()

def draw3(vg): # Rounded rectangle
    vg.BeginPath()
    vg.RoundedRect(100, 100, 300, 150, 10)
    vg.FillColor(nvg.RGBAf(1, 0, 0, 0.5))
    vg.Fill()
    vg.ClosePath()

def draw4(vg): # Triangles
    vg.BeginPath()
    vg.MoveTo(100, 100) # Top left corner
    vg.LineTo(400, 100) # Top right corner: 100 (x) + 300 (w), y remains
    vg.LineTo(100, 250) # Bottom left corner: x remains, 100 (y) + 150 (h)
    vg.LineTo(100, 100) # Back to top left
    vg.FillColor(nvg.RGBAf(1, 0, 1, 0.5))
    vg.Fill()
    vg.ClosePath()

def draw5(vg): # Triangle outline
    vg.BeginPath()
    vg.MoveTo(100, 100)
    vg.LineTo(400, 100)
    vg.LineTo(100, 250)
    vg.LineTo(100, 100)
    vg.StrokeColor(nvg.RGBAf(1, 0.5, 0, 0.5))
    vg.StrokeWidth(5.5)
    vg.Stroke()
    vg.ClosePath()

def draw6(vg): # Concave filling
    vg.BeginPath()
    vg.MoveTo(100, 100)
    vg.LineTo(150, 150)
    vg.LineTo(200, 100)
    vg.LineTo(200, 200)
    vg.LineTo(100, 200)
    vg.LineTo(100, 100)
    vg.StrokeColor(nvg.RGBAf(1, 0.5, 0, 0.5))
    vg.StrokeWidth(5.5)
    vg.Stroke()
    vg.FillColor(nvg.RGBAf(1, 0, 0, 0.5))
    vg.Fill()
    vg.ClosePath()

def draw7(vg): # Gradients and paints
    vg.BeginPath()
    vg.Rect(100, 100, 300, 500)
    vg.FillPaint(vg.BoxGradient(100, 200, 300, 300, 150, 100, nvg.RGBAf(1, 0, 0, 1), nvg.RGBAf(1, 1, 0, 1)))
    vg.Fill()
    vg.ClosePath()
    vg.BeginPath()
    vg.Rect(500, 100, 300, 500)
    vg.FillPaint(vg.LinearGradient(500, 100, 500, 600, nvg.RGBAf(1, 0, 0, 1), nvg.RGBAf(1, 1, 0, 1)))
    vg.Fill()
    vg.ClosePath()
    vg.BeginPath()
    vg.Rect(900, 100, 300, 500)
    vg.FillPaint(vg.RadialGradient(1050, 350, 100, 200, nvg.RGBAf(1, 0, 0, 1), nvg.RGBAf(1, 1, 0, 1)))
    vg.Fill()

def draw8(vg): # Bezier Quad I
    vg.BeginPath()
    vg.MoveTo(100, 100) # Start point: (100, 100)
    vg.QuadTo(200, 400, 300, 100) # Control point: (200, 400); End point: (300, 100)
    vg.StrokeColor(nvg.RGBAf(1, 0.5, 0, 0.5))
    vg.StrokeWidth(5.5)
    vg.Stroke()
    vg.ClosePath()

def draw9(vg): # Bezier Quad II
    vg.BeginPath()
    vg.MoveTo(100, 100) # Start point: (100, 100)
    vg.QuadTo(150, 400, 300, 300) # Control point: (150, 400); End point: (300, 300)
    vg.StrokeColor(nvg.RGBAf(1, 0.5, 0, 0.5))
    vg.StrokeWidth(5.5)
    vg.Stroke()
    vg.ClosePath()

def draw10(vg): # Bezier Quad III
    vg.BeginPath()
    vg.MoveTo(100, 100)
    vg.QuadTo(150, 400, 300, 300)
    vg.QuadTo(450, 200, 300, 400)
    vg.QuadTo(150, 600, 600, 600)
    vg.QuadTo(800, 600, 600, 300)
    vg.StrokeColor(nvg.RGBAf(1, 0.5, 0, 0.5))
    vg.StrokeWidth(5.5)
    vg.Stroke()
    vg.ClosePath()

def draw11(vg): # Bezier Cubic I
    vg.BeginPath()
    vg.MoveTo(100, 100)
    vg.BezierTo(150, 400, 450, 200, 300, 400)
    vg.StrokeColor(nvg.RGBAf(0, 0.5, 1, 0.5))
    vg.StrokeWidth(5.5)
    vg.Stroke()
    vg.ClosePath()

def draw12(vg): # Bézier Cubic II
    vg.BeginPath()
    vg.MoveTo(100, 100)
    vg.BezierTo(150, 400, 450, 200, 300, 400)
    vg.BezierTo(150, 600, 800, 600, 600, 300)
    vg.StrokeColor(nvg.RGBAf(0, 0.5, 1, 0.5))
    vg.StrokeWidth(5.5)
    vg.Stroke()
    vg.ClosePath()

def runTest():
    if sdl2.SDL_Init(sdl2.SDL_INIT_VIDEO) != 0:
        logging.error(sdl2.SDL_GetError())
        return False

    #~ context = sdl2.SDL_GLContext()
    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_STENCIL_SIZE, 8);

    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_MAJOR_VERSION, 2)
    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_MINOR_VERSION, 0)
    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_PROFILE_MASK, sdl2.SDL_GL_CONTEXT_PROFILE_CORE)

    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_DOUBLEBUFFER, 1)

    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_MULTISAMPLEBUFFERS, 1)
    sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_MULTISAMPLESAMPLES, 8)
    window = sdl2.SDL_CreateWindow(b'SDL2/OpenGL/NanoVG',
                                   sdl2.SDL_WINDOWPOS_UNDEFINED,
                                   sdl2.SDL_WINDOWPOS_UNDEFINED,
                                   1024,
                                   800,
                                   sdl2.SDL_WINDOW_OPENGL | sdl2.SDL_WINDOW_RESIZABLE | sdl2.SDL_WINDOW_SHOWN | sdl2.SDL_WINDOW_ALLOW_HIGHDPI)

    if not window:
        logging.debug(sdl2.SDL_GetError())
        logging.debug('fallback')
        sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_MULTISAMPLEBUFFERS, 0)
        sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_MULTISAMPLESAMPLES, 0)
        window = sdl2.SDL_CreateWindow(b'SDL2/OpenGL/NanoVG',
                                       sdl2.SDL_WINDOWPOS_UNDEFINED,
                                       sdl2.SDL_WINDOWPOS_UNDEFINED,
                                       1024,
                                       800,
                                       sdl2.SDL_WINDOW_OPENGL | sdl2.SDL_WINDOW_RESIZABLE | sdl2.SDL_WINDOW_SHOWN | sdl2.SDL_WINDOW_ALLOW_HIGHDPI)

    if not window:
        logging.error(sdl2.SDL_GetError())
        return False

    context = sdl2.SDL_GL_CreateContext(window)
    sdl2.SDL_GL_MakeCurrent(window, context)

    vg = nvg.CreateGL3(nvg.NVG_ANTIALIAS | nvg.NVG_STENCIL_STROKES | nvg.NVG_DEBUG)
    if not vg.isValid():
        logging.error('Error in CreateGL3')
        return False

    w = ctypes.c_int()
    h = ctypes.c_int()
    sdl2.SDL_GetWindowSize(window, w, h)
    # Window Width and Height
    winWidth = w.value
    winHeight = h.value
    # Frame Buffer Width and Height
    fbWidth = winWidth
    fbHeight = winHeight
    # Pixel Ratio
    pxRatio = float(winWidth) / float(winWidth)
    logging.info(f"W = {winWidth},  H = {winHeight}, Ratio = {pxRatio}")

    event = sdl2.SDL_Event()
    running = True
    while running:
        while sdl2.SDL_PollEvent(ctypes.byref(event)) != 0:
            if event.type == sdl2.SDL_QUIT:
                running = False

            elif event.type == sdl2.SDL_MOUSEMOTION:
                pass

            elif event.type == sdl2.SDL_MOUSEBUTTONDOWN:
                b = event.button.button
                if b == sdl2.SDL_BUTTON_LEFT:
                    pass
                elif b == sdl2.SDL_BUTTON_RIGHT:
                    pass
                elif b == sdl2.SDL_BUTTON_MIDDLE:
                    pass

            elif event.type == sdl2.SDL_KEYDOWN:
                k = event.key.keysym.sym
                if k == sdl2.SDLK_ESCAPE:
                    running = False

        GL.glClearColor(0.0, 0.0, 0.0, 0.0)
        GL.glClear(GL.GL_COLOR_BUFFER_BIT)

        vg.BeginFrame(winWidth, winHeight, pxRatio)
        draw12(vg)
        vg.EndFrame()

        sdl2.SDL_GL_SwapWindow(window)

    sdl2.SDL_GL_DeleteContext(context)
    sdl2.SDL_DestroyWindow(window)
    sdl2.SDL_Quit()
    return True

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Dump logging output with colors

class ColorStderr(logging.StreamHandler):
    def __init__(self, fmt=None):
        class AddColor(logging.Formatter):
            def __init__(self):
                super().__init__(fmt)
            def format(self, record: logging.LogRecord):
                msg = super().format(record)
                # Green/Cyan/Yellow/Red/Redder based on log level:
                color = '\033[1;' + ('32m', '36m', '33m', '31m', '41m')[min(4,int(4 * record.levelno / logging.FATAL))]
                return color + record.levelname + '\033[1;0m: ' + msg
        super().__init__(sys.stderr)
        self.setFormatter(AddColor())

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

LOG_CONSOLE_FORMAT = "[%(pathname)s:%(lineno)d] [%(asctime)s]: '%(message)s' [PID=%(process)d]"
LOG_FILE_FORMAT    = "[%(levelname)s] [%(pathname)s:%(lineno)d] [%(asctime)s] [%(name)s]: '%(message)s' [PID=%(process)d]"
LOG_SIMPLE_FORMAT  = "[%(levelname)s] %(message)s"

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-q', '--quiet', help='set logging to ERROR',
                        action='store_const', dest='loglevel',
                        const=logging.ERROR, default=logging.INFO)
    parser.add_argument('-d', '--debug', help='set logging to DEBUG',
                        action='store_const', dest='loglevel',
                        const=logging.DEBUG, default=logging.INFO)
    parser.add_argument('--log', action=argparse.BooleanOptionalAction)
    parser.add_argument('test', nargs=argparse.REMAINDER)
    args = parser.parse_args()

    logger = logging.getLogger()
    logger.setLevel(logging.DEBUG)
    logger.handlers = []

    log_console_handler = ColorStderr(LOG_CONSOLE_FORMAT)
    log_console_handler.setLevel(args.loglevel)
    logger.addHandler(log_console_handler)

    if args.log:
        now = datetime.now()
        logs_dir = os.path.abspath(os.path.join(MY_PATH, 'logs', f"{now.strftime('%Y%m%d')}"))
        os.makedirs(logs_dir, exist_ok=True)
        log_filename = f"{now.strftime('%Y%m%d')}_{now.strftime('%H%M%S')}.txt"
        log_file_handler = logging.FileHandler(os.path.join(logs_dir, log_filename))
        log_formatter = logging.Formatter(LOG_FILE_FORMAT)
        log_file_handler.setFormatter(log_formatter)
        log_file_handler.setLevel(logging.DEBUG)
        logger.addHandler(log_file_handler)
        logging.info(f"Storing log into '{logs_dir}/{log_filename}'")

    if not args.test:
        tests = [ 'test' ]
    else:
        tests = args.test

    ret = True

    for test in tests:
        logging.info(f"Running test: {test}")
        if test == 'test':
            if not runTest():
                ret = False
        else:
            logging.warning(f"Unknown test: {test}")

    return ret

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

if __name__ == "__main__":
    faulthandler.enable()
    sys.exit(main())

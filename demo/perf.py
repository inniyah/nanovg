from functools import reduce
import ctypes
import math
from NanoVG import *

class PerfGraph:
    GRAPH_RENDER_FPS     = 0
    GRAPH_RENDER_MS      = 1
    GRAPH_RENDER_PERCENT = 2

    GRAPH_HISTORY_COUNT = 100

    def __init__(self, style, name):
        self.style = style
        self.name = name
        self.values = [0.0] * PerfGraph.GRAPH_HISTORY_COUNT
        self.head = 0

    def update(self, frameTime):
        self.head = (self.head + 1) % PerfGraph.GRAPH_HISTORY_COUNT
        self.values[self.head] = frameTime

    def average(self):
        return reduce(lambda x, y: x + y, self.values) / PerfGraph.GRAPH_HISTORY_COUNT

    def render(self, vg, x, y):
        avg = self.average()

        w = 200
        h = 35

        nvgBeginPath(vg)
        nvgRect(vg, x,y, w,h)
        nvgFillColor(vg, nvgRGBA(0,0,0,128))
        nvgFill(vg)

        nvgBeginPath(vg)
        nvgMoveTo(vg, x, y+h)
        if self.style == PerfGraph.GRAPH_RENDER_FPS:
            for i in range(0, PerfGraph.GRAPH_HISTORY_COUNT):
                v = 1.0 / (0.00001 + self.values[(self.head+i) % PerfGraph.GRAPH_HISTORY_COUNT])
                v = 80.0 if v > 80.0 else v
                vx = x + (float(i)/(PerfGraph.GRAPH_HISTORY_COUNT-1)) * w
                vy = y + h - ((v / 80.0) * h)
                nvgLineTo(vg, vx, vy)
        elif self.style == PerfGraph.GRAPH_RENDER_PERCENT:
            for i in range(0, PerfGraph.GRAPH_HISTORY_COUNT):
                v = self.values[(self.head+i) % PerfGraph.GRAPH_HISTORY_COUNT] * 1.0
                v = 100.0 if v > 100.0 else v
                vx = x + (i.to_f/(PerfGraph.GRAPH_HISTORY_COUNT-1)) * w
                vy = y + h - ((v / 100.0) * h)
                nvgLineTo(vg, vx, vy)
        else:
            for i in range(0, PerfGraph.GRAPH_HISTORY_COUNT):
                v = self.values[(self.head+i) % PerfGraph.GRAPH_HISTORY_COUNT] * 1000.0
                v = 20.0 if v > 20.0 else v
                vx = x + (i.to_f/(PerfGraph.GRAPH_HISTORY_COUNT-1)) * w
                vy = y + h - ((v / 20.0) * h)
                nvgLineTo(vg, vx, vy)

        nvgLineTo(vg, x+w, y+h)
        nvgFillColor(vg, nvgRGBA(255,192,0,128))
        nvgFill(vg)

        nvgFontFace(vg, b"sans")

        if self.name:
            nvgFontSize(vg, 14.0)
            nvgTextAlign(vg, NVG_ALIGN_LEFT|NVG_ALIGN_TOP)
            nvgFillColor(vg, nvgRGBA(240,240,240,192))
            nvgText(vg, x+3,y+1, self.name.encode('utf-8'), None)

        if self.style == PerfGraph.GRAPH_RENDER_FPS:
            nvgFontSize(vg, 18.0)
            nvgTextAlign(vg, NVG_ALIGN_RIGHT|NVG_ALIGN_TOP)
            nvgFillColor(vg, nvgRGBA(240,240,240,255))
            s = "%.2f FPS" % (1.0 / avg)
            nvgText(vg, x+w-3,y+1, s.encode('utf-8'), None)

            nvgFontSize(vg, 15.0)
            nvgTextAlign(vg, NVG_ALIGN_RIGHT|NVG_ALIGN_BOTTOM)
            nvgFillColor(vg, nvgRGBA(240,240,240,160))
            s = "%.2f ms" % (avg * 1000.0)
            nvgText(vg, x+w-3,y+h-1, s.encode('utf-8'), None)
        elif self.style == PerfGraph.GRAPH_RENDER_PERCENT:
            nvgFontSize(vg, 18.0)
            nvgTextAlign(vg,NVG_ALIGN_RIGHT|NVG_ALIGN_TOP)
            nvgFillColor(vg, nvgRGBA(240,240,240,255))
            s = "%.1f %%" % (avg * 1.0)
            nvgText(vg, x+w-3,y+1, s.encode('utf-8'), None)
        else:
            nvgFontSize(vg, 18.0)
            nvgTextAlign(vg,NVG_ALIGN_RIGHT|NVG_ALIGN_TOP)
            nvgFillColor(vg, nvgRGBA(240,240,240,255))
            s = "%.2f ms" & (avg * 1000.0)
            nvgText(vg, x+w-3,y+1, s.encode('utf-8'), None)

# cython: profile=False
# cython: embedsignature = True
# cython: language_level = 3
# distutils: language = c++

from libc.stdint cimport uint64_t, uint32_t, uint16_t, uint8_t
from libc.stdlib cimport calloc, malloc, free
from libc.string cimport memset, strcmp
from libc.stdio cimport printf

from libcpp cimport bool
from libcpp.memory cimport unique_ptr, shared_ptr, make_shared, allocator
from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp.utility cimport pair

from cpython cimport array
from cpython.ref cimport PyObject
from cpython.mem cimport PyMem_Malloc, PyMem_Realloc, PyMem_Free
from cpython.bytes cimport PyBytes_FromStringAndSize

from cython.operator cimport dereference as deref

from cpython.pycapsule cimport PyCapsule_New, PyCapsule_IsValid, PyCapsule_GetPointer, PyCapsule_GetName

from enum import IntEnum

import logging

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

cimport SDL2.SDL2 as c_SDL2
cimport SDL2.SDL2_image as c_SDL2_image
cimport nanovg.nanovg as c_nanovg
cimport nanovg.nanovg_gl as c_nanovg_gl

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

NVG_ANTIALIAS = c_nanovg_gl.NVG_ANTIALIAS
NVG_STENCIL_STROKES = c_nanovg_gl.NVG_STENCIL_STROKES
NVG_DEBUG = c_nanovg_gl.NVG_DEBUG

cdef class _Color:
    cdef c_nanovg.NVGcolor _color

    def getRGBA(self):
        return self._color.rgba

    def getR(self) -> float:
        return self._color.r

    def getG(self) -> float:
        return self._color.g

    def getB(self) -> float:
        return self._color.b

    def getA(self) -> float:
        return self._color.a

def RGB(r : uint8_t, g : uint8_t, b : uint8_t):
    c = _Color()
    c._color = c_nanovg.nvgRGB(r, g, b)
    return c

def RGBf(r : float, g : float, b : float):
    c = _Color()
    c._color = c_nanovg.nvgRGBf(r, g, b)
    return c

def RGBA(r : uint8_t, g : uint8_t, b : uint8_t, a : uint8_t):
    c = _Color()
    c._color = c_nanovg.nvgRGBA(r, g, b, a)
    return c

def RGBAf(r : float, g : float, b : float, a : float):
    c = _Color()
    c._color = c_nanovg.nvgRGBAf(r, g, b, a)
    return c

def LerpRGBA(c0 : _Color, c1 : _Color, u : float):
    c = _Color()
    c._color = c_nanovg.nvgLerpRGBA(c0._color, c1._color, u)
    return c

def TransRGBA(c0 : _Color, a : uint8_t):
    c = _Color()
    c._color = c_nanovg.nvgTransRGBA(c0._color, a)
    return c

def TransRGBAf(c0 : _Color, a : float):
    c = _Color()
    c._color = c_nanovg.nvgTransRGBAf(c0._color, a)
    return c

def HSL(h : float, s : float, l : float):
    c = _Color()
    c._color = c_nanovg.nvgHSL(h, s, l)
    return c

def HSLA(h : float, s : float, l : float, a : uint8_t):
    c = _Color()
    c._color = c_nanovg.nvgHSLA(h, s, l, a)
    return c


cdef class _Paint:
    cdef c_nanovg.NVGpaint _paint

    def getXform(self) -> float[6]:
        return self._paint.xform

    def getExtent(self) -> float[2]:
        return self._paint.extent

    def getRadius(self) -> float:
        return self._paint.radius

    def getFeather(self) -> float:
        return self._paint.feather

    def getInnerColor(self) -> _Color:
        c = _Color()
        c._color = self._paint.innerColor
        return c

    def getOuterColor(self) -> _Color:
        c = _Color()
        c._color = self._paint.outerColor
        return c

    def getImage(self) -> int:
        return self._paint.image

cdef class _NVGcontext:
    cdef c_nanovg.NVGcontext * _vg

    def __cinit__(self):
        self._vg = NULL

    def isValid(self):
        return False if self._vg == NULL else True

    @staticmethod
    cdef create(c_nanovg.NVGcontext * vg):
        cdef _NVGcontext e = _NVGcontext()
        e._vg = vg
        return e

    def BeginFrame(self, windowWidth : float, windowHeight : float, devicePixelRatio : float):
        c_nanovg.nvgBeginFrame(self._vg, windowWidth, windowHeight, devicePixelRatio)
    def CancelFrame(self):
        c_nanovg.nvgCancelFrame(self._vg)
    def EndFrame(self):
        c_nanovg.nvgEndFrame(self._vg)
    def GlobalCompositeOperation(self, op : int):
        c_nanovg.nvgGlobalCompositeOperation(self._vg, op)
    def GlobalCompositeBlendFunc(self, sfactor : int, dfactor : int):
        c_nanovg.nvgGlobalCompositeBlendFunc(self._vg, sfactor, dfactor)
    def GlobalCompositeBlendFuncSeparate(self, srcRGB : int, dstRGB : int, srcAlpha : int, dstAlpha : int):
        c_nanovg.nvgGlobalCompositeBlendFuncSeparate(self._vg, srcRGB, dstRGB, srcAlpha, dstAlpha)
    def Save(self):
        c_nanovg.nvgSave(self._vg)
    def Restore(self):
        c_nanovg.nvgRestore(self._vg)
    def Reset(self):
        c_nanovg.nvgReset(self._vg)
    def ShapeAntiAlias(self, enabled : int):
        c_nanovg.nvgShapeAntiAlias(self._vg, enabled)
    def StrokeColor(self, color : _Color):
        c_nanovg.nvgStrokeColor(self._vg, color._color)
    def StrokePaint(self, paint : _Paint):
        c_nanovg.nvgStrokePaint(self._vg, paint._paint)
    def FillColor(self, color : _Color):
        c_nanovg.nvgFillColor(self._vg, color._color)
    def FillPaint(self, paint : _Paint):
        c_nanovg.nvgFillPaint(self._vg, paint._paint)
    def MiterLimit(self, limit : float):
        c_nanovg.nvgMiterLimit(self._vg, limit)
    def StrokeWidth(self, size : float):
        c_nanovg.nvgStrokeWidth(self._vg, size)
    def LineCap(self, cap : int):
        c_nanovg.nvgLineCap(self._vg, cap)
    def LineJoin(self, join : int):
        c_nanovg.nvgLineJoin(self._vg, join)
    def GlobalAlpha(self, alpha : float):
        c_nanovg.nvgGlobalAlpha(self._vg, alpha)
    def ResetTransform(self):
        c_nanovg.nvgResetTransform(self._vg)
    def Transform(self, a : float, b : float, c : float, d : float, e : float, f : float):
        c_nanovg.nvgTransform(self._vg, a, b, c, d, e, f)
    def Translate(self, x : float, y : float):
        c_nanovg.nvgTranslate(self._vg, x, y)
    def Rotate(self, angle : float):
        c_nanovg.nvgRotate(self._vg, angle)
    def SkewX(self, angle : float):
        c_nanovg.nvgSkewX(self._vg, angle)
    def SkewY(self, angle : float):
        c_nanovg.nvgSkewY(self._vg, angle)
    def Scale(self, x : float, y : float):
        c_nanovg.nvgScale(self._vg, x, y)
    #~ def CurrentTransform(self, float* xform):
    #~     c_nanovg.nvgCurrentTransform(self._vg, xform)
    def CreateImage(self, filename : str, imageFlags : int) -> int:
        return c_nanovg.nvgCreateImage(self._vg, filename.encode('utf8'), imageFlags)
    #~ def CreateImageMem(self, imageFlags : int, unsigned char* data, ndata : int) -> int:
    #~     return c_nanovg.nvgCreateImageMem(self._vg, imageFlags, data, ndata)
    #~ def CreateImageRGBA(self, w : int, h : int, imageFlags : int, unsigned char* data) -> int:
    #~     return c_nanovg.nvgCreateImageRGBA(self._vg, w, h, imageFlags, data)
    #~ def CreateImageAlpha(self, w : int, h : int, imageFlags : int, unsigned char* data) -> int:
    #~     return c_nanovg.nvgCreateImageAlpha(self._vg, w, h, imageFlags, data)
    #~ def UpdateImage(self, image : int, unsigned char* data):
    #~     c_nanovg.nvgUpdateImage(self._vg, image, data)
    def ImageSize(self, image : int):
        cdef int w = 0, h = 0
        c_nanovg.nvgImageSize(self._vg, image, &w, &h)
        return w, h
    def DeleteImage(self, image : int):
        c_nanovg.nvgDeleteImage(self._vg, image)
    def LinearGradient(self, sx : float, sy : float, ex : float, ey : float, icol : _Color, ocol : _Color) -> _Paint:
        p = _Paint()
        p._paint = c_nanovg.nvgLinearGradient(self._vg, sx, sy, ex, ey, icol._color, ocol._color)
        return p
    def BoxGradient(self, x : float, y : float, w : float, h : float, r : float, f : float, icol : _Color, ocol : _Color) -> _Paint:
        p = _Paint()
        p._paint = c_nanovg.nvgBoxGradient(self._vg, x, y, w, h, r, f, icol._color, ocol._color)
        return p
    def RadialGradient(self, cx : float, cy : float, inr : float, outr : float, icol : _Color, ocol : _Color) -> _Paint:
        p = _Paint()
        p._paint = c_nanovg.nvgRadialGradient(self._vg, cx, cy, inr, outr, icol._color, ocol._color)
        return p
    def ImagePattern(self, ox : float, oy : float, ex : float, ey : float, angle : float, image : int, alpha : float) -> _Paint:
        p = _Paint()
        p._paint = c_nanovg.nvgImagePattern(self._vg, ox, oy, ex, ey, angle, image, alpha)
        return p
    def Scissor(self, x : float, y : float, w : float, h : float):
        c_nanovg.nvgScissor(self._vg, x, y, w, h)
    def IntersectScissor(self, x : float, y : float, w : float, h : float):
        c_nanovg.nvgIntersectScissor(self._vg, x, y, w, h)
    def ResetScissor(self):
        c_nanovg.nvgResetScissor(self._vg)
    def BeginPath(self):
        c_nanovg.nvgBeginPath(self._vg)
    def MoveTo(self, x : float, y : float):
        c_nanovg.nvgMoveTo(self._vg, x, y)
    def LineTo(self, x : float, y : float):
        c_nanovg.nvgLineTo(self._vg, x, y)
    def BezierTo(self, c1x : float, c1y : float, c2x : float, c2y : float, x : float, y : float):
        c_nanovg.nvgBezierTo(self._vg, c1x, c1y, c2x, c2y, x, y)
    def QuadTo(self, cx : float, cy : float, x : float, y : float):
        c_nanovg.nvgQuadTo(self._vg, cx, cy, x, y)
    def ArcTo(self, x1 : float, y1 : float, x2 : float, y2 : float, radius : float):
        c_nanovg.nvgArcTo(self._vg, x1, y1, x2, y2, radius)
    def ClosePath(self):
        c_nanovg.nvgClosePath(self._vg)
    def PathWinding(self, dir : int):
        c_nanovg.nvgPathWinding(self._vg, dir)
    def Arc(self, cx : float, cy : float, r : float, a0 : float, a1 : float, dir : int):
        c_nanovg.nvgArc(self._vg, cx, cy, r, a0, a1, dir)
    def Barc(self, cx : float, cy : float, r : float, a0 : float, a1 : float, dir : int, join : int):
        c_nanovg.nvgBarc(self._vg, cx, cy, r, a0, a1, dir, join)
    def Rect(self, x : float, y : float, w : float, h : float):
        c_nanovg.nvgRect(self._vg, x, y, w, h)
    def RoundedRect(self, x : float, y : float, w : float, h : float, r : float):
        c_nanovg.nvgRoundedRect(self._vg, x, y, w, h, r)
    def RoundedRectVarying(self, x : float, y : float, w : float, h : float, radTopLeft : float, radTopRight : float, radBottomRight : float, radBottomLeft : float):
        c_nanovg.nvgRoundedRectVarying(self._vg, x, y, w, h, radTopLeft, radTopRight, radBottomRight, radBottomLeft)
    def Ellipse(self, cx : float, cy : float, rx : float, ry : float):
        c_nanovg.nvgEllipse(self._vg, cx, cy, rx, ry)
    def Circle(self, cx : float, cy : float, r : float):
        c_nanovg.nvgCircle(self._vg, cx, cy, r)
    def Fill(self):
        c_nanovg.nvgFill(self._vg)
    def Stroke(self):
        c_nanovg.nvgStroke(self._vg)
    def CreateFont(self, name : str, filename : str) -> int:
        return c_nanovg.nvgCreateFont(self._vg, name.encode('utf8'), filename.encode('utf8'))
    def CreateFontAtIndex(self, name : str, filename : str, fontIndex : int) -> int:
        return c_nanovg.nvgCreateFontAtIndex(self._vg, name.encode('utf8'), filename.encode('utf8'), fontIndex)
    #~ def CreateFontMem(self, name : str, unsigned char* data, ndata : int, freeData : int) -> int:
    #~     return c_nanovg.nvgCreateFontMem(self._vg, name.encode('utf8'), unsigned char* data, ndata : int, freeData)
    #~ def CreateFontMemAtIndex(self, name : str, unsigned char* data, ndata : int, freeData : int, fontIndex : int) -> int:
    #~     return c_nanovg.nvgCreateFontMemAtIndex(self._vg, name.encode('utf8'), unsigned char* data, ndata : int, freeData : int, fontIndex)
    def FindFont(self, name : str) -> int:
        return c_nanovg.nvgFindFont(self._vg, name.encode('utf8'))
    def AddFallbackFontId(self, baseFont : int, fallbackFont : int) -> int:
        return c_nanovg.nvgAddFallbackFontId(self._vg, baseFont, fallbackFont)
    #~ def AddFallbackFont(self, char* baseFont, char* fallbackFont) -> int:
    #~     return c_nanovg.nvgAddFallbackFont(self._vg, char* baseFont, char* fallbackFont)
    def ResetFallbackFontsId(self, baseFont : int):
        c_nanovg.nvgResetFallbackFontsId(self._vg, baseFont)
    #~ def ResetFallbackFonts(self, char* baseFont):
    #~     c_nanovg.nvgResetFallbackFonts(self._vg, char* baseFont)
    def FontSize(self, size : float):
        c_nanovg.nvgFontSize(self._vg, size)
    def FontBlur(self, blur : float):
        c_nanovg.nvgFontBlur(self._vg, blur)
    def TextLetterSpacing(self, spacing : float):
        c_nanovg.nvgTextLetterSpacing(self._vg, spacing)
    def TextLineHeight(self, lineHeight : float):
        c_nanovg.nvgTextLineHeight(self._vg, lineHeight)
    def TextAlign(self, align : int):
        c_nanovg.nvgTextAlign(self._vg, align)
    def FontFaceId(self, font : int):
        c_nanovg.nvgFontFaceId(self._vg, font)
    #~ def FontFace(self, char* font):
    #~     c_nanovg.nvgFontFace(self._vg, char* font)
    def Text(self, x : float, y : float, string : str, end : str) -> float:
        return c_nanovg.nvgText(self._vg, x, y, string.encode('utf8'), end.encode('utf8'))
    def TextBox(self, x : float, y : float, breakRowWidth : float, string : str, end : str):
        c_nanovg.nvgTextBox(self._vg, x, y, breakRowWidth, string.encode('utf8'), end.encode('utf8'))
    #~ def TextBounds(self, x : float, y : float, string : str, end : str, float* bounds) -> float:
    #~     return c_nanovg.nvgTextBounds(self._vg, x, y, string.encode('utf8'), end.encode('utf8'), bounds)
    #~ def TextBoxBounds(self, x : float, y : float, breakRowWidth : float, string : str, end : str, float* bounds):
    #~     c_nanovg.nvgTextBoxBounds(self._vg, x, y, breakRowWidth, string.encode('utf8'), end.encode('utf8'), float* bounds)
    #~ def TextGlyphPositions(self, x : float, y : float, string : str, end : str, NVGglyphPosition* positions, maxPositions : int) -> int:
    #~     return c_nanovg.nvgTextGlyphPositions(self._vg, x : float, y : float, string.encode('utf8'), end.encode('utf8'), NVGglyphPosition* positions, maxPositions)
    #~ def TextMetrics(self, float* ascender, float* descender, float* lineh):
    #~     c_nanovg.nvgTextMetrics(self._vg, float* ascender, float* descender, float* lineh)
    #~ def TextBreakLines(self, char* string, char* end, breakRowWidth : float, NVGtextRow* rows, maxRows : int) -> int:
    #~     return c_nanovg.nvgTextBreakLines(self._vg, string.encode('utf8'), end.encode('utf8'), breakRowWidth, NVGtextRow* rows, maxRows)
    def DeleteInternal(self):
        c_nanovg.nvgDeleteInternal(self._vg)
    #~ def nvgInternalParams(NVGcontext* ctx) -> NVGparams*:
    #~     return c_nanovg.nvgInternalParams(self._vg)
    def DebugDumpPathCache(self):
        c_nanovg.nvgDebugDumpPathCache(self._vg)

    def DegToRad(deg : float) -> float:
        return c_nanovg.nvgDegToRad(deg)
    def RadToDeg(rad : float) -> float:
        return c_nanovg.nvgRadToDeg(rad)

def CreateGL2(flags : int):
    cdef c_nanovg.NVGcontext * vg = c_nanovg_gl.nvgCreateGL2(flags)
    return _NVGcontext.create(vg)

def CreateGL3(flags : int):
    cdef c_nanovg.NVGcontext * vg = c_nanovg_gl.nvgCreateGL3(flags)
    return _NVGcontext.create(vg)

def CreateGLES2(flags : int):
    cdef c_nanovg.NVGcontext * vg = c_nanovg_gl.nvgCreateGLES2(flags)
    return _NVGcontext.create(vg)

def CreateGLES3(flags : int):
    cdef c_nanovg.NVGcontext * vg = c_nanovg_gl.nvgCreateGLES3(flags)
    return _NVGcontext.create(vg)

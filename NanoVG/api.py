import ctypes
import NanoVG
from .defs import *

def nvgBeginFrame(ctx, windowWidth, windowHeight, devicePixelRatio):
    return NanoVG.library.__NANOVG_LOADER.nvgBeginFrame(ctx, windowWidth, windowHeight, devicePixelRatio)

def nvgCancelFrame(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgCancelFrame(ctx)

def nvgEndFrame(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgEndFrame(ctx)

def nvgGlobalCompositeOperation(ctx, op):
    return NanoVG.library.__NANOVG_LOADER.nvgGlobalCompositeOperation(ctx, op)

def nvgGlobalCompositeBlendFunc(ctx, sfactor, dfactor):
    return NanoVG.library.__NANOVG_LOADER.nvgGlobalCompositeBlendFunc(ctx, sfactor, dfactor)

def nvgGlobalCompositeBlendFuncSeparate(ctx, srcRGB, dstRGB, srcAlpha, dstAlpha):
    return NanoVG.library.__NANOVG_LOADER.nvgGlobalCompositeBlendFuncSeparate(ctx, srcRGB, dstRGB, srcAlpha, dstAlpha)

def nvgRGB(r, g, b):
    return NanoVG.library.__NANOVG_LOADER.nvgRGB(r, g, b)

def nvgRGBf(r, g, b):
    return NanoVG.library.__NANOVG_LOADER.nvgRGBf(r, g, b)

def nvgRGBA(r, g, b, a):
    return NanoVG.library.__NANOVG_LOADER.nvgRGBA(r, g, b, a)

def nvgRGBAf(r, g, b, a):
    return NanoVG.library.__NANOVG_LOADER.nvgRGBAf(r, g, b, a)

def nvgLerpRGBA(c0, c1, u):
    return NanoVG.library.__NANOVG_LOADER.nvgLerpRGBA(c0, c1, u)

def nvgTransRGBA(c0, a):
    return NanoVG.library.__NANOVG_LOADER.nvgTransRGBA(c0, a)

def nvgTransRGBAf(c0, a):
    return NanoVG.library.__NANOVG_LOADER.nvgTransRGBAf(c0, a)

def nvgHSL(h, s, l):
    return NanoVG.library.__NANOVG_LOADER.nvgHSL(h, s, l)

def nvgHSLA(h, s, l, a):
    return NanoVG.library.__NANOVG_LOADER.nvgHSLA(h, s, l, a)

def nvgSave(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgSave(ctx)

def nvgRestore(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgRestore(ctx)

def nvgReset(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgReset(ctx)

def nvgShapeAntiAlias(ctx, enabled):
    return NanoVG.library.__NANOVG_LOADER.nvgShapeAntiAlias(ctx, enabled)

def nvgStrokeColor(ctx, color):
    return NanoVG.library.__NANOVG_LOADER.nvgStrokeColor(ctx, color)

def nvgStrokePaint(ctx, paint):
    return NanoVG.library.__NANOVG_LOADER.nvgStrokePaint(ctx, paint)

def nvgFillColor(ctx, color):
    return NanoVG.library.__NANOVG_LOADER.nvgFillColor(ctx, color)

def nvgFillPaint(ctx, paint):
    return NanoVG.library.__NANOVG_LOADER.nvgFillPaint(ctx, paint)

def nvgMiterLimit(ctx, limit):
    return NanoVG.library.__NANOVG_LOADER.nvgMiterLimit(ctx, limit)

def nvgStrokeWidth(ctx, size):
    return NanoVG.library.__NANOVG_LOADER.nvgStrokeWidth(ctx, size)

def nvgLineCap(ctx, cap):
    return NanoVG.library.__NANOVG_LOADER.nvgLineCap(ctx, cap)

def nvgLineJoin(ctx, join):
    return NanoVG.library.__NANOVG_LOADER.nvgLineJoin(ctx, join)

def nvgGlobalAlpha(ctx, alpha):
    return NanoVG.library.__NANOVG_LOADER.nvgGlobalAlpha(ctx, alpha)

def nvgResetTransform(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgResetTransform(ctx)

def nvgTransform(ctx, a, b, c, d, e, f):
    return NanoVG.library.__NANOVG_LOADER.nvgTransform(ctx, a, b, c, d, e, f)

def nvgTranslate(ctx, x, y):
    return NanoVG.library.__NANOVG_LOADER.nvgTranslate(ctx, x, y)

def nvgRotate(ctx, angle):
    return NanoVG.library.__NANOVG_LOADER.nvgRotate(ctx, angle)

def nvgSkewX(ctx, angle):
    return NanoVG.library.__NANOVG_LOADER.nvgSkewX(ctx, angle)

def nvgSkewY(ctx, angle):
    return NanoVG.library.__NANOVG_LOADER.nvgSkewY(ctx, angle)

def nvgScale(ctx, x, y):
    return NanoVG.library.__NANOVG_LOADER.nvgScale(ctx, x, y)

def nvgCurrentTransform(ctx, xform):
    return NanoVG.library.__NANOVG_LOADER.nvgCurrentTransform(ctx, xform)

def nvgTransformIdentity(dst):
    return NanoVG.library.__NANOVG_LOADER.nvgTransformIdentity(dst)

def nvgTransformTranslate(dst, tx, ty):
    return NanoVG.library.__NANOVG_LOADER.nvgTransformTranslate(dst, tx, ty)

def nvgTransformScale(dst, sx, sy):
    return NanoVG.library.__NANOVG_LOADER.nvgTransformScale(dst, sx, sy)

def nvgTransformRotate(dst, a):
    return NanoVG.library.__NANOVG_LOADER.nvgTransformRotate(dst, a)

def nvgTransformSkewX(dst, a):
    return NanoVG.library.__NANOVG_LOADER.nvgTransformSkewX(dst, a)

def nvgTransformSkewY(dst, a):
    return NanoVG.library.__NANOVG_LOADER.nvgTransformSkewY(dst, a)

def nvgTransformMultiply(dst, src):
    return NanoVG.library.__NANOVG_LOADER.nvgTransformMultiply(dst, src)

def nvgTransformPremultiply(dst, src):
    return NanoVG.library.__NANOVG_LOADER.nvgTransformPremultiply(dst, src)

def nvgTransformInverse(dst, src):
    return NanoVG.library.__NANOVG_LOADER.nvgTransformInverse(dst, src)

def nvgTransformPoint(dstx, dsty, xform, srcx, srcy):
    return NanoVG.library.__NANOVG_LOADER.nvgTransformPoint(dstx, dsty, xform, srcx, srcy)

def nvgDegToRad(deg):
    return NanoVG.library.__NANOVG_LOADER.nvgDegToRad(deg)

def nvgRadToDeg(rad):
    return NanoVG.library.__NANOVG_LOADER.nvgRadToDeg(rad)

def nvgCreateImage(ctx, filename, imageFlags):
    return NanoVG.library.__NANOVG_LOADER.nvgCreateImage(ctx, filename, imageFlags)

def nvgCreateImageMem(ctx, imageFlags, data, ndata):
    return NanoVG.library.__NANOVG_LOADER.nvgCreateImageMem(ctx, imageFlags, data, ndata)

def nvgCreateImageRGBA(ctx, w, h, imageFlags, data):
    return NanoVG.library.__NANOVG_LOADER.nvgCreateImageRGBA(ctx, w, h, imageFlags, data)

def nvgUpdateImage(ctx, image, data):
    return NanoVG.library.__NANOVG_LOADER.nvgUpdateImage(ctx, image, data)

def nvgImageSize(ctx, image, w, h):
    return NanoVG.library.__NANOVG_LOADER.nvgImageSize(ctx, image, w, h)

def nvgDeleteImage(ctx, image):
    return NanoVG.library.__NANOVG_LOADER.nvgDeleteImage(ctx, image)

def nvgLinearGradient(ctx, sx, sy, ex, ey, icol, ocol):
    return NanoVG.library.__NANOVG_LOADER.nvgLinearGradient(ctx, sx, sy, ex, ey, icol, ocol)

def nvgBoxGradient(ctx, x, y, w, h, r, f, icol, ocol):
    return NanoVG.library.__NANOVG_LOADER.nvgBoxGradient(ctx, x, y, w, h, r, f, icol, ocol)

def nvgRadialGradient(ctx, cx, cy, inr, outr, icol, ocol):
    return NanoVG.library.__NANOVG_LOADER.nvgRadialGradient(ctx, cx, cy, inr, outr, icol, ocol)

def nvgImagePattern(ctx, ox, oy, ex, ey, angle, image, alpha):
    return NanoVG.library.__NANOVG_LOADER.nvgImagePattern(ctx, ox, oy, ex, ey, angle, image, alpha)

def nvgScissor(ctx, x, y, w, h):
    return NanoVG.library.__NANOVG_LOADER.nvgScissor(ctx, x, y, w, h)

def nvgIntersectScissor(ctx, x, y, w, h):
    return NanoVG.library.__NANOVG_LOADER.nvgIntersectScissor(ctx, x, y, w, h)

def nvgResetScissor(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgResetScissor(ctx)

def nvgBeginPath(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgBeginPath(ctx)

def nvgMoveTo(ctx, x, y):
    return NanoVG.library.__NANOVG_LOADER.nvgMoveTo(ctx, x, y)

def nvgLineTo(ctx, x, y):
    return NanoVG.library.__NANOVG_LOADER.nvgLineTo(ctx, x, y)

def nvgBezierTo(ctx, c1x, c1y, c2x, c2y, x, y):
    return NanoVG.library.__NANOVG_LOADER.nvgBezierTo(ctx, c1x, c1y, c2x, c2y, x, y)

def nvgQuadTo(ctx, cx, cy, x, y):
    return NanoVG.library.__NANOVG_LOADER.nvgQuadTo(ctx, cx, cy, x, y)

def nvgArcTo(ctx, x1, y1, x2, y2, radius):
    return NanoVG.library.__NANOVG_LOADER.nvgArcTo(ctx, x1, y1, x2, y2, radius)

def nvgClosePath(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgClosePath(ctx)

def nvgPathWinding(ctx, dir):
    return NanoVG.library.__NANOVG_LOADER.nvgPathWinding(ctx, dir)

def nvgArc(ctx, cx, cy, r, a0, a1, dir):
    return NanoVG.library.__NANOVG_LOADER.nvgArc(ctx, cx, cy, r, a0, a1, dir)

def nvgRect(ctx, x, y, w, h):
    return NanoVG.library.__NANOVG_LOADER.nvgRect(ctx, x, y, w, h)

def nvgRoundedRect(ctx, x, y, w, h, r):
    return NanoVG.library.__NANOVG_LOADER.nvgRoundedRect(ctx, x, y, w, h, r)

def nvgRoundedRectVarying(ctx, x, y, w, h, radTopLeft, radTopRight, radBottomRight, radBottomLeft):
    return NanoVG.library.__NANOVG_LOADER.nvgRoundedRectVarying(ctx, x, y, w, h, radTopLeft, radTopRight, radBottomRight, radBottomLeft)

def nvgEllipse(ctx, cx, cy, rx, ry):
    return NanoVG.library.__NANOVG_LOADER.nvgEllipse(ctx, cx, cy, rx, ry)

def nvgCircle(ctx, cx, cy, r):
    return NanoVG.library.__NANOVG_LOADER.nvgCircle(ctx, cx, cy, r)

def nvgFill(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgFill(ctx)

def nvgStroke(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgStroke(ctx)

def nvgCreateFont(ctx, name, filename):
    return NanoVG.library.__NANOVG_LOADER.nvgCreateFont(ctx, name, filename)

def nvgCreateFontMem(ctx, name, data, ndata, freeData):
    return NanoVG.library.__NANOVG_LOADER.nvgCreateFontMem(ctx, name, data, ndata, freeData)

def nvgFindFont(ctx, name):
    return NanoVG.library.__NANOVG_LOADER.nvgFindFont(ctx, name)

def nvgAddFallbackFontId(ctx, baseFont, fallbackFont):
    return NanoVG.library.__NANOVG_LOADER.nvgAddFallbackFontId(ctx, baseFont, fallbackFont)

def nvgAddFallbackFont(ctx, baseFont, fallbackFont):
    return NanoVG.library.__NANOVG_LOADER.nvgAddFallbackFont(ctx, baseFont, fallbackFont)

def nvgFontSize(ctx, size):
    return NanoVG.library.__NANOVG_LOADER.nvgFontSize(ctx, size)

def nvgFontBlur(ctx, blur):
    return NanoVG.library.__NANOVG_LOADER.nvgFontBlur(ctx, blur)

def nvgTextLetterSpacing(ctx, spacing):
    return NanoVG.library.__NANOVG_LOADER.nvgTextLetterSpacing(ctx, spacing)

def nvgTextLineHeight(ctx, lineHeight):
    return NanoVG.library.__NANOVG_LOADER.nvgTextLineHeight(ctx, lineHeight)

def nvgTextAlign(ctx, align):
    return NanoVG.library.__NANOVG_LOADER.nvgTextAlign(ctx, align)

def nvgFontFaceId(ctx, font):
    return NanoVG.library.__NANOVG_LOADER.nvgFontFaceId(ctx, font)

def nvgFontFace(ctx, font):
    return NanoVG.library.__NANOVG_LOADER.nvgFontFace(ctx, font)

def nvgText(ctx, x, y, string, end):
    return NanoVG.library.__NANOVG_LOADER.nvgText(ctx, x, y, string, end)

def nvgTextBox(ctx, x, y, breakRowWidth, string, end):
    return NanoVG.library.__NANOVG_LOADER.nvgTextBox(ctx, x, y, breakRowWidth, string, end)

def nvgTextBounds(ctx, x, y, string, end, bounds):
    return NanoVG.library.__NANOVG_LOADER.nvgTextBounds(ctx, x, y, string, end, bounds)

def nvgTextBoxBounds(ctx, x, y, breakRowWidth, string, end, bounds):
    return NanoVG.library.__NANOVG_LOADER.nvgTextBoxBounds(ctx, x, y, breakRowWidth, string, end, bounds)

def nvgTextGlyphPositions(ctx, x, y, string, end, positions, maxPositions):
    return NanoVG.library.__NANOVG_LOADER.nvgTextGlyphPositions(ctx, x, y, string, end, positions, maxPositions)

def nvgTextMetrics(ctx, ascender, descender, lineh):
    return NanoVG.library.__NANOVG_LOADER.nvgTextMetrics(ctx, ascender, descender, lineh)

def nvgTextBreakLines(ctx, string, end, breakRowWidth, rows, maxRows):
    return NanoVG.library.__NANOVG_LOADER.nvgTextBreakLines(ctx, string, end, breakRowWidth, rows, maxRows)

def nvgSetupGL2():
    return NanoVG.library.__NANOVG_LOADER.nvgSetupGL2()

def nvgCreateGL2(flags):
    return NanoVG.library.__NANOVG_LOADER.nvgCreateGL2(flags)

def nvgDeleteGL2(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgDeleteGL2(ctx)

def nvgSetupGL3():
    return NanoVG.library.__NANOVG_LOADER.nvgSetupGL3()

def nvgCreateGL3(flags):
    return NanoVG.library.__NANOVG_LOADER.nvgCreateGL3(flags)

def nvgDeleteGL3(ctx):
    return NanoVG.library.__NANOVG_LOADER.nvgDeleteGL3(ctx)


# Python-NanoVG : A Python bindings of NanoVG
# Copyright (c) 2017 vaiorabbit
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
#     1. The origin of this software must not be misrepresented; you must not
#     claim that you wrote the original software. If you use this software
#     in a product, an acknowledgment in the product documentation would be
#     appreciated but is not required.
#
#     2. Altered source versions must be plainly marked as such, and must not be
#     misrepresented as being the original software.
#
#     3. This notice may not be removed or altered from any source
#     distribution.

import ctypes
from .defs import *

__NANOVG_LOADER = None

__NANOVG_API_NAMES = []
__NANOVG_API_ARGS_MAP = {}
__NANOVG_API_RETVAL_MAP = {}

def load_nanovg_library(lib, render_backend = 'gl2', output_error = False):

    global __NANOVG_LOADER
    __NANOVG_LOADER = ctypes.cdll.LoadLibrary(lib)

    # API

    __NANOVG_API_NAMES.append('nvgBeginFrame')
    __NANOVG_API_ARGS_MAP['nvgBeginFrame'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgBeginFrame'] = None

    __NANOVG_API_NAMES.append('nvgCancelFrame')
    __NANOVG_API_ARGS_MAP['nvgCancelFrame'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgCancelFrame'] = None

    __NANOVG_API_NAMES.append('nvgEndFrame')
    __NANOVG_API_ARGS_MAP['nvgEndFrame'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgEndFrame'] = None

    __NANOVG_API_NAMES.append('nvgGlobalCompositeOperation')
    __NANOVG_API_ARGS_MAP['nvgGlobalCompositeOperation'] = [ctypes.c_void_p,  ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgGlobalCompositeOperation'] = None

    __NANOVG_API_NAMES.append('nvgGlobalCompositeBlendFunc')
    __NANOVG_API_ARGS_MAP['nvgGlobalCompositeBlendFunc'] = [ctypes.c_void_p, ctypes.c_int32, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgGlobalCompositeBlendFunc'] = None

    __NANOVG_API_NAMES.append('nvgGlobalCompositeBlendFuncSeparate')
    __NANOVG_API_ARGS_MAP['nvgGlobalCompositeBlendFuncSeparate'] = [ctypes.c_void_p, ctypes.c_int32, ctypes.c_int32, ctypes.c_int32, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgGlobalCompositeBlendFuncSeparate'] = None

    __NANOVG_API_NAMES.append('nvgRGB')
    __NANOVG_API_ARGS_MAP['nvgRGB'] = [ctypes.c_ubyte, ctypes.c_ubyte, ctypes.c_ubyte]
    __NANOVG_API_RETVAL_MAP['nvgRGB'] = NVGcolor

    __NANOVG_API_NAMES.append('nvgRGBf')
    __NANOVG_API_ARGS_MAP['nvgRGBf'] = [ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgRGBf'] = NVGcolor

    __NANOVG_API_NAMES.append('nvgRGBA')
    __NANOVG_API_ARGS_MAP['nvgRGBA'] = [ctypes.c_ubyte, ctypes.c_ubyte, ctypes.c_ubyte, ctypes.c_ubyte]
    __NANOVG_API_RETVAL_MAP['nvgRGBA'] = NVGcolor

    __NANOVG_API_NAMES.append('nvgRGBAf')
    __NANOVG_API_ARGS_MAP['nvgRGBAf'] = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgRGBAf'] = NVGcolor

    __NANOVG_API_NAMES.append('nvgLerpRGBA')
    __NANOVG_API_ARGS_MAP['nvgLerpRGBA'] = [NVGcolor, NVGcolor, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgLerpRGBA'] = NVGcolor

    __NANOVG_API_NAMES.append('nvgTransRGBA')
    __NANOVG_API_ARGS_MAP['nvgTransRGBA'] = [NVGcolor, ctypes.c_ubyte]
    __NANOVG_API_RETVAL_MAP['nvgTransRGBA'] = NVGcolor

    __NANOVG_API_NAMES.append('nvgTransRGBAf')
    __NANOVG_API_ARGS_MAP['nvgTransRGBAf'] = [NVGcolor, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTransRGBAf'] = NVGcolor

    __NANOVG_API_NAMES.append('nvgHSL')
    __NANOVG_API_ARGS_MAP['nvgHSL'] = [ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgHSL'] = NVGcolor

    __NANOVG_API_NAMES.append('nvgHSLA')
    __NANOVG_API_ARGS_MAP['nvgHSLA'] = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_ubyte]
    __NANOVG_API_RETVAL_MAP['nvgHSLA'] = NVGcolor

    __NANOVG_API_NAMES.append('nvgSave')
    __NANOVG_API_ARGS_MAP['nvgSave'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgSave'] = None

    __NANOVG_API_NAMES.append('nvgRestore')
    __NANOVG_API_ARGS_MAP['nvgRestore'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgRestore'] = None

    __NANOVG_API_NAMES.append('nvgReset')
    __NANOVG_API_ARGS_MAP['nvgReset'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgReset'] = None

    __NANOVG_API_NAMES.append('nvgShapeAntiAlias')
    __NANOVG_API_ARGS_MAP['nvgShapeAntiAlias'] = [ctypes.c_void_p, NVGcolor]
    __NANOVG_API_RETVAL_MAP['nvgShapeAntiAlias'] = None

    __NANOVG_API_NAMES.append('nvgStrokeColor')
    __NANOVG_API_ARGS_MAP['nvgStrokeColor'] = [ctypes.c_void_p, NVGcolor]
    __NANOVG_API_RETVAL_MAP['nvgStrokeColor'] = None

    __NANOVG_API_NAMES.append('nvgStrokePaint')
    __NANOVG_API_ARGS_MAP['nvgStrokePaint'] = [ctypes.c_void_p, NVGpaint]
    __NANOVG_API_RETVAL_MAP['nvgStrokePaint'] = None

    __NANOVG_API_NAMES.append('nvgFillColor')
    __NANOVG_API_ARGS_MAP['nvgFillColor'] = [ctypes.c_void_p, NVGcolor]
    __NANOVG_API_RETVAL_MAP['nvgFillColor'] = None

    __NANOVG_API_NAMES.append('nvgFillPaint')
    __NANOVG_API_ARGS_MAP['nvgFillPaint'] = [ctypes.c_void_p, NVGpaint]
    __NANOVG_API_RETVAL_MAP['nvgFillPaint'] = None

    __NANOVG_API_NAMES.append('nvgMiterLimit')
    __NANOVG_API_ARGS_MAP['nvgMiterLimit'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgMiterLimit'] = None

    __NANOVG_API_NAMES.append('nvgStrokeWidth')
    __NANOVG_API_ARGS_MAP['nvgStrokeWidth'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgStrokeWidth'] = None

    __NANOVG_API_NAMES.append('nvgLineCap')
    __NANOVG_API_ARGS_MAP['nvgLineCap'] = [ctypes.c_void_p, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgLineCap'] = None

    __NANOVG_API_NAMES.append('nvgLineJoin')
    __NANOVG_API_ARGS_MAP['nvgLineJoin'] = [ctypes.c_void_p, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgLineJoin'] = None

    __NANOVG_API_NAMES.append('nvgGlobalAlpha')
    __NANOVG_API_ARGS_MAP['nvgGlobalAlpha'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgGlobalAlpha'] = None

    __NANOVG_API_NAMES.append('nvgResetTransform')
    __NANOVG_API_ARGS_MAP['nvgResetTransform'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgResetTransform'] = None

    __NANOVG_API_NAMES.append('nvgTransform')
    __NANOVG_API_ARGS_MAP['nvgTransform'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTransform'] = None

    __NANOVG_API_NAMES.append('nvgTranslate')
    __NANOVG_API_ARGS_MAP['nvgTranslate'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTranslate'] = None

    __NANOVG_API_NAMES.append('nvgRotate')
    __NANOVG_API_ARGS_MAP['nvgRotate'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgRotate'] = None

    __NANOVG_API_NAMES.append('nvgSkewX')
    __NANOVG_API_ARGS_MAP['nvgSkewX'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgSkewX'] = None

    __NANOVG_API_NAMES.append('nvgSkewY')
    __NANOVG_API_ARGS_MAP['nvgSkewY'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgSkewY'] = None

    __NANOVG_API_NAMES.append('nvgScale')
    __NANOVG_API_ARGS_MAP['nvgScale'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgScale'] = None

    __NANOVG_API_NAMES.append('nvgCurrentTransform')
    __NANOVG_API_ARGS_MAP['nvgCurrentTransform'] = [ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgCurrentTransform'] = None

    __NANOVG_API_NAMES.append('nvgTransformIdentity')
    __NANOVG_API_ARGS_MAP['nvgTransformIdentity'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgTransformIdentity'] = None

    __NANOVG_API_NAMES.append('nvgTransformTranslate')
    __NANOVG_API_ARGS_MAP['nvgTransformTranslate'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTransformTranslate'] = None

    __NANOVG_API_NAMES.append('nvgTransformScale')
    __NANOVG_API_ARGS_MAP['nvgTransformScale'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTransformScale'] = None

    __NANOVG_API_NAMES.append('nvgTransformRotate')
    __NANOVG_API_ARGS_MAP['nvgTransformRotate'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTransformRotate'] = None

    __NANOVG_API_NAMES.append('nvgTransformSkewX')
    __NANOVG_API_ARGS_MAP['nvgTransformSkewX'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTransformSkewX'] = None

    __NANOVG_API_NAMES.append('nvgTransformSkewY')
    __NANOVG_API_ARGS_MAP['nvgTransformSkewY'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTransformSkewY'] = None

    __NANOVG_API_NAMES.append('nvgTransformMultiply')
    __NANOVG_API_ARGS_MAP['nvgTransformMultiply'] = [ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgTransformMultiply'] = None

    __NANOVG_API_NAMES.append('nvgTransformPremultiply')
    __NANOVG_API_ARGS_MAP['nvgTransformPremultiply'] = [ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgTransformPremultiply'] = None

    __NANOVG_API_NAMES.append('nvgTransformInverse')
    __NANOVG_API_ARGS_MAP['nvgTransformInverse'] = [ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgTransformInverse'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgTransformPoint')
    __NANOVG_API_ARGS_MAP['nvgTransformPoint'] = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTransformPoint'] = None

    __NANOVG_API_NAMES.append('nvgDegToRad')
    __NANOVG_API_ARGS_MAP['nvgDegToRad'] = [ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgDegToRad'] = ctypes.c_float

    __NANOVG_API_NAMES.append('nvgRadToDeg')
    __NANOVG_API_ARGS_MAP['nvgRadToDeg'] = [ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgRadToDeg'] = ctypes.c_float

    __NANOVG_API_NAMES.append('nvgCreateImage')
    __NANOVG_API_ARGS_MAP['nvgCreateImage'] = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgCreateImage'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgCreateImageMem')
    __NANOVG_API_ARGS_MAP['nvgCreateImageMem'] = [ctypes.c_void_p, ctypes.c_int32, ctypes.c_void_p, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgCreateImageMem'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgCreateImageRGBA')
    __NANOVG_API_ARGS_MAP['nvgCreateImageRGBA'] = [ctypes.c_void_p, ctypes.c_int32, ctypes.c_int32, ctypes.c_int32, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgCreateImageRGBA'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgUpdateImage')
    __NANOVG_API_ARGS_MAP['nvgUpdateImage'] = [ctypes.c_void_p, ctypes.c_int32, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgUpdateImage'] = None

    __NANOVG_API_NAMES.append('nvgImageSize')
    __NANOVG_API_ARGS_MAP['nvgImageSize'] = [ctypes.c_void_p, ctypes.c_int32, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
    __NANOVG_API_RETVAL_MAP['nvgImageSize'] = None

    __NANOVG_API_NAMES.append('nvgDeleteImage')
    __NANOVG_API_ARGS_MAP['nvgDeleteImage'] = [ctypes.c_void_p, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgDeleteImage'] = None

    __NANOVG_API_NAMES.append('nvgLinearGradient')
    __NANOVG_API_ARGS_MAP['nvgLinearGradient'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, NVGcolor, NVGcolor]
    __NANOVG_API_RETVAL_MAP['nvgLinearGradient'] = NVGpaint

    __NANOVG_API_NAMES.append('nvgBoxGradient')
    __NANOVG_API_ARGS_MAP['nvgBoxGradient'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, NVGcolor, NVGcolor]
    __NANOVG_API_RETVAL_MAP['nvgBoxGradient'] = NVGpaint

    __NANOVG_API_NAMES.append('nvgRadialGradient')
    __NANOVG_API_ARGS_MAP['nvgRadialGradient'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, NVGcolor, NVGcolor]
    __NANOVG_API_RETVAL_MAP['nvgRadialGradient'] = NVGpaint

    __NANOVG_API_NAMES.append('nvgImagePattern')
    __NANOVG_API_ARGS_MAP['nvgImagePattern'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_int32, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgImagePattern'] = NVGpaint

    __NANOVG_API_NAMES.append('nvgScissor')
    __NANOVG_API_ARGS_MAP['nvgScissor'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgScissor'] = None

    __NANOVG_API_NAMES.append('nvgIntersectScissor')
    __NANOVG_API_ARGS_MAP['nvgIntersectScissor'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgIntersectScissor'] = None

    __NANOVG_API_NAMES.append('nvgResetScissor')
    __NANOVG_API_ARGS_MAP['nvgResetScissor'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgResetScissor'] = None

    __NANOVG_API_NAMES.append('nvgBeginPath')
    __NANOVG_API_ARGS_MAP['nvgBeginPath'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgBeginPath'] = None

    __NANOVG_API_NAMES.append('nvgMoveTo')
    __NANOVG_API_ARGS_MAP['nvgMoveTo'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgMoveTo'] = None

    __NANOVG_API_NAMES.append('nvgLineTo')
    __NANOVG_API_ARGS_MAP['nvgLineTo'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgLineTo'] = None

    __NANOVG_API_NAMES.append('nvgBezierTo')
    __NANOVG_API_ARGS_MAP['nvgBezierTo'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgBezierTo'] = None

    __NANOVG_API_NAMES.append('nvgQuadTo')
    __NANOVG_API_ARGS_MAP['nvgQuadTo'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgQuadTo'] = None

    __NANOVG_API_NAMES.append('nvgArcTo')
    __NANOVG_API_ARGS_MAP['nvgArcTo'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgArcTo'] = None

    __NANOVG_API_NAMES.append('nvgClosePath')
    __NANOVG_API_ARGS_MAP['nvgClosePath'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgClosePath'] = None

    __NANOVG_API_NAMES.append('nvgPathWinding')
    __NANOVG_API_ARGS_MAP['nvgPathWinding'] = [ctypes.c_void_p, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgPathWinding'] = None

    __NANOVG_API_NAMES.append('nvgArc')
    __NANOVG_API_ARGS_MAP['nvgArc'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgArc'] = None

    __NANOVG_API_NAMES.append('nvgRect')
    __NANOVG_API_ARGS_MAP['nvgRect'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgRect'] = None

    __NANOVG_API_NAMES.append('nvgRoundedRect')
    __NANOVG_API_ARGS_MAP['nvgRoundedRect'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgRoundedRect'] = None

    __NANOVG_API_NAMES.append('nvgRoundedRectVarying')
    __NANOVG_API_ARGS_MAP['nvgRoundedRectVarying'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgRoundedRectVarying'] = None

    __NANOVG_API_NAMES.append('nvgEllipse')
    __NANOVG_API_ARGS_MAP['nvgEllipse'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgEllipse'] = None

    __NANOVG_API_NAMES.append('nvgCircle')
    __NANOVG_API_ARGS_MAP['nvgCircle'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgCircle'] = None

    __NANOVG_API_NAMES.append('nvgFill')
    __NANOVG_API_ARGS_MAP['nvgFill'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgFill'] = None

    __NANOVG_API_NAMES.append('nvgStroke')
    __NANOVG_API_ARGS_MAP['nvgStroke'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgStroke'] = None

    __NANOVG_API_NAMES.append('nvgCreateFont')
    __NANOVG_API_ARGS_MAP['nvgCreateFont'] = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgCreateFont'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgCreateFontMem')
    __NANOVG_API_ARGS_MAP['nvgCreateFontMem'] = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int32, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgCreateFontMem'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgFindFont')
    __NANOVG_API_ARGS_MAP['nvgFindFont'] = [ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgFindFont'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgAddFallbackFontId')
    __NANOVG_API_ARGS_MAP['nvgAddFallbackFontId'] = [ctypes.c_void_p, ctypes.c_int32, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgAddFallbackFontId'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgAddFallbackFont')
    __NANOVG_API_ARGS_MAP['nvgAddFallbackFont'] = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgAddFallbackFont'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgFontSize')
    __NANOVG_API_ARGS_MAP['nvgFontSize'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgFontSize'] = None

    __NANOVG_API_NAMES.append('nvgFontBlur')
    __NANOVG_API_ARGS_MAP['nvgFontBlur'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgFontBlur'] = None

    __NANOVG_API_NAMES.append('nvgTextLetterSpacing')
    __NANOVG_API_ARGS_MAP['nvgTextLetterSpacing'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTextLetterSpacing'] = None

    __NANOVG_API_NAMES.append('nvgTextLineHeight')
    __NANOVG_API_ARGS_MAP['nvgTextLineHeight'] = [ctypes.c_void_p, ctypes.c_float]
    __NANOVG_API_RETVAL_MAP['nvgTextLineHeight'] = None

    __NANOVG_API_NAMES.append('nvgTextAlign')
    __NANOVG_API_ARGS_MAP['nvgTextAlign'] = [ctypes.c_void_p, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgTextAlign'] = None

    __NANOVG_API_NAMES.append('nvgFontFaceId')
    __NANOVG_API_ARGS_MAP['nvgFontFaceId'] = [ctypes.c_void_p, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgFontFaceId'] = None

    __NANOVG_API_NAMES.append('nvgFontFace')
    __NANOVG_API_ARGS_MAP['nvgFontFace'] = [ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgFontFace'] = None

    __NANOVG_API_NAMES.append('nvgText')
    __NANOVG_API_ARGS_MAP['nvgText'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgText'] = ctypes.c_float

    __NANOVG_API_NAMES.append('nvgTextBox')
    __NANOVG_API_ARGS_MAP['nvgTextBox'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgTextBox'] = None

    __NANOVG_API_NAMES.append('nvgTextBounds')
    __NANOVG_API_ARGS_MAP['nvgTextBounds'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgTextBounds'] = ctypes.c_float

    __NANOVG_API_NAMES.append('nvgTextBoxBounds')
    __NANOVG_API_ARGS_MAP['nvgTextBoxBounds'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_float)]
    __NANOVG_API_RETVAL_MAP['nvgTextBoxBounds'] = None

    __NANOVG_API_NAMES.append('nvgTextGlyphPositions')
    __NANOVG_API_ARGS_MAP['nvgTextGlyphPositions'] = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgTextGlyphPositions'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgTextMetrics')
    __NANOVG_API_ARGS_MAP['nvgTextMetrics'] = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_float)]
    __NANOVG_API_RETVAL_MAP['nvgTextMetrics'] = None

    __NANOVG_API_NAMES.append('nvgTextBreakLines')
    __NANOVG_API_ARGS_MAP['nvgTextBreakLines'] = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_char_p, ctypes.c_float, ctypes.POINTER(NVGtextRow), ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgTextBreakLines'] = ctypes.c_int32

    __NANOVG_API_NAMES.append('nvgCreateGL2')
    __NANOVG_API_ARGS_MAP['nvgCreateGL2'] = [ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgCreateGL2'] = ctypes.c_void_p

    __NANOVG_API_NAMES.append('nvgDeleteGL2')
    __NANOVG_API_ARGS_MAP['nvgDeleteGL2'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgDeleteGL2'] = None

    __NANOVG_API_NAMES.append('nvgSetupGL2')
    __NANOVG_API_ARGS_MAP['nvgSetupGL2'] = None
    __NANOVG_API_RETVAL_MAP['nvgSetupGL2'] = None

    __NANOVG_API_NAMES.append('nvgCreateGL3')
    __NANOVG_API_ARGS_MAP['nvgCreateGL3'] = [ctypes.c_int32]
    __NANOVG_API_RETVAL_MAP['nvgCreateGL3'] = ctypes.c_void_p

    __NANOVG_API_NAMES.append('nvgDeleteGL3')
    __NANOVG_API_ARGS_MAP['nvgDeleteGL3'] = [ctypes.c_void_p]
    __NANOVG_API_RETVAL_MAP['nvgDeleteGL3'] = None

    __NANOVG_API_NAMES.append('nvgSetupGL3')
    __NANOVG_API_ARGS_MAP['nvgSetupGL3'] = None
    __NANOVG_API_RETVAL_MAP['nvgSetupGL3'] = None

    for api in __NANOVG_API_NAMES:
        try:
            func_ptr = getattr(__NANOVG_LOADER, api) # ctypes _FuncPtr
            func_ptr.argtypes = __NANOVG_API_ARGS_MAP[api]
            func_ptr.restype = __NANOVG_API_RETVAL_MAP[api]
        except AttributeError:
            if output_error:
                print("Python-NANOVG : API {} not found.".format(api))
        finally:
            pass


# Python-NanoVG : A Python bindings of NanoVG
# Copyright (c) 2017-2018 vaiorabbit
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

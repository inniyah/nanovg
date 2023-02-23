cdef extern from "nanovg.h":

    cdef struct NVGcolor:
        float rgba[4]
        float r
        float g
        float b
        float a

    cdef struct NVGpaint:
        float xform[6]
        float extent[2]
        float radius
        float feather
        NVGcolor innerColor
        NVGcolor outerColor
        int image

    cpdef enum NVGwinding:
        NVG_CCW
        NVG_CW

    cpdef enum NVGsolidity:
        NVG_SOLID
        NVG_HOLE

    cpdef enum NVGlineCap:
        NVG_BUTT
        NVG_ROUND
        NVG_SQUARE
        NVG_BEVEL
        NVG_MITER

    cpdef enum NVGalign:
        NVG_ALIGN_LEFT
        NVG_ALIGN_CENTER
        NVG_ALIGN_RIGHT
        NVG_ALIGN_TOP
        NVG_ALIGN_MIDDLE
        NVG_ALIGN_BOTTOM
        NVG_ALIGN_BASELINE

    cpdef enum NVGblendFactor:
        NVG_ZERO
        NVG_ONE
        NVG_SRC_COLOR
        NVG_ONE_MINUS_SRC_COLOR
        NVG_DST_COLOR
        NVG_ONE_MINUS_DST_COLOR
        NVG_SRC_ALPHA
        NVG_ONE_MINUS_SRC_ALPHA
        NVG_DST_ALPHA
        NVG_ONE_MINUS_DST_ALPHA
        NVG_SRC_ALPHA_SATURATE

    cpdef enum NVGcompositeOperation:
        NVG_SOURCE_OVER
        NVG_SOURCE_IN
        NVG_SOURCE_OUT
        NVG_ATOP
        NVG_DESTINATION_OVER
        NVG_DESTINATION_IN
        NVG_DESTINATION_OUT
        NVG_DESTINATION_ATOP
        NVG_LIGHTER
        NVG_COPY
        NVG_XOR

    cdef struct NVGcompositeOperationState:
        int srcRGB
        int dstRGB
        int srcAlpha
        int dstAlpha

    cdef struct NVGglyphPosition:
        char* str
        float x
        float minx
        float maxx

    cdef struct NVGtextRow:
        char* start
        char* end
        char* next
        float width
        float minx
        float maxx

    cpdef enum NVGimageFlags:
        NVG_IMAGE_GENERATE_MIPMAPS
        NVG_IMAGE_REPEATX
        NVG_IMAGE_REPEATY
        NVG_IMAGE_FLIPY
        NVG_IMAGE_PREMULTIPLIED
        NVG_IMAGE_NEAREST

    void nvgBeginFrame(NVGcontext* ctx, float windowWidth, float windowHeight, float devicePixelRatio)

    void nvgCancelFrame(NVGcontext* ctx)

    void nvgEndFrame(NVGcontext* ctx)

    void nvgGlobalCompositeOperation(NVGcontext* ctx, int op)

    void nvgGlobalCompositeBlendFunc(NVGcontext* ctx, int sfactor, int dfactor)

    void nvgGlobalCompositeBlendFuncSeparate(NVGcontext* ctx, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha)

    NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b)

    NVGcolor nvgRGBf(float r, float g, float b)

    NVGcolor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)

    NVGcolor nvgRGBAf(float r, float g, float b, float a)

    NVGcolor nvgLerpRGBA(NVGcolor c0, NVGcolor c1, float u)

    NVGcolor nvgTransRGBA(NVGcolor c0, unsigned char a)

    NVGcolor nvgTransRGBAf(NVGcolor c0, float a)

    NVGcolor nvgHSL(float h, float s, float l)

    NVGcolor nvgHSLA(float h, float s, float l, unsigned char a)

    void nvgSave(NVGcontext* ctx)

    void nvgRestore(NVGcontext* ctx)

    void nvgReset(NVGcontext* ctx)

    void nvgShapeAntiAlias(NVGcontext* ctx, int enabled)

    void nvgStrokeColor(NVGcontext* ctx, NVGcolor color)

    void nvgStrokePaint(NVGcontext* ctx, NVGpaint paint)

    void nvgFillColor(NVGcontext* ctx, NVGcolor color)

    void nvgFillPaint(NVGcontext* ctx, NVGpaint paint)

    void nvgMiterLimit(NVGcontext* ctx, float limit)

    void nvgStrokeWidth(NVGcontext* ctx, float size)

    void nvgLineCap(NVGcontext* ctx, int cap)

    void nvgLineJoin(NVGcontext* ctx, int join)

    void nvgGlobalAlpha(NVGcontext* ctx, float alpha)

    void nvgResetTransform(NVGcontext* ctx)

    void nvgTransform(NVGcontext* ctx, float a, float b, float c, float d, float e, float f)

    void nvgTranslate(NVGcontext* ctx, float x, float y)

    void nvgRotate(NVGcontext* ctx, float angle)

    void nvgSkewX(NVGcontext* ctx, float angle)

    void nvgSkewY(NVGcontext* ctx, float angle)

    void nvgScale(NVGcontext* ctx, float x, float y)

    void nvgCurrentTransform(NVGcontext* ctx, float* xform)

    void nvgTransformIdentity(float* dst)

    void nvgTransformTranslate(float* dst, float tx, float ty)

    void nvgTransformScale(float* dst, float sx, float sy)

    void nvgTransformRotate(float* dst, float a)

    void nvgTransformSkewX(float* dst, float a)

    void nvgTransformSkewY(float* dst, float a)

    void nvgTransformMultiply(float* dst, float* src)

    void nvgTransformPremultiply(float* dst, float* src)

    int nvgTransformInverse(float* dst, float* src)

    void nvgTransformPoint(float* dstx, float* dsty, float* xform, float srcx, float srcy)

    float nvgDegToRad(float deg)

    float nvgRadToDeg(float rad)

    int nvgCreateImage(NVGcontext* ctx, char* filename, int imageFlags)

    int nvgCreateImageMem(NVGcontext* ctx, int imageFlags, unsigned char* data, int ndata)

    int nvgCreateImageRGBA(NVGcontext* ctx, int w, int h, int imageFlags, unsigned char* data)

    int nvgCreateImageAlpha(NVGcontext* ctx, int w, int h, int imageFlags, unsigned char* data)

    void nvgUpdateImage(NVGcontext* ctx, int image, unsigned char* data)

    void nvgImageSize(NVGcontext* ctx, int image, int* w, int* h)

    void nvgDeleteImage(NVGcontext* ctx, int image)

    NVGpaint nvgLinearGradient(NVGcontext* ctx, float sx, float sy, float ex, float ey, NVGcolor icol, NVGcolor ocol)

    NVGpaint nvgBoxGradient(NVGcontext* ctx, float x, float y, float w, float h, float r, float f, NVGcolor icol, NVGcolor ocol)

    NVGpaint nvgRadialGradient(NVGcontext* ctx, float cx, float cy, float inr, float outr, NVGcolor icol, NVGcolor ocol)

    NVGpaint nvgImagePattern(NVGcontext* ctx, float ox, float oy, float ex, float ey, float angle, int image, float alpha)

    void nvgScissor(NVGcontext* ctx, float x, float y, float w, float h)

    void nvgIntersectScissor(NVGcontext* ctx, float x, float y, float w, float h)

    void nvgResetScissor(NVGcontext* ctx)

    void nvgBeginPath(NVGcontext* ctx)

    void nvgMoveTo(NVGcontext* ctx, float x, float y)

    void nvgLineTo(NVGcontext* ctx, float x, float y)

    void nvgBezierTo(NVGcontext* ctx, float c1x, float c1y, float c2x, float c2y, float x, float y)

    void nvgQuadTo(NVGcontext* ctx, float cx, float cy, float x, float y)

    void nvgArcTo(NVGcontext* ctx, float x1, float y1, float x2, float y2, float radius)

    void nvgClosePath(NVGcontext* ctx)

    void nvgPathWinding(NVGcontext* ctx, int dir)

    void nvgArc(NVGcontext* ctx, float cx, float cy, float r, float a0, float a1, int dir)

    void nvgBarc(NVGcontext* ctx, float cx, float cy, float r, float a0, float a1, int dir, int join)

    void nvgRect(NVGcontext* ctx, float x, float y, float w, float h)

    void nvgRoundedRect(NVGcontext* ctx, float x, float y, float w, float h, float r)

    void nvgRoundedRectVarying(NVGcontext* ctx, float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft)

    void nvgEllipse(NVGcontext* ctx, float cx, float cy, float rx, float ry)

    void nvgCircle(NVGcontext* ctx, float cx, float cy, float r)

    void nvgFill(NVGcontext* ctx)

    void nvgStroke(NVGcontext* ctx)

    int nvgCreateFont(NVGcontext* ctx, char* name, char* filename)

    int nvgCreateFontAtIndex(NVGcontext* ctx, char* name, char* filename, int fontIndex)

    int nvgCreateFontMem(NVGcontext* ctx, char* name, unsigned char* data, int ndata, int freeData)

    int nvgCreateFontMemAtIndex(NVGcontext* ctx, char* name, unsigned char* data, int ndata, int freeData, int fontIndex)

    int nvgFindFont(NVGcontext* ctx, char* name)

    int nvgAddFallbackFontId(NVGcontext* ctx, int baseFont, int fallbackFont)

    int nvgAddFallbackFont(NVGcontext* ctx, char* baseFont, char* fallbackFont)

    void nvgResetFallbackFontsId(NVGcontext* ctx, int baseFont)

    void nvgResetFallbackFonts(NVGcontext* ctx, char* baseFont)

    void nvgFontSize(NVGcontext* ctx, float size)

    void nvgFontBlur(NVGcontext* ctx, float blur)

    void nvgTextLetterSpacing(NVGcontext* ctx, float spacing)

    void nvgTextLineHeight(NVGcontext* ctx, float lineHeight)

    void nvgTextAlign(NVGcontext* ctx, int align)

    void nvgFontFaceId(NVGcontext* ctx, int font)

    void nvgFontFace(NVGcontext* ctx, char* font)

    float nvgText(NVGcontext* ctx, float x, float y, char* string, char* end)

    void nvgTextBox(NVGcontext* ctx, float x, float y, float breakRowWidth, char* string, char* end)

    float nvgTextBounds(NVGcontext* ctx, float x, float y, char* string, char* end, float* bounds)

    void nvgTextBoxBounds(NVGcontext* ctx, float x, float y, float breakRowWidth, char* string, char* end, float* bounds)

    int nvgTextGlyphPositions(NVGcontext* ctx, float x, float y, char* string, char* end, NVGglyphPosition* positions, int maxPositions)

    void nvgTextMetrics(NVGcontext* ctx, float* ascender, float* descender, float* lineh)

    int nvgTextBreakLines(NVGcontext* ctx, char* string, char* end, float breakRowWidth, NVGtextRow* rows, int maxRows)

    cpdef enum NVGtexture:
        NVG_TEXTURE_ALPHA
        NVG_TEXTURE_RGBA

    cdef struct NVGscissor:
        float xform[6]
        float extent[2]

    cdef struct NVGvertex:
        float x
        float y
        float u
        float v

    cdef struct NVGpath:
        int first
        int count
        unsigned char closed
        int nbevel
        NVGvertex* fill
        int nfill
        NVGvertex* stroke
        int nstroke
        int winding
        int convex

    ctypedef int (*_NVGparams_renderCreate_ft)(void* uptr)

    ctypedef int (*_NVGparams_renderCreateTexture_ft)(void* uptr, int type, int w, int h, int imageFlags, unsigned char* data)

    ctypedef int (*_NVGparams_renderDeleteTexture_ft)(void* uptr, int image)

    ctypedef int (*_NVGparams_renderUpdateTexture_ft)(void* uptr, int image, int x, int y, int w, int h, unsigned char* data)

    ctypedef int (*_NVGparams_renderGetTextureSize_ft)(void* uptr, int image, int* w, int* h)

    ctypedef void (*_NVGparams_renderViewport_ft)(void* uptr, float width, float height, float devicePixelRatio)

    ctypedef void (*_NVGparams_renderCancel_ft)(void* uptr)

    ctypedef void (*_NVGparams_renderFlush_ft)(void* uptr)

    ctypedef void (*_NVGparams_renderFill_ft)(void* uptr, NVGpaint* paint, NVGcompositeOperationState compositeOperation, NVGscissor* scissor, float fringe, float* bounds, NVGpath* paths, int npaths)

    ctypedef void (*_NVGparams_renderStroke_ft)(void* uptr, NVGpaint* paint, NVGcompositeOperationState compositeOperation, NVGscissor* scissor, float fringe, float strokeWidth, NVGpath* paths, int npaths)

    ctypedef void (*_NVGparams_renderTriangles_ft)(void* uptr, NVGpaint* paint, NVGcompositeOperationState compositeOperation, NVGscissor* scissor, NVGvertex* verts, int nverts, float fringe)

    ctypedef void (*_NVGparams_renderDelete_ft)(void* uptr)

    cdef struct NVGparams:
        void* userPtr
        int edgeAntiAlias
        _NVGparams_renderCreate_ft renderCreate
        _NVGparams_renderCreateTexture_ft renderCreateTexture
        _NVGparams_renderDeleteTexture_ft renderDeleteTexture
        _NVGparams_renderUpdateTexture_ft renderUpdateTexture
        _NVGparams_renderGetTextureSize_ft renderGetTextureSize
        _NVGparams_renderViewport_ft renderViewport
        _NVGparams_renderCancel_ft renderCancel
        _NVGparams_renderFlush_ft renderFlush
        _NVGparams_renderFill_ft renderFill
        _NVGparams_renderStroke_ft renderStroke
        _NVGparams_renderTriangles_ft renderTriangles
        _NVGparams_renderDelete_ft renderDelete

    NVGcontext* nvgCreateInternal(NVGparams* params)

    void nvgDeleteInternal(NVGcontext* ctx)

    NVGparams* nvgInternalParams(NVGcontext* ctx)

    void nvgDebugDumpPathCache(NVGcontext* ctx)

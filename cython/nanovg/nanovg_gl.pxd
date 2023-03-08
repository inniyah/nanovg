cdef extern from "nanovg_gl.h":

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

    ctypedef unsigned int GLenum

    ctypedef unsigned char GLboolean

    ctypedef unsigned int GLbitfield

    ctypedef void GLvoid

    ctypedef signed char GLbyte

    ctypedef short GLshort

    ctypedef int GLint

    ctypedef unsigned char GLubyte

    ctypedef unsigned short GLushort

    ctypedef unsigned int GLuint

    ctypedef int GLsizei

    ctypedef float GLfloat

    ctypedef float GLclampf

    ctypedef double GLdouble

    ctypedef double GLclampd

    void glClearIndex(GLfloat c)

    void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)

    void glClear(GLbitfield mask)

    void glIndexMask(GLuint mask)

    void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)

    void glAlphaFunc(GLenum func, GLclampf ref)

    void glBlendFunc(GLenum sfactor, GLenum dfactor)

    void glLogicOp(GLenum opcode)

    void glCullFace(GLenum mode)

    void glFrontFace(GLenum mode)

    void glPointSize(GLfloat size)

    void glLineWidth(GLfloat width)

    void glLineStipple(GLint factor, GLushort pattern)

    void glPolygonMode(GLenum face, GLenum mode)

    void glPolygonOffset(GLfloat factor, GLfloat units)

    void glPolygonStipple(GLubyte* mask)

    void glGetPolygonStipple(GLubyte* mask)

    void glEdgeFlag(GLboolean flag)

    void glEdgeFlagv(GLboolean* flag)

    void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)

    void glClipPlane(GLenum plane, GLdouble* equation)

    void glGetClipPlane(GLenum plane, GLdouble* equation)

    void glDrawBuffer(GLenum mode)

    void glReadBuffer(GLenum mode)

    void glEnable(GLenum cap)

    void glDisable(GLenum cap)

    GLboolean glIsEnabled(GLenum cap)

    void glEnableClientState(GLenum cap)

    void glDisableClientState(GLenum cap)

    void glGetBooleanv(GLenum pname, GLboolean* params)

    void glGetDoublev(GLenum pname, GLdouble* params)

    void glGetFloatv(GLenum pname, GLfloat* params)

    void glGetIntegerv(GLenum pname, GLint* params)

    void glPushAttrib(GLbitfield mask)

    void glPopAttrib()

    void glPushClientAttrib(GLbitfield mask)

    void glPopClientAttrib()

    GLint glRenderMode(GLenum mode)

    GLenum glGetError()

    GLubyte* glGetString(GLenum name)

    void glFinish()

    void glFlush()

    void glHint(GLenum target, GLenum mode)

    void glClearDepth(GLclampd depth)

    void glDepthFunc(GLenum func)

    void glDepthMask(GLboolean flag)

    void glDepthRange(GLclampd near_val, GLclampd far_val)

    void glClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)

    void glAccum(GLenum op, GLfloat value)

    void glMatrixMode(GLenum mode)

    void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val)

    void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val)

    void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)

    void glPushMatrix()

    void glPopMatrix()

    void glLoadIdentity()

    void glLoadMatrixd(GLdouble* m)

    void glLoadMatrixf(GLfloat* m)

    void glMultMatrixd(GLdouble* m)

    void glMultMatrixf(GLfloat* m)

    void glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)

    void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)

    void glScaled(GLdouble x, GLdouble y, GLdouble z)

    void glScalef(GLfloat x, GLfloat y, GLfloat z)

    void glTranslated(GLdouble x, GLdouble y, GLdouble z)

    void glTranslatef(GLfloat x, GLfloat y, GLfloat z)

    GLboolean glIsList(GLuint list)

    void glDeleteLists(GLuint list, GLsizei range)

    GLuint glGenLists(GLsizei range)

    void glNewList(GLuint list, GLenum mode)

    void glEndList()

    void glCallList(GLuint list)

    void glCallLists(GLsizei n, GLenum type, GLvoid* lists)

    void glListBase(GLuint base)

    void glBegin(GLenum mode)

    void glEnd()

    void glVertex2d(GLdouble x, GLdouble y)

    void glVertex2f(GLfloat x, GLfloat y)

    void glVertex2i(GLint x, GLint y)

    void glVertex2s(GLshort x, GLshort y)

    void glVertex3d(GLdouble x, GLdouble y, GLdouble z)

    void glVertex3f(GLfloat x, GLfloat y, GLfloat z)

    void glVertex3i(GLint x, GLint y, GLint z)

    void glVertex3s(GLshort x, GLshort y, GLshort z)

    void glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w)

    void glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)

    void glVertex4i(GLint x, GLint y, GLint z, GLint w)

    void glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w)

    void glVertex2dv(GLdouble* v)

    void glVertex2fv(GLfloat* v)

    void glVertex2iv(GLint* v)

    void glVertex2sv(GLshort* v)

    void glVertex3dv(GLdouble* v)

    void glVertex3fv(GLfloat* v)

    void glVertex3iv(GLint* v)

    void glVertex3sv(GLshort* v)

    void glVertex4dv(GLdouble* v)

    void glVertex4fv(GLfloat* v)

    void glVertex4iv(GLint* v)

    void glVertex4sv(GLshort* v)

    void glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz)

    void glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz)

    void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz)

    void glNormal3i(GLint nx, GLint ny, GLint nz)

    void glNormal3s(GLshort nx, GLshort ny, GLshort nz)

    void glNormal3bv(GLbyte* v)

    void glNormal3dv(GLdouble* v)

    void glNormal3fv(GLfloat* v)

    void glNormal3iv(GLint* v)

    void glNormal3sv(GLshort* v)

    void glIndexd(GLdouble c)

    void glIndexf(GLfloat c)

    void glIndexi(GLint c)

    void glIndexs(GLshort c)

    void glIndexub(GLubyte c)

    void glIndexdv(GLdouble* c)

    void glIndexfv(GLfloat* c)

    void glIndexiv(GLint* c)

    void glIndexsv(GLshort* c)

    void glIndexubv(GLubyte* c)

    void glColor3b(GLbyte red, GLbyte green, GLbyte blue)

    void glColor3d(GLdouble red, GLdouble green, GLdouble blue)

    void glColor3f(GLfloat red, GLfloat green, GLfloat blue)

    void glColor3i(GLint red, GLint green, GLint blue)

    void glColor3s(GLshort red, GLshort green, GLshort blue)

    void glColor3ub(GLubyte red, GLubyte green, GLubyte blue)

    void glColor3ui(GLuint red, GLuint green, GLuint blue)

    void glColor3us(GLushort red, GLushort green, GLushort blue)

    void glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha)

    void glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha)

    void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)

    void glColor4i(GLint red, GLint green, GLint blue, GLint alpha)

    void glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha)

    void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)

    void glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha)

    void glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha)

    void glColor3bv(GLbyte* v)

    void glColor3dv(GLdouble* v)

    void glColor3fv(GLfloat* v)

    void glColor3iv(GLint* v)

    void glColor3sv(GLshort* v)

    void glColor3ubv(GLubyte* v)

    void glColor3uiv(GLuint* v)

    void glColor3usv(GLushort* v)

    void glColor4bv(GLbyte* v)

    void glColor4dv(GLdouble* v)

    void glColor4fv(GLfloat* v)

    void glColor4iv(GLint* v)

    void glColor4sv(GLshort* v)

    void glColor4ubv(GLubyte* v)

    void glColor4uiv(GLuint* v)

    void glColor4usv(GLushort* v)

    void glTexCoord1d(GLdouble s)

    void glTexCoord1f(GLfloat s)

    void glTexCoord1i(GLint s)

    void glTexCoord1s(GLshort s)

    void glTexCoord2d(GLdouble s, GLdouble t)

    void glTexCoord2f(GLfloat s, GLfloat t)

    void glTexCoord2i(GLint s, GLint t)

    void glTexCoord2s(GLshort s, GLshort t)

    void glTexCoord3d(GLdouble s, GLdouble t, GLdouble r)

    void glTexCoord3f(GLfloat s, GLfloat t, GLfloat r)

    void glTexCoord3i(GLint s, GLint t, GLint r)

    void glTexCoord3s(GLshort s, GLshort t, GLshort r)

    void glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q)

    void glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q)

    void glTexCoord4i(GLint s, GLint t, GLint r, GLint q)

    void glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q)

    void glTexCoord1dv(GLdouble* v)

    void glTexCoord1fv(GLfloat* v)

    void glTexCoord1iv(GLint* v)

    void glTexCoord1sv(GLshort* v)

    void glTexCoord2dv(GLdouble* v)

    void glTexCoord2fv(GLfloat* v)

    void glTexCoord2iv(GLint* v)

    void glTexCoord2sv(GLshort* v)

    void glTexCoord3dv(GLdouble* v)

    void glTexCoord3fv(GLfloat* v)

    void glTexCoord3iv(GLint* v)

    void glTexCoord3sv(GLshort* v)

    void glTexCoord4dv(GLdouble* v)

    void glTexCoord4fv(GLfloat* v)

    void glTexCoord4iv(GLint* v)

    void glTexCoord4sv(GLshort* v)

    void glRasterPos2d(GLdouble x, GLdouble y)

    void glRasterPos2f(GLfloat x, GLfloat y)

    void glRasterPos2i(GLint x, GLint y)

    void glRasterPos2s(GLshort x, GLshort y)

    void glRasterPos3d(GLdouble x, GLdouble y, GLdouble z)

    void glRasterPos3f(GLfloat x, GLfloat y, GLfloat z)

    void glRasterPos3i(GLint x, GLint y, GLint z)

    void glRasterPos3s(GLshort x, GLshort y, GLshort z)

    void glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w)

    void glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)

    void glRasterPos4i(GLint x, GLint y, GLint z, GLint w)

    void glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w)

    void glRasterPos2dv(GLdouble* v)

    void glRasterPos2fv(GLfloat* v)

    void glRasterPos2iv(GLint* v)

    void glRasterPos2sv(GLshort* v)

    void glRasterPos3dv(GLdouble* v)

    void glRasterPos3fv(GLfloat* v)

    void glRasterPos3iv(GLint* v)

    void glRasterPos3sv(GLshort* v)

    void glRasterPos4dv(GLdouble* v)

    void glRasterPos4fv(GLfloat* v)

    void glRasterPos4iv(GLint* v)

    void glRasterPos4sv(GLshort* v)

    void glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)

    void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)

    void glRecti(GLint x1, GLint y1, GLint x2, GLint y2)

    void glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2)

    void glRectdv(GLdouble* v1, GLdouble* v2)

    void glRectfv(GLfloat* v1, GLfloat* v2)

    void glRectiv(GLint* v1, GLint* v2)

    void glRectsv(GLshort* v1, GLshort* v2)

    void glVertexPointer(GLint size, GLenum type, GLsizei stride, GLvoid* ptr)

    void glNormalPointer(GLenum type, GLsizei stride, GLvoid* ptr)

    void glColorPointer(GLint size, GLenum type, GLsizei stride, GLvoid* ptr)

    void glIndexPointer(GLenum type, GLsizei stride, GLvoid* ptr)

    void glTexCoordPointer(GLint size, GLenum type, GLsizei stride, GLvoid* ptr)

    void glEdgeFlagPointer(GLsizei stride, GLvoid* ptr)

    void glGetPointerv(GLenum pname, GLvoid** params)

    void glArrayElement(GLint i)

    void glDrawArrays(GLenum mode, GLint first, GLsizei count)

    void glDrawElements(GLenum mode, GLsizei count, GLenum type, GLvoid* indices)

    void glInterleavedArrays(GLenum format, GLsizei stride, GLvoid* pointer)

    void glShadeModel(GLenum mode)

    void glLightf(GLenum light, GLenum pname, GLfloat param)

    void glLighti(GLenum light, GLenum pname, GLint param)

    void glLightfv(GLenum light, GLenum pname, GLfloat* params)

    void glLightiv(GLenum light, GLenum pname, GLint* params)

    void glGetLightfv(GLenum light, GLenum pname, GLfloat* params)

    void glGetLightiv(GLenum light, GLenum pname, GLint* params)

    void glLightModelf(GLenum pname, GLfloat param)

    void glLightModeli(GLenum pname, GLint param)

    void glLightModelfv(GLenum pname, GLfloat* params)

    void glLightModeliv(GLenum pname, GLint* params)

    void glMaterialf(GLenum face, GLenum pname, GLfloat param)

    void glMateriali(GLenum face, GLenum pname, GLint param)

    void glMaterialfv(GLenum face, GLenum pname, GLfloat* params)

    void glMaterialiv(GLenum face, GLenum pname, GLint* params)

    void glGetMaterialfv(GLenum face, GLenum pname, GLfloat* params)

    void glGetMaterialiv(GLenum face, GLenum pname, GLint* params)

    void glColorMaterial(GLenum face, GLenum mode)

    void glPixelZoom(GLfloat xfactor, GLfloat yfactor)

    void glPixelStoref(GLenum pname, GLfloat param)

    void glPixelStorei(GLenum pname, GLint param)

    void glPixelTransferf(GLenum pname, GLfloat param)

    void glPixelTransferi(GLenum pname, GLint param)

    void glPixelMapfv(GLenum map, GLsizei mapsize, GLfloat* values)

    void glPixelMapuiv(GLenum map, GLsizei mapsize, GLuint* values)

    void glPixelMapusv(GLenum map, GLsizei mapsize, GLushort* values)

    void glGetPixelMapfv(GLenum map, GLfloat* values)

    void glGetPixelMapuiv(GLenum map, GLuint* values)

    void glGetPixelMapusv(GLenum map, GLushort* values)

    void glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, GLubyte* bitmap)

    void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)

    void glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)

    void glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type)

    void glStencilFunc(GLenum func, GLint ref, GLuint mask)

    void glStencilMask(GLuint mask)

    void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)

    void glClearStencil(GLint s)

    void glTexGend(GLenum coord, GLenum pname, GLdouble param)

    void glTexGenf(GLenum coord, GLenum pname, GLfloat param)

    void glTexGeni(GLenum coord, GLenum pname, GLint param)

    void glTexGendv(GLenum coord, GLenum pname, GLdouble* params)

    void glTexGenfv(GLenum coord, GLenum pname, GLfloat* params)

    void glTexGeniv(GLenum coord, GLenum pname, GLint* params)

    void glGetTexGendv(GLenum coord, GLenum pname, GLdouble* params)

    void glGetTexGenfv(GLenum coord, GLenum pname, GLfloat* params)

    void glGetTexGeniv(GLenum coord, GLenum pname, GLint* params)

    void glTexEnvf(GLenum target, GLenum pname, GLfloat param)

    void glTexEnvi(GLenum target, GLenum pname, GLint param)

    void glTexEnvfv(GLenum target, GLenum pname, GLfloat* params)

    void glTexEnviv(GLenum target, GLenum pname, GLint* params)

    void glGetTexEnvfv(GLenum target, GLenum pname, GLfloat* params)

    void glGetTexEnviv(GLenum target, GLenum pname, GLint* params)

    void glTexParameterf(GLenum target, GLenum pname, GLfloat param)

    void glTexParameteri(GLenum target, GLenum pname, GLint param)

    void glTexParameterfv(GLenum target, GLenum pname, GLfloat* params)

    void glTexParameteriv(GLenum target, GLenum pname, GLint* params)

    void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)

    void glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)

    void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat* params)

    void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint* params)

    void glTexImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, GLvoid* pixels)

    void glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid* pixels)

    void glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid* pixels)

    void glGenTextures(GLsizei n, GLuint* textures)

    void glDeleteTextures(GLsizei n, GLuint* textures)

    void glBindTexture(GLenum target, GLuint texture)

    void glPrioritizeTextures(GLsizei n, GLuint* textures, GLclampf* priorities)

    GLboolean glAreTexturesResident(GLsizei n, GLuint* textures, GLboolean* residences)

    GLboolean glIsTexture(GLuint texture)

    void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, GLvoid* pixels)

    void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)

    void glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)

    void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)

    void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)

    void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)

    void glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, GLdouble* points)

    void glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, GLfloat* points)

    void glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble* points)

    void glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat* points)

    void glGetMapdv(GLenum target, GLenum query, GLdouble* v)

    void glGetMapfv(GLenum target, GLenum query, GLfloat* v)

    void glGetMapiv(GLenum target, GLenum query, GLint* v)

    void glEvalCoord1d(GLdouble u)

    void glEvalCoord1f(GLfloat u)

    void glEvalCoord1dv(GLdouble* u)

    void glEvalCoord1fv(GLfloat* u)

    void glEvalCoord2d(GLdouble u, GLdouble v)

    void glEvalCoord2f(GLfloat u, GLfloat v)

    void glEvalCoord2dv(GLdouble* u)

    void glEvalCoord2fv(GLfloat* u)

    void glMapGrid1d(GLint un, GLdouble u1, GLdouble u2)

    void glMapGrid1f(GLint un, GLfloat u1, GLfloat u2)

    void glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2)

    void glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2)

    void glEvalPoint1(GLint i)

    void glEvalPoint2(GLint i, GLint j)

    void glEvalMesh1(GLenum mode, GLint i1, GLint i2)

    void glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2)

    void glFogf(GLenum pname, GLfloat param)

    void glFogi(GLenum pname, GLint param)

    void glFogfv(GLenum pname, GLfloat* params)

    void glFogiv(GLenum pname, GLint* params)

    void glFeedbackBuffer(GLsizei size, GLenum type, GLfloat* buffer)

    void glPassThrough(GLfloat token)

    void glSelectBuffer(GLsizei size, GLuint* buffer)

    void glInitNames()

    void glLoadName(GLuint name)

    void glPushName(GLuint name)

    void glPopName()

    void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid* indices)

    void glTexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid* pixels)

    void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid* pixels)

    void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)

    ctypedef void (*PFNGLDRAWRANGEELEMENTSPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid* indices)

    ctypedef void (*PFNGLTEXIMAGE3DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid* pixels)

    ctypedef void (*PFNGLTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid* pixels)

    ctypedef void (*PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)

    void glColorTable(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, GLvoid* table)

    void glColorSubTable(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, GLvoid* data)

    void glColorTableParameteriv(GLenum target, GLenum pname, GLint* params)

    void glColorTableParameterfv(GLenum target, GLenum pname, GLfloat* params)

    void glCopyColorSubTable(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width)

    void glCopyColorTable(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)

    void glGetColorTable(GLenum target, GLenum format, GLenum type, GLvoid* table)

    void glGetColorTableParameterfv(GLenum target, GLenum pname, GLfloat* params)

    void glGetColorTableParameteriv(GLenum target, GLenum pname, GLint* params)

    void glBlendEquation(GLenum mode)

    void glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)

    void glHistogram(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink)

    void glResetHistogram(GLenum target)

    void glGetHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid* values)

    void glGetHistogramParameterfv(GLenum target, GLenum pname, GLfloat* params)

    void glGetHistogramParameteriv(GLenum target, GLenum pname, GLint* params)

    void glMinmax(GLenum target, GLenum internalformat, GLboolean sink)

    void glResetMinmax(GLenum target)

    void glGetMinmax(GLenum target, GLboolean reset, GLenum format, GLenum types, GLvoid* values)

    void glGetMinmaxParameterfv(GLenum target, GLenum pname, GLfloat* params)

    void glGetMinmaxParameteriv(GLenum target, GLenum pname, GLint* params)

    void glConvolutionFilter1D(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, GLvoid* image)

    void glConvolutionFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* image)

    void glConvolutionParameterf(GLenum target, GLenum pname, GLfloat params)

    void glConvolutionParameterfv(GLenum target, GLenum pname, GLfloat* params)

    void glConvolutionParameteri(GLenum target, GLenum pname, GLint params)

    void glConvolutionParameteriv(GLenum target, GLenum pname, GLint* params)

    void glCopyConvolutionFilter1D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)

    void glCopyConvolutionFilter2D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)

    void glGetConvolutionFilter(GLenum target, GLenum format, GLenum type, GLvoid* image)

    void glGetConvolutionParameterfv(GLenum target, GLenum pname, GLfloat* params)

    void glGetConvolutionParameteriv(GLenum target, GLenum pname, GLint* params)

    void glSeparableFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* row, GLvoid* column)

    void glGetSeparableFilter(GLenum target, GLenum format, GLenum type, GLvoid* row, GLvoid* column, GLvoid* span)

    void glActiveTexture(GLenum texture)

    void glClientActiveTexture(GLenum texture)

    void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, GLvoid* data)

    void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLvoid* data)

    void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLvoid* data)

    void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, GLvoid* data)

    void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLvoid* data)

    void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLvoid* data)

    void glGetCompressedTexImage(GLenum target, GLint lod, GLvoid* img)

    void glMultiTexCoord1d(GLenum target, GLdouble s)

    void glMultiTexCoord1dv(GLenum target, GLdouble* v)

    void glMultiTexCoord1f(GLenum target, GLfloat s)

    void glMultiTexCoord1fv(GLenum target, GLfloat* v)

    void glMultiTexCoord1i(GLenum target, GLint s)

    void glMultiTexCoord1iv(GLenum target, GLint* v)

    void glMultiTexCoord1s(GLenum target, GLshort s)

    void glMultiTexCoord1sv(GLenum target, GLshort* v)

    void glMultiTexCoord2d(GLenum target, GLdouble s, GLdouble t)

    void glMultiTexCoord2dv(GLenum target, GLdouble* v)

    void glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t)

    void glMultiTexCoord2fv(GLenum target, GLfloat* v)

    void glMultiTexCoord2i(GLenum target, GLint s, GLint t)

    void glMultiTexCoord2iv(GLenum target, GLint* v)

    void glMultiTexCoord2s(GLenum target, GLshort s, GLshort t)

    void glMultiTexCoord2sv(GLenum target, GLshort* v)

    void glMultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r)

    void glMultiTexCoord3dv(GLenum target, GLdouble* v)

    void glMultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r)

    void glMultiTexCoord3fv(GLenum target, GLfloat* v)

    void glMultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r)

    void glMultiTexCoord3iv(GLenum target, GLint* v)

    void glMultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r)

    void glMultiTexCoord3sv(GLenum target, GLshort* v)

    void glMultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)

    void glMultiTexCoord4dv(GLenum target, GLdouble* v)

    void glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)

    void glMultiTexCoord4fv(GLenum target, GLfloat* v)

    void glMultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q)

    void glMultiTexCoord4iv(GLenum target, GLint* v)

    void glMultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)

    void glMultiTexCoord4sv(GLenum target, GLshort* v)

    void glLoadTransposeMatrixd(GLdouble m[16])

    void glLoadTransposeMatrixf(GLfloat m[16])

    void glMultTransposeMatrixd(GLdouble m[16])

    void glMultTransposeMatrixf(GLfloat m[16])

    void glSampleCoverage(GLclampf value, GLboolean invert)

    ctypedef void (*PFNGLACTIVETEXTUREPROC)(GLenum texture)

    ctypedef void (*PFNGLSAMPLECOVERAGEPROC)(GLclampf value, GLboolean invert)

    ctypedef void (*PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLvoid* data)

    ctypedef void (*PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLvoid* data)

    ctypedef void (*PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, GLvoid* data)

    ctypedef void (*PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLvoid* data)

    ctypedef void (*PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLvoid* data)

    ctypedef void (*PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, GLvoid* data)

    ctypedef void (*PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint level, GLvoid* img)

    void glActiveTextureARB(GLenum texture)

    void glClientActiveTextureARB(GLenum texture)

    void glMultiTexCoord1dARB(GLenum target, GLdouble s)

    void glMultiTexCoord1dvARB(GLenum target, GLdouble* v)

    void glMultiTexCoord1fARB(GLenum target, GLfloat s)

    void glMultiTexCoord1fvARB(GLenum target, GLfloat* v)

    void glMultiTexCoord1iARB(GLenum target, GLint s)

    void glMultiTexCoord1ivARB(GLenum target, GLint* v)

    void glMultiTexCoord1sARB(GLenum target, GLshort s)

    void glMultiTexCoord1svARB(GLenum target, GLshort* v)

    void glMultiTexCoord2dARB(GLenum target, GLdouble s, GLdouble t)

    void glMultiTexCoord2dvARB(GLenum target, GLdouble* v)

    void glMultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t)

    void glMultiTexCoord2fvARB(GLenum target, GLfloat* v)

    void glMultiTexCoord2iARB(GLenum target, GLint s, GLint t)

    void glMultiTexCoord2ivARB(GLenum target, GLint* v)

    void glMultiTexCoord2sARB(GLenum target, GLshort s, GLshort t)

    void glMultiTexCoord2svARB(GLenum target, GLshort* v)

    void glMultiTexCoord3dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r)

    void glMultiTexCoord3dvARB(GLenum target, GLdouble* v)

    void glMultiTexCoord3fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r)

    void glMultiTexCoord3fvARB(GLenum target, GLfloat* v)

    void glMultiTexCoord3iARB(GLenum target, GLint s, GLint t, GLint r)

    void glMultiTexCoord3ivARB(GLenum target, GLint* v)

    void glMultiTexCoord3sARB(GLenum target, GLshort s, GLshort t, GLshort r)

    void glMultiTexCoord3svARB(GLenum target, GLshort* v)

    void glMultiTexCoord4dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)

    void glMultiTexCoord4dvARB(GLenum target, GLdouble* v)

    void glMultiTexCoord4fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)

    void glMultiTexCoord4fvARB(GLenum target, GLfloat* v)

    void glMultiTexCoord4iARB(GLenum target, GLint s, GLint t, GLint r, GLint q)

    void glMultiTexCoord4ivARB(GLenum target, GLint* v)

    void glMultiTexCoord4sARB(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)

    void glMultiTexCoord4svARB(GLenum target, GLshort* v)

    ctypedef void (*PFNGLACTIVETEXTUREARBPROC)(GLenum texture)

    ctypedef void (*PFNGLCLIENTACTIVETEXTUREARBPROC)(GLenum texture)

    ctypedef void (*PFNGLMULTITEXCOORD1DARBPROC)(GLenum target, GLdouble s)

    ctypedef void (*PFNGLMULTITEXCOORD1DVARBPROC)(GLenum target, GLdouble* v)

    ctypedef void (*PFNGLMULTITEXCOORD1FARBPROC)(GLenum target, GLfloat s)

    ctypedef void (*PFNGLMULTITEXCOORD1FVARBPROC)(GLenum target, GLfloat* v)

    ctypedef void (*PFNGLMULTITEXCOORD1IARBPROC)(GLenum target, GLint s)

    ctypedef void (*PFNGLMULTITEXCOORD1IVARBPROC)(GLenum target, GLint* v)

    ctypedef void (*PFNGLMULTITEXCOORD1SARBPROC)(GLenum target, GLshort s)

    ctypedef void (*PFNGLMULTITEXCOORD1SVARBPROC)(GLenum target, GLshort* v)

    ctypedef void (*PFNGLMULTITEXCOORD2DARBPROC)(GLenum target, GLdouble s, GLdouble t)

    ctypedef void (*PFNGLMULTITEXCOORD2DVARBPROC)(GLenum target, GLdouble* v)

    ctypedef void (*PFNGLMULTITEXCOORD2FARBPROC)(GLenum target, GLfloat s, GLfloat t)

    ctypedef void (*PFNGLMULTITEXCOORD2FVARBPROC)(GLenum target, GLfloat* v)

    ctypedef void (*PFNGLMULTITEXCOORD2IARBPROC)(GLenum target, GLint s, GLint t)

    ctypedef void (*PFNGLMULTITEXCOORD2IVARBPROC)(GLenum target, GLint* v)

    ctypedef void (*PFNGLMULTITEXCOORD2SARBPROC)(GLenum target, GLshort s, GLshort t)

    ctypedef void (*PFNGLMULTITEXCOORD2SVARBPROC)(GLenum target, GLshort* v)

    ctypedef void (*PFNGLMULTITEXCOORD3DARBPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r)

    ctypedef void (*PFNGLMULTITEXCOORD3DVARBPROC)(GLenum target, GLdouble* v)

    ctypedef void (*PFNGLMULTITEXCOORD3FARBPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r)

    ctypedef void (*PFNGLMULTITEXCOORD3FVARBPROC)(GLenum target, GLfloat* v)

    ctypedef void (*PFNGLMULTITEXCOORD3IARBPROC)(GLenum target, GLint s, GLint t, GLint r)

    ctypedef void (*PFNGLMULTITEXCOORD3IVARBPROC)(GLenum target, GLint* v)

    ctypedef void (*PFNGLMULTITEXCOORD3SARBPROC)(GLenum target, GLshort s, GLshort t, GLshort r)

    ctypedef void (*PFNGLMULTITEXCOORD3SVARBPROC)(GLenum target, GLshort* v)

    ctypedef void (*PFNGLMULTITEXCOORD4DARBPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)

    ctypedef void (*PFNGLMULTITEXCOORD4DVARBPROC)(GLenum target, GLdouble* v)

    ctypedef void (*PFNGLMULTITEXCOORD4FARBPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)

    ctypedef void (*PFNGLMULTITEXCOORD4FVARBPROC)(GLenum target, GLfloat* v)

    ctypedef void (*PFNGLMULTITEXCOORD4IARBPROC)(GLenum target, GLint s, GLint t, GLint r, GLint q)

    ctypedef void (*PFNGLMULTITEXCOORD4IVARBPROC)(GLenum target, GLint* v)

    ctypedef void (*PFNGLMULTITEXCOORD4SARBPROC)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)

    ctypedef void (*PFNGLMULTITEXCOORD4SVARBPROC)(GLenum target, GLshort* v)

    void glBlendEquationSeparateATI(GLenum modeRGB, GLenum modeA)

    ctypedef void (*PFNGLBLENDEQUATIONSEPARATEATIPROC)(GLenum modeRGB, GLenum modeA)

    ctypedef void* GLeglImageOES

    ctypedef void (*PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)(GLenum target, GLeglImageOES image)

    ctypedef void (*PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC)(GLenum target, GLeglImageOES image)

    cpdef enum NVGcreateFlags:
        NVG_ANTIALIAS
        NVG_STENCIL_STROKES
        NVG_DEBUG

    ctypedef NVGcontext* (*_NanoVG_GL_Functions_VTable_NanoVG_GL_Functions_VTable_createContext_ft)(int flags)

    ctypedef void (*_NanoVG_GL_Functions_VTable_NanoVG_GL_Functions_VTable_deleteContext_ft)(NVGcontext* ctx)

    ctypedef int (*_NanoVG_GL_Functions_VTable_NanoVG_GL_Functions_VTable_createImageFromHandle_ft)(NVGcontext* ctx, unsigned int textureId, int w, int h, int flags)

    ctypedef unsigned int (*_NanoVG_GL_Functions_VTable_NanoVG_GL_Functions_VTable_getImageHandle_ft)(NVGcontext* ctx, int image)

    ctypedef struct NanoVG_GL_Functions_VTable:
        char* name
        _NanoVG_GL_Functions_VTable_NanoVG_GL_Functions_VTable_createContext_ft createContext
        _NanoVG_GL_Functions_VTable_NanoVG_GL_Functions_VTable_deleteContext_ft deleteContext
        _NanoVG_GL_Functions_VTable_NanoVG_GL_Functions_VTable_createImageFromHandle_ft createImageFromHandle
        _NanoVG_GL_Functions_VTable_NanoVG_GL_Functions_VTable_getImageHandle_ft getImageHandle

    NVGcontext* nvgCreateGL2(int flags)

    void nvgDeleteGL2(NVGcontext* ctx)

    int nvglCreateImageFromHandleGL2(NVGcontext* ctx, GLuint textureId, int w, int h, int flags)

    GLuint nvglImageHandleGL2(NVGcontext* ctx, int image)

    NVGcontext* nvgCreateGL3(int flags)

    void nvgDeleteGL3(NVGcontext* ctx)

    int nvglCreateImageFromHandleGL3(NVGcontext* ctx, GLuint textureId, int w, int h, int flags)

    GLuint nvglImageHandleGL3(NVGcontext* ctx, int image)

    NVGcontext* nvgCreateGLES2(int flags)

    void nvgDeleteGLES2(NVGcontext* ctx)

    int nvglCreateImageFromHandleGLES2(NVGcontext* ctx, GLuint textureId, int w, int h, int flags)

    GLuint nvglImageHandleGLES2(NVGcontext* ctx, int image)

    NVGcontext* nvgCreateGLES3(int flags)

    void nvgDeleteGLES3(NVGcontext* ctx)

    int nvglCreateImageFromHandleGLES3(NVGcontext* ctx, GLuint textureId, int w, int h, int flags)

    GLuint nvglImageHandleGLES3(NVGcontext* ctx, int image)

    cpdef enum NVGimageFlagsGL:
        NVG_IMAGE_NODELETE

    NanoVG_GL_Functions_VTable NanoVG_GL2_Functions_VTable

    NanoVG_GL_Functions_VTable NanoVG_GL3_Functions_VTable

    NanoVG_GL_Functions_VTable NanoVG_GLES2_Functions_VTable

    NanoVG_GL_Functions_VTable NanoVG_GLES3_Functions_VTable

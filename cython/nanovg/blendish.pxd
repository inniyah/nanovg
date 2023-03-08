cdef extern from "blendish.h":

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

    cdef struct BNDwidgetTheme:
        NVGcolor outlineColor
        NVGcolor itemColor
        NVGcolor innerColor
        NVGcolor innerSelectedColor
        NVGcolor textColor
        NVGcolor textSelectedColor
        int shadeTop
        int shadeDown

    cdef struct BNDnodeTheme:
        NVGcolor nodeSelectedColor
        NVGcolor wiresColor
        NVGcolor textSelectedColor
        NVGcolor activeNodeColor
        NVGcolor wireSelectColor
        NVGcolor nodeBackdropColor
        int noodleCurving

    cdef struct BNDtheme:
        NVGcolor backgroundColor
        BNDwidgetTheme regularTheme
        BNDwidgetTheme toolTheme
        BNDwidgetTheme radioTheme
        BNDwidgetTheme textFieldTheme
        BNDwidgetTheme optionTheme
        BNDwidgetTheme choiceTheme
        BNDwidgetTheme numberFieldTheme
        BNDwidgetTheme sliderTheme
        BNDwidgetTheme scrollBarTheme
        BNDwidgetTheme tooltipTheme
        BNDwidgetTheme menuTheme
        BNDwidgetTheme menuItemTheme
        BNDnodeTheme nodeTheme

    cpdef enum BNDtextAlignment:
        BND_LEFT
        BND_CENTER

    cpdef enum BNDwidgetState:
        BND_DEFAULT
        BND_HOVER
        BND_ACTIVE

    cpdef enum BNDcornerFlags:
        BND_CORNER_NONE
        BND_CORNER_TOP_LEFT
        BND_CORNER_TOP_RIGHT
        BND_CORNER_DOWN_RIGHT
        BND_CORNER_DOWN_LEFT
        BND_CORNER_ALL
        BND_CORNER_TOP
        BND_CORNER_DOWN
        BND_CORNER_LEFT
        BND_CORNER_RIGHT

    cpdef enum:
        BND_WIDGET_HEIGHT
        BND_TOOL_WIDTH
        BND_NODE_PORT_RADIUS
        BND_NODE_MARGIN_TOP
        BND_NODE_MARGIN_DOWN
        BND_NODE_MARGIN_SIDE
        BND_NODE_TITLE_HEIGHT
        BND_NODE_ARROW_AREA_WIDTH
        BND_SPLITTER_AREA_SIZE
        BND_SCROLLBAR_WIDTH
        BND_SCROLLBAR_HEIGHT
        BND_VSPACING
        BND_VSPACING_GROUP
        BND_HSPACING

    cpdef enum BNDicon:
        BND_ICON_NONE
        BND_ICON_QUESTION
        BND_ICON_ERROR
        BND_ICON_CANCEL
        BND_ICON_TRIA_RIGHT
        BND_ICON_TRIA_DOWN
        BND_ICON_TRIA_LEFT
        BND_ICON_TRIA_UP
        BND_ICON_ARROW_LEFTRIGHT
        BND_ICON_PLUS
        BND_ICON_DISCLOSURE_TRI_DOWN
        BND_ICON_DISCLOSURE_TRI_RIGHT
        BND_ICON_RADIOBUT_OFF
        BND_ICON_RADIOBUT_ON
        BND_ICON_MENU_PANEL
        BND_ICON_BLENDER
        BND_ICON_GRIP
        BND_ICON_DOT
        BND_ICON_COLLAPSEMENU
        BND_ICON_X
        BND_ICON_GO_LEFT
        BND_ICON_PLUG
        BND_ICON_UI
        BND_ICON_NODE
        BND_ICON_NODE_SEL
        BND_ICON_FULLSCREEN
        BND_ICON_SPLITSCREEN
        BND_ICON_RIGHTARROW_THIN
        BND_ICON_BORDERMOVE
        BND_ICON_VIEWZOOM
        BND_ICON_ZOOMIN
        BND_ICON_ZOOMOUT
        BND_ICON_PANEL_CLOSE
        BND_ICON_COPY_ID
        BND_ICON_EYEDROPPER
        BND_ICON_LINK_AREA
        BND_ICON_AUTO
        BND_ICON_CHECKBOX_DEHLT
        BND_ICON_CHECKBOX_HLT
        BND_ICON_UNLOCKED
        BND_ICON_LOCKED
        BND_ICON_UNPINNED
        BND_ICON_PINNED
        BND_ICON_SCREEN_BACK
        BND_ICON_RIGHTARROW
        BND_ICON_DOWNARROW_HLT
        BND_ICON_DOTSUP
        BND_ICON_DOTSDOWN
        BND_ICON_LINK
        BND_ICON_INLINK
        BND_ICON_PLUGIN
        BND_ICON_HELP
        BND_ICON_GHOST_ENABLED
        BND_ICON_COLOR
        BND_ICON_LINKED
        BND_ICON_UNLINKED
        BND_ICON_HAND
        BND_ICON_ZOOM_ALL
        BND_ICON_ZOOM_SELECTED
        BND_ICON_ZOOM_PREVIOUS
        BND_ICON_ZOOM_IN
        BND_ICON_ZOOM_OUT
        BND_ICON_RENDER_REGION
        BND_ICON_BORDER_RECT
        BND_ICON_BORDER_LASSO
        BND_ICON_FREEZE
        BND_ICON_STYLUS_PRESSURE
        BND_ICON_GHOST_DISABLED
        BND_ICON_NEW
        BND_ICON_FILE_TICK
        BND_ICON_QUIT
        BND_ICON_URL
        BND_ICON_RECOVER_LAST
        BND_ICON_FULLSCREEN_ENTER
        BND_ICON_FULLSCREEN_EXIT
        BND_ICON_BLANK1
        BND_ICON_LAMP
        BND_ICON_MATERIAL
        BND_ICON_TEXTURE
        BND_ICON_ANIM
        BND_ICON_WORLD
        BND_ICON_SCENE
        BND_ICON_EDIT
        BND_ICON_GAME
        BND_ICON_RADIO
        BND_ICON_SCRIPT
        BND_ICON_PARTICLES
        BND_ICON_PHYSICS
        BND_ICON_SPEAKER
        BND_ICON_TEXTURE_SHADED
        BND_ICON_VIEW3D
        BND_ICON_IPO
        BND_ICON_OOPS
        BND_ICON_BUTS
        BND_ICON_FILESEL
        BND_ICON_IMAGE_COL
        BND_ICON_INFO
        BND_ICON_SEQUENCE
        BND_ICON_TEXT
        BND_ICON_IMASEL
        BND_ICON_SOUND
        BND_ICON_ACTION
        BND_ICON_NLA
        BND_ICON_SCRIPTWIN
        BND_ICON_TIME
        BND_ICON_NODETREE
        BND_ICON_LOGIC
        BND_ICON_CONSOLE
        BND_ICON_PREFERENCES
        BND_ICON_CLIP
        BND_ICON_ASSET_MANAGER
        BND_ICON_OBJECT_DATAMODE
        BND_ICON_EDITMODE_HLT
        BND_ICON_FACESEL_HLT
        BND_ICON_VPAINT_HLT
        BND_ICON_TPAINT_HLT
        BND_ICON_WPAINT_HLT
        BND_ICON_SCULPTMODE_HLT
        BND_ICON_POSE_HLT
        BND_ICON_PARTICLEMODE
        BND_ICON_LIGHTPAINT
        BND_ICON_SCENE_DATA
        BND_ICON_RENDERLAYERS
        BND_ICON_WORLD_DATA
        BND_ICON_OBJECT_DATA
        BND_ICON_MESH_DATA
        BND_ICON_CURVE_DATA
        BND_ICON_META_DATA
        BND_ICON_LATTICE_DATA
        BND_ICON_LAMP_DATA
        BND_ICON_MATERIAL_DATA
        BND_ICON_TEXTURE_DATA
        BND_ICON_ANIM_DATA
        BND_ICON_CAMERA_DATA
        BND_ICON_PARTICLE_DATA
        BND_ICON_LIBRARY_DATA_DIRECT
        BND_ICON_GROUP
        BND_ICON_ARMATURE_DATA
        BND_ICON_POSE_DATA
        BND_ICON_BONE_DATA
        BND_ICON_CONSTRAINT
        BND_ICON_SHAPEKEY_DATA
        BND_ICON_CONSTRAINT_BONE
        BND_ICON_CAMERA_STEREO
        BND_ICON_PACKAGE
        BND_ICON_UGLYPACKAGE
        BND_ICON_BRUSH_DATA
        BND_ICON_IMAGE_DATA
        BND_ICON_FILE
        BND_ICON_FCURVE
        BND_ICON_FONT_DATA
        BND_ICON_RENDER_RESULT
        BND_ICON_SURFACE_DATA
        BND_ICON_EMPTY_DATA
        BND_ICON_SETTINGS
        BND_ICON_RENDER_ANIMATION
        BND_ICON_RENDER_STILL
        BND_ICON_BOIDS
        BND_ICON_STRANDS
        BND_ICON_LIBRARY_DATA_INDIRECT
        BND_ICON_GREASEPENCIL
        BND_ICON_LINE_DATA
        BND_ICON_GROUP_BONE
        BND_ICON_GROUP_VERTEX
        BND_ICON_GROUP_VCOL
        BND_ICON_GROUP_UVS
        BND_ICON_RNA
        BND_ICON_RNA_ADD
        BND_ICON_OUTLINER_OB_EMPTY
        BND_ICON_OUTLINER_OB_MESH
        BND_ICON_OUTLINER_OB_CURVE
        BND_ICON_OUTLINER_OB_LATTICE
        BND_ICON_OUTLINER_OB_META
        BND_ICON_OUTLINER_OB_LAMP
        BND_ICON_OUTLINER_OB_CAMERA
        BND_ICON_OUTLINER_OB_ARMATURE
        BND_ICON_OUTLINER_OB_FONT
        BND_ICON_OUTLINER_OB_SURFACE
        BND_ICON_OUTLINER_OB_SPEAKER
        BND_ICON_RESTRICT_VIEW_OFF
        BND_ICON_RESTRICT_VIEW_ON
        BND_ICON_RESTRICT_SELECT_OFF
        BND_ICON_RESTRICT_SELECT_ON
        BND_ICON_RESTRICT_RENDER_OFF
        BND_ICON_RESTRICT_RENDER_ON
        BND_ICON_OUTLINER_DATA_EMPTY
        BND_ICON_OUTLINER_DATA_MESH
        BND_ICON_OUTLINER_DATA_CURVE
        BND_ICON_OUTLINER_DATA_LATTICE
        BND_ICON_OUTLINER_DATA_META
        BND_ICON_OUTLINER_DATA_LAMP
        BND_ICON_OUTLINER_DATA_CAMERA
        BND_ICON_OUTLINER_DATA_ARMATURE
        BND_ICON_OUTLINER_DATA_FONT
        BND_ICON_OUTLINER_DATA_SURFACE
        BND_ICON_OUTLINER_DATA_SPEAKER
        BND_ICON_OUTLINER_DATA_POSE
        BND_ICON_MESH_PLANE
        BND_ICON_MESH_CUBE
        BND_ICON_MESH_CIRCLE
        BND_ICON_MESH_UVSPHERE
        BND_ICON_MESH_ICOSPHERE
        BND_ICON_MESH_GRID
        BND_ICON_MESH_MONKEY
        BND_ICON_MESH_CYLINDER
        BND_ICON_MESH_TORUS
        BND_ICON_MESH_CONE
        BND_ICON_LAMP_POINT
        BND_ICON_LAMP_SUN
        BND_ICON_LAMP_SPOT
        BND_ICON_LAMP_HEMI
        BND_ICON_LAMP_AREA
        BND_ICON_META_EMPTY
        BND_ICON_META_PLANE
        BND_ICON_META_CUBE
        BND_ICON_META_BALL
        BND_ICON_META_ELLIPSOID
        BND_ICON_META_CAPSULE
        BND_ICON_SURFACE_NCURVE
        BND_ICON_SURFACE_NCIRCLE
        BND_ICON_SURFACE_NSURFACE
        BND_ICON_SURFACE_NCYLINDER
        BND_ICON_SURFACE_NSPHERE
        BND_ICON_SURFACE_NTORUS
        BND_ICON_CURVE_BEZCURVE
        BND_ICON_CURVE_BEZCIRCLE
        BND_ICON_CURVE_NCURVE
        BND_ICON_CURVE_NCIRCLE
        BND_ICON_CURVE_PATH
        BND_ICON_COLOR_RED
        BND_ICON_COLOR_GREEN
        BND_ICON_COLOR_BLUE
        BND_ICON_FORCE_FORCE
        BND_ICON_FORCE_WIND
        BND_ICON_FORCE_VORTEX
        BND_ICON_FORCE_MAGNETIC
        BND_ICON_FORCE_HARMONIC
        BND_ICON_FORCE_CHARGE
        BND_ICON_FORCE_LENNARDJONES
        BND_ICON_FORCE_TEXTURE
        BND_ICON_FORCE_CURVE
        BND_ICON_FORCE_BOID
        BND_ICON_FORCE_TURBULENCE
        BND_ICON_FORCE_DRAG
        BND_ICON_FORCE_SMOKEFLOW
        BND_ICON_MODIFIER
        BND_ICON_MOD_WAVE
        BND_ICON_MOD_BUILD
        BND_ICON_MOD_DECIM
        BND_ICON_MOD_MIRROR
        BND_ICON_MOD_SOFT
        BND_ICON_MOD_SUBSURF
        BND_ICON_HOOK
        BND_ICON_MOD_PHYSICS
        BND_ICON_MOD_PARTICLES
        BND_ICON_MOD_BOOLEAN
        BND_ICON_MOD_EDGESPLIT
        BND_ICON_MOD_ARRAY
        BND_ICON_MOD_UVPROJECT
        BND_ICON_MOD_DISPLACE
        BND_ICON_MOD_CURVE
        BND_ICON_MOD_LATTICE
        BND_ICON_CONSTRAINT_DATA
        BND_ICON_MOD_ARMATURE
        BND_ICON_MOD_SHRINKWRAP
        BND_ICON_MOD_CAST
        BND_ICON_MOD_MESHDEFORM
        BND_ICON_MOD_BEVEL
        BND_ICON_MOD_SMOOTH
        BND_ICON_MOD_SIMPLEDEFORM
        BND_ICON_MOD_MASK
        BND_ICON_MOD_CLOTH
        BND_ICON_MOD_EXPLODE
        BND_ICON_MOD_FLUIDSIM
        BND_ICON_MOD_MULTIRES
        BND_ICON_MOD_SMOKE
        BND_ICON_MOD_SOLIDIFY
        BND_ICON_MOD_SCREW
        BND_ICON_MOD_VERTEX_WEIGHT
        BND_ICON_MOD_DYNAMICPAINT
        BND_ICON_MOD_REMESH
        BND_ICON_MOD_OCEAN
        BND_ICON_MOD_WARP
        BND_ICON_MOD_SKIN
        BND_ICON_MOD_TRIANGULATE
        BND_ICON_MOD_WIREFRAME
        BND_ICON_REC
        BND_ICON_PLAY
        BND_ICON_FF
        BND_ICON_REW
        BND_ICON_PAUSE
        BND_ICON_PREV_KEYFRAME
        BND_ICON_NEXT_KEYFRAME
        BND_ICON_PLAY_AUDIO
        BND_ICON_PLAY_REVERSE
        BND_ICON_PREVIEW_RANGE
        BND_ICON_ACTION_TWEAK
        BND_ICON_PMARKER_ACT
        BND_ICON_PMARKER_SEL
        BND_ICON_PMARKER
        BND_ICON_MARKER_HLT
        BND_ICON_MARKER
        BND_ICON_SPACE2
        BND_ICON_SPACE3
        BND_ICON_KEYINGSET
        BND_ICON_KEY_DEHLT
        BND_ICON_KEY_HLT
        BND_ICON_MUTE_IPO_OFF
        BND_ICON_MUTE_IPO_ON
        BND_ICON_VISIBLE_IPO_OFF
        BND_ICON_VISIBLE_IPO_ON
        BND_ICON_DRIVER
        BND_ICON_SOLO_OFF
        BND_ICON_SOLO_ON
        BND_ICON_FRAME_PREV
        BND_ICON_FRAME_NEXT
        BND_ICON_NLA_PUSHDOWN
        BND_ICON_IPO_CONSTANT
        BND_ICON_IPO_LINEAR
        BND_ICON_IPO_BEZIER
        BND_ICON_IPO_SINE
        BND_ICON_IPO_QUAD
        BND_ICON_IPO_CUBIC
        BND_ICON_IPO_QUART
        BND_ICON_IPO_QUINT
        BND_ICON_IPO_EXPO
        BND_ICON_IPO_CIRC
        BND_ICON_IPO_BOUNCE
        BND_ICON_IPO_ELASTIC
        BND_ICON_IPO_BACK
        BND_ICON_IPO_EASE_IN
        BND_ICON_IPO_EASE_OUT
        BND_ICON_IPO_EASE_IN_OUT
        BND_ICON_VERTEXSEL
        BND_ICON_EDGESEL
        BND_ICON_FACESEL
        BND_ICON_LOOPSEL
        BND_ICON_ROTATE
        BND_ICON_CURSOR
        BND_ICON_ROTATECOLLECTION
        BND_ICON_ROTATECENTER
        BND_ICON_ROTACTIVE
        BND_ICON_ALIGN
        BND_ICON_SMOOTHCURVE
        BND_ICON_SPHERECURVE
        BND_ICON_ROOTCURVE
        BND_ICON_SHARPCURVE
        BND_ICON_LINCURVE
        BND_ICON_NOCURVE
        BND_ICON_RNDCURVE
        BND_ICON_PROP_OFF
        BND_ICON_PROP_ON
        BND_ICON_PROP_CON
        BND_ICON_SCULPT_DYNTOPO
        BND_ICON_PARTICLE_POINT
        BND_ICON_PARTICLE_TIP
        BND_ICON_PARTICLE_PATH
        BND_ICON_MAN_TRANS
        BND_ICON_MAN_ROT
        BND_ICON_MAN_SCALE
        BND_ICON_MANIPUL
        BND_ICON_SNAP_OFF
        BND_ICON_SNAP_ON
        BND_ICON_SNAP_NORMAL
        BND_ICON_SNAP_INCREMENT
        BND_ICON_SNAP_VERTEX
        BND_ICON_SNAP_EDGE
        BND_ICON_SNAP_FACE
        BND_ICON_SNAP_VOLUME
        BND_ICON_STICKY_UVS_LOC
        BND_ICON_STICKY_UVS_DISABLE
        BND_ICON_STICKY_UVS_VERT
        BND_ICON_CLIPUV_DEHLT
        BND_ICON_CLIPUV_HLT
        BND_ICON_SNAP_PEEL_OBJECT
        BND_ICON_GRID
        BND_ICON_PASTEDOWN
        BND_ICON_COPYDOWN
        BND_ICON_PASTEFLIPUP
        BND_ICON_PASTEFLIPDOWN
        BND_ICON_SNAP_SURFACE
        BND_ICON_AUTOMERGE_ON
        BND_ICON_AUTOMERGE_OFF
        BND_ICON_RETOPO
        BND_ICON_UV_VERTEXSEL
        BND_ICON_UV_EDGESEL
        BND_ICON_UV_FACESEL
        BND_ICON_UV_ISLANDSEL
        BND_ICON_UV_SYNC_SELECT
        BND_ICON_BBOX
        BND_ICON_WIRE
        BND_ICON_SOLID
        BND_ICON_SMOOTH
        BND_ICON_POTATO
        BND_ICON_ORTHO
        BND_ICON_LOCKVIEW_OFF
        BND_ICON_LOCKVIEW_ON
        BND_ICON_AXIS_SIDE
        BND_ICON_AXIS_FRONT
        BND_ICON_AXIS_TOP
        BND_ICON_NDOF_DOM
        BND_ICON_NDOF_TURN
        BND_ICON_NDOF_FLY
        BND_ICON_NDOF_TRANS
        BND_ICON_LAYER_USED
        BND_ICON_LAYER_ACTIVE
        BND_ICON_SORTALPHA
        BND_ICON_SORTBYEXT
        BND_ICON_SORTTIME
        BND_ICON_SORTSIZE
        BND_ICON_LONGDISPLAY
        BND_ICON_SHORTDISPLAY
        BND_ICON_GHOST
        BND_ICON_IMGDISPLAY
        BND_ICON_SAVE_AS
        BND_ICON_SAVE_COPY
        BND_ICON_BOOKMARKS
        BND_ICON_FONTPREVIEW
        BND_ICON_FILTER
        BND_ICON_NEWFOLDER
        BND_ICON_OPEN_RECENT
        BND_ICON_FILE_PARENT
        BND_ICON_FILE_REFRESH
        BND_ICON_FILE_FOLDER
        BND_ICON_FILE_BLANK
        BND_ICON_FILE_BLEND
        BND_ICON_FILE_IMAGE
        BND_ICON_FILE_MOVIE
        BND_ICON_FILE_SCRIPT
        BND_ICON_FILE_SOUND
        BND_ICON_FILE_FONT
        BND_ICON_FILE_TEXT
        BND_ICON_RECOVER_AUTO
        BND_ICON_SAVE_PREFS
        BND_ICON_LINK_BLEND
        BND_ICON_APPEND_BLEND
        BND_ICON_IMPORT
        BND_ICON_EXPORT
        BND_ICON_EXTERNAL_DATA
        BND_ICON_LOAD_FACTORY
        BND_ICON_LOOP_BACK
        BND_ICON_LOOP_FORWARDS
        BND_ICON_BACK
        BND_ICON_FORWARD
        BND_ICON_FILE_BACKUP
        BND_ICON_DISK_DRIVE
        BND_ICON_MATPLANE
        BND_ICON_MATSPHERE
        BND_ICON_MATCUBE
        BND_ICON_MONKEY
        BND_ICON_HAIR
        BND_ICON_ALIASED
        BND_ICON_ANTIALIASED
        BND_ICON_MAT_SPHERE_SKY
        BND_ICON_WORDWRAP_OFF
        BND_ICON_WORDWRAP_ON
        BND_ICON_SYNTAX_OFF
        BND_ICON_SYNTAX_ON
        BND_ICON_LINENUMBERS_OFF
        BND_ICON_LINENUMBERS_ON
        BND_ICON_SCRIPTPLUGINS
        BND_ICON_SEQ_SEQUENCER
        BND_ICON_SEQ_PREVIEW
        BND_ICON_SEQ_LUMA_WAVEFORM
        BND_ICON_SEQ_CHROMA_SCOPE
        BND_ICON_SEQ_HISTOGRAM
        BND_ICON_SEQ_SPLITVIEW
        BND_ICON_IMAGE_RGB
        BND_ICON_IMAGE_RGB_ALPHA
        BND_ICON_IMAGE_ALPHA
        BND_ICON_IMAGE_ZDEPTH
        BND_ICON_IMAGEFILE

    void bndSetTheme(BNDtheme theme)

    BNDtheme* bndGetTheme()

    void bndSetIconImage(int image)

    void bndSetFont(int font)

    void bndLabel(NVGcontext* ctx, float x, float y, float w, float h, int iconid, char* label)

    void bndToolButton(NVGcontext* ctx, float x, float y, float w, float h, int flags, BNDwidgetState state, int iconid, char* label)

    void bndRadioButton(NVGcontext* ctx, float x, float y, float w, float h, int flags, BNDwidgetState state, int iconid, char* label)

    int bndTextFieldTextPosition(NVGcontext* ctx, float x, float y, float w, float h, int iconid, char* text, int px, int py)

    void bndTextField(NVGcontext* ctx, float x, float y, float w, float h, int flags, BNDwidgetState state, int iconid, char* text, int cbegin, int cend)

    void bndOptionButton(NVGcontext* ctx, float x, float y, float w, float h, BNDwidgetState state, char* label)

    void bndChoiceButton(NVGcontext* ctx, float x, float y, float w, float h, int flags, BNDwidgetState state, int iconid, char* label)

    void bndColorButton(NVGcontext* ctx, float x, float y, float w, float h, int flags, NVGcolor color)

    void bndNumberField(NVGcontext* ctx, float x, float y, float w, float h, int flags, BNDwidgetState state, char* label, char* value)

    void bndSlider(NVGcontext* ctx, float x, float y, float w, float h, int flags, BNDwidgetState state, float progress, char* label, char* value)

    void bndScrollBar(NVGcontext* ctx, float x, float y, float w, float h, BNDwidgetState state, float offset, float size)

    void bndMenuBackground(NVGcontext* ctx, float x, float y, float w, float h, int flags)

    void bndMenuLabel(NVGcontext* ctx, float x, float y, float w, float h, int iconid, char* label)

    void bndMenuItem(NVGcontext* ctx, float x, float y, float w, float h, BNDwidgetState state, int iconid, char* label)

    void bndTooltipBackground(NVGcontext* ctx, float x, float y, float w, float h)

    void bndNodePort(NVGcontext* ctx, float x, float y, BNDwidgetState state, NVGcolor color)

    void bndNodeWire(NVGcontext* ctx, float x0, float y0, float x1, float y1, BNDwidgetState state0, BNDwidgetState state1)

    void bndColoredNodeWire(NVGcontext* ctx, float x0, float y0, float x1, float y1, NVGcolor color0, NVGcolor color1)

    void bndNodeBackground(NVGcontext* ctx, float x, float y, float w, float h, BNDwidgetState state, int iconid, char* label, NVGcolor titleColor)

    void bndSplitterWidgets(NVGcontext* ctx, float x, float y, float w, float h)

    void bndJoinAreaOverlay(NVGcontext* ctx, float x, float y, float w, float h, int vertical, int mirror)

    float bndLabelWidth(NVGcontext* ctx, int iconid, char* label)

    float bndLabelHeight(NVGcontext* ctx, int iconid, char* label, float width)

    NVGcolor bndTransparent(NVGcolor color)

    NVGcolor bndOffsetColor(NVGcolor color, int delta)

    void bndSelectCorners(float* radiuses, float r, int flags)

    void bndInnerColors(NVGcolor* shade_top, NVGcolor* shade_down, BNDwidgetTheme* theme, BNDwidgetState state, int flipActive)

    NVGcolor bndTextColor(BNDwidgetTheme* theme, BNDwidgetState state)

    void bndScrollHandleRect(float* x, float* y, float* w, float* h, float offset, float size)

    void bndRoundedBox(NVGcontext* ctx, float x, float y, float w, float h, float cr0, float cr1, float cr2, float cr3)

    void bndBackground(NVGcontext* ctx, float x, float y, float w, float h)

    void bndBevel(NVGcontext* ctx, float x, float y, float w, float h)

    void bndBevelInset(NVGcontext* ctx, float x, float y, float w, float h, float cr2, float cr3)

    void bndIcon(NVGcontext* ctx, float x, float y, int iconid)

    void bndDropShadow(NVGcontext* ctx, float x, float y, float w, float h, float r, float feather, float alpha)

    void bndInnerBox(NVGcontext* ctx, float x, float y, float w, float h, float cr0, float cr1, float cr2, float cr3, NVGcolor shade_top, NVGcolor shade_down)

    void bndOutlineBox(NVGcontext* ctx, float x, float y, float w, float h, float cr0, float cr1, float cr2, float cr3, NVGcolor color)

    void bndIconLabelValue(NVGcontext* ctx, float x, float y, float w, float h, int iconid, NVGcolor color, int align, float fontsize, char* label, char* value)

    void bndNodeIconLabel(NVGcontext* ctx, float x, float y, float w, float h, int iconid, NVGcolor color, NVGcolor shadowColor, int align, float fontsize, char* label)

    int bndIconLabelTextPosition(NVGcontext* ctx, float x, float y, float w, float h, int iconid, float fontsize, char* label, int px, int py)

    void bndIconLabelCaret(NVGcontext* ctx, float x, float y, float w, float h, int iconid, NVGcolor color, float fontsize, char* label, NVGcolor caretcolor, int cbegin, int cend)

    void bndCheck(NVGcontext* ctx, float ox, float oy, NVGcolor color)

    void bndArrow(NVGcontext* ctx, float x, float y, float s, NVGcolor color)

    void bndUpDownArrow(NVGcontext* ctx, float x, float y, float s, NVGcolor color)

    void bndNodeArrowDown(NVGcontext* ctx, float x, float y, float s, NVGcolor color)

    NVGcolor bndNodeWireColor(BNDnodeTheme* theme, BNDwidgetState state)

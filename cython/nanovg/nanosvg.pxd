cdef extern from "nanosvg.h":

    cpdef enum NSVGpaintType:
        NSVG_PAINT_UNDEF
        NSVG_PAINT_NONE
        NSVG_PAINT_COLOR
        NSVG_PAINT_LINEAR_GRADIENT
        NSVG_PAINT_RADIAL_GRADIENT

    cpdef enum NSVGspreadType:
        NSVG_SPREAD_PAD
        NSVG_SPREAD_REFLECT
        NSVG_SPREAD_REPEAT

    cpdef enum NSVGlineJoin:
        NSVG_JOIN_MITER
        NSVG_JOIN_ROUND
        NSVG_JOIN_BEVEL

    cpdef enum NSVGlineCap:
        NSVG_CAP_BUTT
        NSVG_CAP_ROUND
        NSVG_CAP_SQUARE

    cpdef enum NSVGfillRule:
        NSVG_FILLRULE_NONZERO
        NSVG_FILLRULE_EVENODD

    cpdef enum NSVGflags:
        NSVG_FLAGS_VISIBLE

    cdef struct NSVGgradientStop:
        unsigned int color
        float offset

    cdef struct NSVGgradient:
        float xform[6]
        char spread
        float fx
        float fy
        int nstops
        NSVGgradientStop stops[1]

    cdef struct NSVGpaint:
        signed char type
        unsigned int color
        NSVGgradient* gradient

    cdef struct NSVGpath:
        float* pts
        int npts
        char closed
        float bounds[4]
        NSVGpath* next

    cdef struct NSVGshape:
        char id[64]
        NSVGpaint fill
        NSVGpaint stroke
        float opacity
        float strokeWidth
        float strokeDashOffset
        float strokeDashArray[8]
        char strokeDashCount
        char strokeLineJoin
        char strokeLineCap
        float miterLimit
        char fillRule
        unsigned char flags
        float bounds[4]
        char fillGradient[64]
        char strokeGradient[64]
        float xform[6]
        NSVGpath* paths
        NSVGshape* next

    cdef struct NSVGimage:
        float width
        float height
        NSVGshape* shapes

    NSVGimage* nsvgParseFromFile(char* filename, char* units, float dpi)

    NSVGimage* nsvgParse(char* input, char* units, float dpi)

    NSVGpath* nsvgDuplicatePath(NSVGpath* p)

    void nsvgDelete(NSVGimage* image)

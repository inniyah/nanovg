import ctypes

################################################################################

class _NVGrgba4(ctypes.Structure): # Internal
    _fields_ = [('r', ctypes.c_float),
                ('g', ctypes.c_float),
                ('b', ctypes.c_float),
                ('a', ctypes.c_float)]

class _NVGrgbaA(ctypes.Structure): # Internal
    _fields_ = [('rgba', ctypes.c_float * 4)]


# See https://docs.python.org/3/library/ctypes.html#ctypes.Structure._anonymous_
class NVGcolor(ctypes.Union):
    _anonymous_ = ('rgbaA', 'rgba4')
    _fields_ = [('rgbaA', _NVGrgba4),
                ('rgba4', _NVGrgbaA)]

class NVGpaint(ctypes.Structure):
    _fields_ = [("xform", ctypes.c_float * 6),
                ("extent", ctypes.c_float * 2),
                ("radius", ctypes.c_float),
                ("feather", ctypes.c_float),
                ("innerColor",  NVGcolor),
                ("outerColor",  NVGcolor),
                ("image", ctypes.c_int32)]

class NVGcompositeOperationState(ctypes.Structure):
    _fields_ = [("srcRGB", ctypes.c_int32),
                ("dstRGB", ctypes.c_int32),
                ("srcAlpha", ctypes.c_int32),
                ("dstAlpha", ctypes.c_int32)]

class NVGglyphPosition(ctypes.Structure):
    _fields_ = [("str", ctypes.c_void_p),
                ("x", ctypes.c_float),
                ("minx", ctypes.c_float),
                ("maxx", ctypes.c_float)]

class NVGtextRow(ctypes.Structure):
    _fields_ = [("start", ctypes.c_void_p),
                ("end", ctypes.c_void_p),
                ("next", ctypes.c_void_p),
                ("width", ctypes.c_float),
                ("minx", ctypes.c_float),
                ("maxx", ctypes.c_float)]

################################################################################

# NVGwinding
NVG_CCW = 1
NVG_CW  = 2

# NVGsolidity
NVG_SOLID = 1
NVG_HOLE  = 2

# NVGlineCap
NVG_BUTT   = 0
NVG_ROUND  = 1
NVG_SQUARE = 2
NVG_BEVEL  = 3
NVG_MITER  = 4

# NVGalign
#  Horizontal align
NVG_ALIGN_LEFT     = 1
NVG_ALIGN_CENTER   = 2
NVG_ALIGN_RIGHT    = 4
#  Vertical align
NVG_ALIGN_TOP      = 8
NVG_ALIGN_MIDDLE   = 16
NVG_ALIGN_BOTTOM   = 32
NVG_ALIGN_BASELINE = 64

# NVGblendFactor
NVG_ZERO                = 1 << 0
NVG_ONE                 = 1 << 1
NVG_SRC_COLOR           = 1 << 2
NVG_ONE_MINUS_SRC_COLOR = 1 << 3
NVG_DST_COLOR           = 1 << 4
NVG_ONE_MINUS_DST_COLOR = 1 << 5
NVG_SRC_ALPHA           = 1 << 6
NVG_ONE_MINUS_SRC_ALPHA = 1 << 7
NVG_DST_ALPHA           = 1 << 8
NVG_ONE_MINUS_DST_ALPHA = 1 << 9
NVG_SRC_ALPHA_SATURATE  = 1 << 10

# NVGcompositeOperation
NVG_SOURCE_OVER      = 0
NVG_SOURCE_IN        = 1
NVG_SOURCE_OUT       = 2
NVG_ATOP             = 3
NVG_DESTINATION_OVER = 4
NVG_DESTINATION_IN   = 5
NVG_DESTINATION_OUT  = 6
NVG_DESTINATION_ATOP = 7
NVG_LIGHTER          = 8
NVG_COPY             = 9
NVG_XOR              = 10

# NVGimageFlags
NVG_IMAGE_GENERATE_MIPMAPS  = 1
NVG_IMAGE_REPEATX           = 2
NVG_IMAGE_REPEATY           = 4
NVG_IMAGE_FLIPY             = 8
NVG_IMAGE_PREMULTIPLIED     = 16
NVG_IMAGE_NEAREST           = 32

# NVGcreateFlags
NVG_ANTIALIAS         = 1
NVG_STENCIL_STROKES   = 2
NVG_DEBUG             = 4

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

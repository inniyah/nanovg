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

cdef class _NVGcontext:
    # https://wiki.libsdl.org/SDL_Event
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

def CreateGL3(flags : int):
    cdef c_nanovg.NVGcontext * vg = c_nanovg_gl.nvgCreateGL3(flags)
    return _NVGcontext.create(vg)

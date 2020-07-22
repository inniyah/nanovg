import ctypes
import glew
import sys

try:
    # For OpenGL-ctypes
    from OpenGL import platform
    gl = platform.OpenGL
except (ImportError, AttributeError):
    try:
      # For PyOpenGL
      gl = ctypes.cdll.LoadLibrary('libGL.so')
    except OSError:
        # Load for Mac
        from ctypes.util import find_library
        path = find_library('OpenGL') # finds the absolute path to the framework
        gl = ctypes.cdll.LoadLibrary(path)

from .defs import *

def glewInit():
    """Initialize the glew world.  There must be an existing OpenGL
    context created for this to work correctly.
    Check return value against GLEW_OK."""
    return glew.library.__GLEW_LOADER.glewInit()

def glewGetString(name):
    """glewGetString(enum) -> str
    Primarily used for getting GLEW_VERSION."""
    return glew.library.__GLEW_LOADER.glewGetString(name)

def glewGetErrorString(err):
    """glewGetErrorString(enum) -> str
    Return the error string for the corresponding glew error.
    Typically the error returned by glewInit."""
    return glew.library.__GLEW_LOADER.glewGetErrorString(err)

def glewGetExtension(name):
    """glewGetExtension(ext) -> bool
    Check if extension ext is supported."""
    return glew.library.__GLEW_LOADER.glewGetExtension(name)

def glewIsSupported(name):
    """glewIsSupported(ext) -> bool
    More efficient string query method."""
    return glew.library.__GLEW_LOADER.glewIsSupported(name)

glCreateShaderObjectARB = gl.glCreateShaderObjectARB
glShaderSourceARB = gl.glShaderSourceARB
glShaderSourceARB.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_char_p), ctypes.POINTER(ctypes.c_int)]
glCompileShaderARB = gl.glCompileShaderARB
glGetObjectParameterivARB = gl.glGetObjectParameterivARB
glGetObjectParameterivARB.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
glCreateProgramObjectARB = gl.glCreateProgramObjectARB
glGetInfoLogARB = gl.glGetShaderInfoLog
glGetInfoLogARB.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.c_char_p]
glAttachObjectARB = gl.glAttachObjectARB
glLinkProgramARB = gl.glLinkProgramARB
glDeleteObjectARB = gl.glDeleteObjectARB
glGetError = gl.glGetError
glUseProgramObjectARB = gl.glUseProgramObjectARB

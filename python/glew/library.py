import ctypes

__GLEW_LOADER = None

__GLEW_API_NAMES = []
__GLEW_API_ARGS_MAP = {}
__GLEW_API_RETVAL_MAP = {}

def load_glew_library(lib, output_error = False):

    global __GLEW_LOADER
    __GLEW_LOADER = ctypes.cdll.LoadLibrary(lib)

    __GLEW_API_NAMES.append('glewInit')
    __GLEW_API_ARGS_MAP['glewInit'] = None
    __GLEW_API_RETVAL_MAP['glewInit'] = ctypes.c_int

    __GLEW_API_NAMES.append('glewGetString')
    __GLEW_API_ARGS_MAP['glewGetString'] = [ctypes.c_uint]
    __GLEW_API_RETVAL_MAP['glewGetString'] = ctypes.c_char_p

    __GLEW_API_NAMES.append('glewGetErrorString')
    __GLEW_API_ARGS_MAP['glewGetErrorString'] = [ctypes.c_uint]
    __GLEW_API_RETVAL_MAP['glewGetErrorString'] = ctypes.c_char_p

    __GLEW_API_NAMES.append('glewGetExtension')
    __GLEW_API_ARGS_MAP['glewGetExtension'] = [ctypes.c_char_p]
    __GLEW_API_RETVAL_MAP['glewGetExtension'] = ctypes.c_ubyte

    __GLEW_API_NAMES.append('glewIsSupported')
    __GLEW_API_ARGS_MAP['glewIsSupported'] = [ctypes.c_char_p]
    __GLEW_API_RETVAL_MAP['glewIsSupported'] = ctypes.c_ubyte

    for api in __GLEW_API_NAMES:
        try:
            func_ptr = getattr(__GLEW_LOADER, api) # ctypes _FuncPtr
            func_ptr.argtypes = __GLEW_API_ARGS_MAP[api]
            func_ptr.restype = __GLEW_API_RETVAL_MAP[api]
        except AttributeError:
            if output_error:
                print("Python-GLEW : API {} not found.".format(api))
        finally:
            pass

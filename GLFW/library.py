from ctypes import *

GLFWkeyfun = CFUNCTYPE(None, c_void_p, c_int, c_int, c_int, c_int)

GLFW_PRESS    = 1
GLFW_KEY_ESCAPE         = 256

__GLFW_LOADER = None

__GLFW_API_NAMES = []
__GLFW_API_ARGS_MAP = {}
__GLFW_API_RETVAL_MAP = {}

def load_glfw_library(lib, output_error = False):

    global __GLFW_LOADER
    __GLFW_LOADER = cdll.LoadLibrary(lib)

    # API

    __GLFW_API_NAMES.append('glfwInit')
    __GLFW_API_ARGS_MAP['glfwInit'] = None
    __GLFW_API_RETVAL_MAP['glfwInit'] = c_int

    __GLFW_API_NAMES.append('glfwTerminate')
    __GLFW_API_ARGS_MAP['glfwTerminate'] = None
    __GLFW_API_RETVAL_MAP['glfwTerminate'] = None

    __GLFW_API_NAMES.append('glfwInitHint') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwInitHint'] = [c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwInitHint'] = None

    __GLFW_API_NAMES.append('glfwInitHintString') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwInitHintString'] = [c_int, c_char_p]
    __GLFW_API_RETVAL_MAP['glfwInitHintString'] = None

    __GLFW_API_NAMES.append('glfwGetVersion')
    __GLFW_API_ARGS_MAP['glfwGetVersion'] = [POINTER(c_int), POINTER(c_int), POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetVersion'] = None

    __GLFW_API_NAMES.append('glfwGetVersionString') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetVersionString'] = None
    __GLFW_API_RETVAL_MAP['glfwGetVersionString'] = c_char_p

    __GLFW_API_NAMES.append('glfwGetError')
    __GLFW_API_ARGS_MAP['glfwGetError'] = [POINTER(c_char_p)]
    __GLFW_API_RETVAL_MAP['glfwGetError'] = c_int

    __GLFW_API_NAMES.append('glfwSetErrorCallback')
    __GLFW_API_ARGS_MAP['glfwSetErrorCallback'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetErrorCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwGetMonitors')
    __GLFW_API_ARGS_MAP['glfwGetMonitors'] = [POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetMonitors'] = c_void_p

    __GLFW_API_NAMES.append('glfwGetPrimaryMonitor')
    __GLFW_API_ARGS_MAP['glfwGetPrimaryMonitor'] = None
    __GLFW_API_RETVAL_MAP['glfwGetPrimaryMonitor'] = c_void_p

    __GLFW_API_NAMES.append('glfwGetMonitorPos')
    __GLFW_API_ARGS_MAP['glfwGetMonitorPos'] = [c_void_p, POINTER(c_int), POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetMonitorPos'] = None

    __GLFW_API_NAMES.append('glfwGetMonitorPhysicalSize')
    __GLFW_API_ARGS_MAP['glfwGetMonitorPhysicalSize'] = [c_void_p, POINTER(c_int), POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetMonitorPhysicalSize'] = None

    __GLFW_API_NAMES.append('glfwGetMonitorName')
    __GLFW_API_ARGS_MAP['glfwGetMonitorName'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetMonitorName'] = c_char_p

    __GLFW_API_NAMES.append('glfwSetMonitorCallback')
    __GLFW_API_ARGS_MAP['glfwSetMonitorCallback'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetMonitorCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwGetVideoModes')
    __GLFW_API_ARGS_MAP['glfwGetVideoModes'] = [c_void_p, POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetVideoModes'] = c_void_p

    __GLFW_API_NAMES.append('glfwGetVideoMode')
    __GLFW_API_ARGS_MAP['glfwGetVideoMode'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetVideoMode'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetGamma')
    __GLFW_API_ARGS_MAP['glfwSetGamma'] = [c_void_p, c_float]
    __GLFW_API_RETVAL_MAP['glfwSetGamma'] = None

    __GLFW_API_NAMES.append('glfwGetGammaRamp')
    __GLFW_API_ARGS_MAP['glfwGetGammaRamp'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetGammaRamp'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetGammaRamp')
    __GLFW_API_ARGS_MAP['glfwSetGammaRamp'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetGammaRamp'] = None

    __GLFW_API_NAMES.append('glfwDefaultWindowHints')
    __GLFW_API_ARGS_MAP['glfwDefaultWindowHints'] = None
    __GLFW_API_RETVAL_MAP['glfwDefaultWindowHints'] = None

    __GLFW_API_NAMES.append('glfwWindowHint')
    __GLFW_API_ARGS_MAP['glfwWindowHint'] = [c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwWindowHint'] = None

    __GLFW_API_NAMES.append('glfwCreateWindow')
    __GLFW_API_ARGS_MAP['glfwCreateWindow'] = [c_int, c_int, c_char_p, c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwCreateWindow'] = c_void_p

    __GLFW_API_NAMES.append('glfwDestroyWindow')
    __GLFW_API_ARGS_MAP['glfwDestroyWindow'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwDestroyWindow'] = None

    __GLFW_API_NAMES.append('glfwWindowShouldClose')
    __GLFW_API_ARGS_MAP['glfwWindowShouldClose'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwWindowShouldClose'] = c_int

    __GLFW_API_NAMES.append('glfwSetWindowShouldClose')
    __GLFW_API_ARGS_MAP['glfwSetWindowShouldClose'] = [c_void_p, c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowShouldClose'] = None

    __GLFW_API_NAMES.append('glfwSetWindowTitle')
    __GLFW_API_ARGS_MAP['glfwSetWindowTitle'] = [c_void_p, c_char_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowTitle'] = None

    __GLFW_API_NAMES.append('glfwSetWindowIcon')
    __GLFW_API_ARGS_MAP['glfwSetWindowIcon'] = [c_void_p, c_int, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowIcon'] = None

    __GLFW_API_NAMES.append('glfwGetWindowPos')
    __GLFW_API_ARGS_MAP['glfwGetWindowPos'] = [c_void_p, POINTER(c_int), POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetWindowPos'] = None

    __GLFW_API_NAMES.append('glfwSetWindowPos')
    __GLFW_API_ARGS_MAP['glfwSetWindowPos'] = [c_void_p, c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowPos'] = None

    __GLFW_API_NAMES.append('glfwGetWindowSize')
    __GLFW_API_ARGS_MAP['glfwGetWindowSize'] = [c_void_p, POINTER(c_int), POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetWindowSize'] = None

    __GLFW_API_NAMES.append('glfwSetWindowSizeLimits')
    __GLFW_API_ARGS_MAP['glfwSetWindowSizeLimits'] = [c_void_p, c_int, c_int, c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowSizeLimits'] = None

    __GLFW_API_NAMES.append('glfwSetWindowAspectRatio')
    __GLFW_API_ARGS_MAP['glfwSetWindowAspectRatio'] = [c_void_p, c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowAspectRatio'] = None

    __GLFW_API_NAMES.append('glfwSetWindowSize')
    __GLFW_API_ARGS_MAP['glfwSetWindowSize'] = [c_void_p, c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowSize'] = None

    __GLFW_API_NAMES.append('glfwGetFramebufferSize')
    __GLFW_API_ARGS_MAP['glfwGetFramebufferSize'] = [c_void_p, POINTER(c_int), POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetFramebufferSize'] = None

    __GLFW_API_NAMES.append('glfwGetWindowFrameSize')
    __GLFW_API_ARGS_MAP['glfwGetWindowFrameSize'] = [c_void_p, POINTER(c_int), POINTER(c_int), POINTER(c_int), POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetWindowFrameSize'] = None

    __GLFW_API_NAMES.append('glfwIconifyWindow')
    __GLFW_API_ARGS_MAP['glfwIconifyWindow'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwIconifyWindow'] = None

    __GLFW_API_NAMES.append('glfwRestoreWindow')
    __GLFW_API_ARGS_MAP['glfwRestoreWindow'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwRestoreWindow'] = None

    __GLFW_API_NAMES.append('glfwMaximizeWindow')
    __GLFW_API_ARGS_MAP['glfwMaximizeWindow'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwMaximizeWindow'] = None

    __GLFW_API_NAMES.append('glfwShowWindow')
    __GLFW_API_ARGS_MAP['glfwShowWindow'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwShowWindow'] = None

    __GLFW_API_NAMES.append('glfwHideWindow')
    __GLFW_API_ARGS_MAP['glfwHideWindow'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwHideWindow'] = None

    __GLFW_API_NAMES.append('glfwFocusWindow')
    __GLFW_API_ARGS_MAP['glfwFocusWindow'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwFocusWindow'] = None

    __GLFW_API_NAMES.append('glfwRequestWindowAttention') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwRequestWindowAttention'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwRequestWindowAttention'] = None

    __GLFW_API_NAMES.append('glfwGetWindowMonitor')
    __GLFW_API_ARGS_MAP['glfwGetWindowMonitor'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetWindowMonitor'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowMonitor')
    __GLFW_API_ARGS_MAP['glfwSetWindowMonitor'] = [c_void_p, c_void_p, c_int, c_int, c_int, c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowMonitor'] = None

    __GLFW_API_NAMES.append('glfwGetWindowAttrib')
    __GLFW_API_ARGS_MAP['glfwGetWindowAttrib'] = [c_void_p, c_int]
    __GLFW_API_RETVAL_MAP['glfwGetWindowAttrib'] = c_int

    __GLFW_API_NAMES.append('glfwSetWindowAttrib') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwSetWindowAttrib'] = [c_void_p, c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowAttrib'] = None

    __GLFW_API_NAMES.append('glfwSetWindowUserPointer')
    __GLFW_API_ARGS_MAP['glfwSetWindowUserPointer'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowUserPointer'] = None

    __GLFW_API_NAMES.append('glfwGetWindowUserPointer')
    __GLFW_API_ARGS_MAP['glfwGetWindowUserPointer'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetWindowUserPointer'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowPosCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowPosCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowPosCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowSizeCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowSizeCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowSizeCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowCloseCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowCloseCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowCloseCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowRefreshCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowRefreshCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowRefreshCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowFocusCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowFocusCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowFocusCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowIconifyCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowIconifyCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowIconifyCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowMaximizeCallback') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwSetWindowMaximizeCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowMaximizeCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetFramebufferSizeCallback')
    __GLFW_API_ARGS_MAP['glfwSetFramebufferSizeCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetFramebufferSizeCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwPollEvents')
    __GLFW_API_ARGS_MAP['glfwPollEvents'] = None
    __GLFW_API_RETVAL_MAP['glfwPollEvents'] = None

    __GLFW_API_NAMES.append('glfwWaitEvents')
    __GLFW_API_ARGS_MAP['glfwWaitEvents'] = None
    __GLFW_API_RETVAL_MAP['glfwWaitEvents'] = None

    __GLFW_API_NAMES.append('glfwWaitEventsTimeout')
    __GLFW_API_ARGS_MAP['glfwWaitEventsTimeout'] = [c_double]
    __GLFW_API_RETVAL_MAP['glfwWaitEventsTimeout'] = None

    __GLFW_API_NAMES.append('glfwPostEmptyEvent')
    __GLFW_API_ARGS_MAP['glfwPostEmptyEvent'] = None
    __GLFW_API_RETVAL_MAP['glfwPostEmptyEvent'] = None

    __GLFW_API_NAMES.append('glfwGetInputMode')
    __GLFW_API_ARGS_MAP['glfwGetInputMode'] = [c_void_p, c_int]
    __GLFW_API_RETVAL_MAP['glfwGetInputMode'] = c_int

    __GLFW_API_NAMES.append('glfwSetInputMode')
    __GLFW_API_ARGS_MAP['glfwSetInputMode'] = [c_void_p, c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwSetInputMode'] = None

    __GLFW_API_NAMES.append('glfwGetKeyName')
    __GLFW_API_ARGS_MAP['glfwGetKeyName'] = [c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwGetKeyName'] = c_char_p

    __GLFW_API_NAMES.append('glfwGetKeyScancode') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetKeyScancode'] = [c_int]
    __GLFW_API_RETVAL_MAP['glfwGetKeyScancode'] = c_int

    __GLFW_API_NAMES.append('glfwGetKey')
    __GLFW_API_ARGS_MAP['glfwGetKey'] = [c_void_p, c_int]
    __GLFW_API_RETVAL_MAP['glfwGetKey'] = c_int

    __GLFW_API_NAMES.append('glfwGetMouseButton')
    __GLFW_API_ARGS_MAP['glfwGetMouseButton'] = [c_void_p, c_int]
    __GLFW_API_RETVAL_MAP['glfwGetMouseButton'] = c_int

    __GLFW_API_NAMES.append('glfwGetCursorPos')
    __GLFW_API_ARGS_MAP['glfwGetCursorPos'] = [c_void_p, POINTER(c_double), POINTER(c_double)]
    __GLFW_API_RETVAL_MAP['glfwGetCursorPos'] = None

    __GLFW_API_NAMES.append('glfwSetCursorPos')
    __GLFW_API_ARGS_MAP['glfwSetCursorPos'] = [c_void_p, c_double, c_double]
    __GLFW_API_RETVAL_MAP['glfwSetCursorPos'] = None

    __GLFW_API_NAMES.append('glfwCreateCursor')
    __GLFW_API_ARGS_MAP['glfwCreateCursor'] = [c_void_p, c_int, c_int]
    __GLFW_API_RETVAL_MAP['glfwCreateCursor'] = c_void_p

    __GLFW_API_NAMES.append('glfwCreateStandardCursor')
    __GLFW_API_ARGS_MAP['glfwCreateStandardCursor'] = [c_int]
    __GLFW_API_RETVAL_MAP['glfwCreateStandardCursor'] = c_void_p

    __GLFW_API_NAMES.append('glfwDestroyCursor')
    __GLFW_API_ARGS_MAP['glfwDestroyCursor'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwDestroyCursor'] = None

    __GLFW_API_NAMES.append('glfwSetCursor')
    __GLFW_API_ARGS_MAP['glfwSetCursor'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetCursor'] = None

    __GLFW_API_NAMES.append('glfwSetKeyCallback')
    __GLFW_API_ARGS_MAP['glfwSetKeyCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetKeyCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetCharCallback')
    __GLFW_API_ARGS_MAP['glfwSetCharCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetCharCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetCharModsCallback')
    __GLFW_API_ARGS_MAP['glfwSetCharModsCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetCharModsCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetMouseButtonCallback')
    __GLFW_API_ARGS_MAP['glfwSetMouseButtonCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetMouseButtonCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetCursorPosCallback')
    __GLFW_API_ARGS_MAP['glfwSetCursorPosCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetCursorPosCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetCursorEnterCallback')
    __GLFW_API_ARGS_MAP['glfwSetCursorEnterCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetCursorEnterCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetScrollCallback')
    __GLFW_API_ARGS_MAP['glfwSetScrollCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetScrollCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwSetDropCallback')
    __GLFW_API_ARGS_MAP['glfwSetDropCallback'] = [c_void_p, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetDropCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwJoystickPresent')
    __GLFW_API_ARGS_MAP['glfwJoystickPresent'] = [c_int]
    __GLFW_API_RETVAL_MAP['glfwJoystickPresent'] = c_int

    __GLFW_API_NAMES.append('glfwGetJoystickAxes')
    __GLFW_API_ARGS_MAP['glfwGetJoystickAxes'] = [c_int, POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetJoystickAxes'] = POINTER(c_float)

    __GLFW_API_NAMES.append('glfwGetJoystickButtons')
    __GLFW_API_ARGS_MAP['glfwGetJoystickButtons'] = [c_int, POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetJoystickButtons'] = POINTER(c_ubyte)

    __GLFW_API_NAMES.append('glfwGetJoystickHats') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetJoystickHats'] = [c_int, POINTER(c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetJoystickHats'] = POINTER(c_ubyte)

    __GLFW_API_NAMES.append('glfwGetJoystickName')
    __GLFW_API_ARGS_MAP['glfwGetJoystickName'] = [c_int]
    __GLFW_API_RETVAL_MAP['glfwGetJoystickName'] = c_char_p

    __GLFW_API_NAMES.append('glfwGetJoystickGUID') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetJoystickGUID'] = [c_int]
    __GLFW_API_RETVAL_MAP['glfwGetJoystickGUID'] = c_char_p

    __GLFW_API_NAMES.append('glfwJoystickIsGamepad') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwJoystickIsGamepad'] = [c_int]
    __GLFW_API_RETVAL_MAP['glfwJoystickIsGamepad'] = c_int

    __GLFW_API_NAMES.append('glfwSetJoystickCallback')
    __GLFW_API_ARGS_MAP['glfwSetJoystickCallback'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetJoystickCallback'] = c_void_p

    __GLFW_API_NAMES.append('glfwUpdateGamepadMappings') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwUpdateGamepadMappings'] = [c_char_p]
    __GLFW_API_RETVAL_MAP['glfwUpdateGamepadMappings'] = c_int

    __GLFW_API_NAMES.append('glfwGetGamepadName') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetGamepadName'] = [c_int]
    __GLFW_API_RETVAL_MAP['glfwGetGamepadName'] = c_char_p

    __GLFW_API_NAMES.append('glfwGetGamepadState') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetGamepadState'] = [c_int, c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetGamepadState'] = c_int

    __GLFW_API_NAMES.append('glfwSetClipboardString')
    __GLFW_API_ARGS_MAP['glfwSetClipboardString'] = [c_void_p, c_char_p]
    __GLFW_API_RETVAL_MAP['glfwSetClipboardString'] = None

    __GLFW_API_NAMES.append('glfwGetClipboardString')
    __GLFW_API_ARGS_MAP['glfwGetClipboardString'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetClipboardString'] = c_char_p

    __GLFW_API_NAMES.append('glfwGetTime')
    __GLFW_API_ARGS_MAP['glfwGetTime'] = None
    __GLFW_API_RETVAL_MAP['glfwGetTime'] = c_double

    __GLFW_API_NAMES.append('glfwSetTime')
    __GLFW_API_ARGS_MAP['glfwSetTime'] = [c_double]
    __GLFW_API_RETVAL_MAP['glfwSetTime'] = None

    __GLFW_API_NAMES.append('glfwGetTimerValue')
    __GLFW_API_ARGS_MAP['glfwGetTimerValue'] = None
    __GLFW_API_RETVAL_MAP['glfwGetTimerValue'] = c_uint64

    __GLFW_API_NAMES.append('glfwGetTimerFrequency')
    __GLFW_API_ARGS_MAP['glfwGetTimerFrequency'] = None
    __GLFW_API_RETVAL_MAP['glfwGetTimerFrequency'] = c_uint64

    __GLFW_API_NAMES.append('glfwMakeContextCurrent')
    __GLFW_API_ARGS_MAP['glfwMakeContextCurrent'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwMakeContextCurrent'] = None

    __GLFW_API_NAMES.append('glfwGetCurrentContext')
    __GLFW_API_ARGS_MAP['glfwGetCurrentContext'] = None
    __GLFW_API_RETVAL_MAP['glfwGetCurrentContext'] = c_void_p

    __GLFW_API_NAMES.append('glfwSwapBuffers')
    __GLFW_API_ARGS_MAP['glfwSwapBuffers'] = [c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSwapBuffers'] = None

    __GLFW_API_NAMES.append('glfwSwapInterval')
    __GLFW_API_ARGS_MAP['glfwSwapInterval'] = [c_int]
    __GLFW_API_RETVAL_MAP['glfwSwapInterval'] = None

    __GLFW_API_NAMES.append('glfwExtensionSupported')
    __GLFW_API_ARGS_MAP['glfwExtensionSupported'] = [c_char_p]
    __GLFW_API_RETVAL_MAP['glfwExtensionSupported'] = c_int

    __GLFW_API_NAMES.append('glfwGetProcAddress')
    __GLFW_API_ARGS_MAP['glfwGetProcAddress'] = [c_char_p]
    __GLFW_API_RETVAL_MAP['glfwGetProcAddress'] = c_void_p

    __GLFW_API_NAMES.append('glfwVulkanSupported')
    __GLFW_API_ARGS_MAP['glfwVulkanSupported'] = None
    __GLFW_API_RETVAL_MAP['glfwVulkanSupported'] = c_int

    __GLFW_API_NAMES.append('glfwGetRequiredInstanceExtensions')
    __GLFW_API_ARGS_MAP['glfwGetRequiredInstanceExtensions'] = [POINTER(c_uint32)]
    __GLFW_API_RETVAL_MAP['glfwGetRequiredInstanceExtensions'] = POINTER(c_char_p)

    for api in __GLFW_API_NAMES:
        try:
            func_ptr = getattr(__GLFW_LOADER, api) # ctypes _FuncPtr
            func_ptr.argtypes = __GLFW_API_ARGS_MAP[api]
            func_ptr.restype = __GLFW_API_RETVAL_MAP[api]
        except AttributeError:
            if output_error:
                print("Python-GLFW : API {} not found.".format(api))
        finally:
            pass

# Python-GLFW : Yet another GLFW wrapper for Python
# Copyright (c) 2017 vaiorabbit <http://twitter.com/vaiorabbit>
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

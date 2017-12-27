import ctypes

__GLFW_LOADER = None

__GLFW_API_NAMES = []
__GLFW_API_ARGS_MAP = {}
__GLFW_API_RETVAL_MAP = {}

def load_glfw_library(lib, output_error = False):

    global __GLFW_LOADER
    __GLFW_LOADER = ctypes.cdll.LoadLibrary(lib)

    # API

    __GLFW_API_NAMES.append('glfwInit')
    __GLFW_API_ARGS_MAP['glfwInit'] = None
    __GLFW_API_RETVAL_MAP['glfwInit'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwTerminate')
    __GLFW_API_ARGS_MAP['glfwTerminate'] = None
    __GLFW_API_RETVAL_MAP['glfwTerminate'] = None

    __GLFW_API_NAMES.append('glfwInitHint') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwInitHint'] = [ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwInitHint'] = None

    __GLFW_API_NAMES.append('glfwInitHintString') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwInitHintString'] = [ctypes.c_int, ctypes.c_char_p]
    __GLFW_API_RETVAL_MAP['glfwInitHintString'] = None

    __GLFW_API_NAMES.append('glfwGetVersion')
    __GLFW_API_ARGS_MAP['glfwGetVersion'] = [ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetVersion'] = None

    __GLFW_API_NAMES.append('glfwGetVersionString') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetVersionString'] = None
    __GLFW_API_RETVAL_MAP['glfwGetVersionString'] = ctypes.c_char_p

    __GLFW_API_NAMES.append('glfwGetError')
    __GLFW_API_ARGS_MAP['glfwGetError'] = [ctypes.POINTER(ctypes.c_char_p)]
    __GLFW_API_RETVAL_MAP['glfwGetError'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwSetErrorCallback')
    __GLFW_API_ARGS_MAP['glfwSetErrorCallback'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetErrorCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwGetMonitors')
    __GLFW_API_ARGS_MAP['glfwGetMonitors'] = [ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetMonitors'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwGetPrimaryMonitor')
    __GLFW_API_ARGS_MAP['glfwGetPrimaryMonitor'] = None
    __GLFW_API_RETVAL_MAP['glfwGetPrimaryMonitor'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwGetMonitorPos')
    __GLFW_API_ARGS_MAP['glfwGetMonitorPos'] = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetMonitorPos'] = None

    __GLFW_API_NAMES.append('glfwGetMonitorPhysicalSize')
    __GLFW_API_ARGS_MAP['glfwGetMonitorPhysicalSize'] = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetMonitorPhysicalSize'] = None

    __GLFW_API_NAMES.append('glfwGetMonitorName')
    __GLFW_API_ARGS_MAP['glfwGetMonitorName'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetMonitorName'] = ctypes.c_char_p

    __GLFW_API_NAMES.append('glfwSetMonitorCallback')
    __GLFW_API_ARGS_MAP['glfwSetMonitorCallback'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetMonitorCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwGetVideoModes')
    __GLFW_API_ARGS_MAP['glfwGetVideoModes'] = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetVideoModes'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwGetVideoMode')
    __GLFW_API_ARGS_MAP['glfwGetVideoMode'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetVideoMode'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetGamma')
    __GLFW_API_ARGS_MAP['glfwSetGamma'] = [ctypes.c_void_p, ctypes.c_float]
    __GLFW_API_RETVAL_MAP['glfwSetGamma'] = None

    __GLFW_API_NAMES.append('glfwGetGammaRamp')
    __GLFW_API_ARGS_MAP['glfwGetGammaRamp'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetGammaRamp'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetGammaRamp')
    __GLFW_API_ARGS_MAP['glfwSetGammaRamp'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetGammaRamp'] = None

    __GLFW_API_NAMES.append('glfwDefaultWindowHints')
    __GLFW_API_ARGS_MAP['glfwDefaultWindowHints'] = None
    __GLFW_API_RETVAL_MAP['glfwDefaultWindowHints'] = None

    __GLFW_API_NAMES.append('glfwWindowHint')
    __GLFW_API_ARGS_MAP['glfwWindowHint'] = [ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwWindowHint'] = None

    __GLFW_API_NAMES.append('glfwCreateWindow')
    __GLFW_API_ARGS_MAP['glfwCreateWindow'] = [ctypes.c_int, ctypes.c_int, ctypes.c_char_p, ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwCreateWindow'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwDestroyWindow')
    __GLFW_API_ARGS_MAP['glfwDestroyWindow'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwDestroyWindow'] = None

    __GLFW_API_NAMES.append('glfwWindowShouldClose')
    __GLFW_API_ARGS_MAP['glfwWindowShouldClose'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwWindowShouldClose'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwSetWindowShouldClose')
    __GLFW_API_ARGS_MAP['glfwSetWindowShouldClose'] = [ctypes.c_void_p, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowShouldClose'] = None

    __GLFW_API_NAMES.append('glfwSetWindowTitle')
    __GLFW_API_ARGS_MAP['glfwSetWindowTitle'] = [ctypes.c_void_p, ctypes.c_char_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowTitle'] = None

    __GLFW_API_NAMES.append('glfwSetWindowIcon')
    __GLFW_API_ARGS_MAP['glfwSetWindowIcon'] = [ctypes.c_void_p, ctypes.c_int, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowIcon'] = None

    __GLFW_API_NAMES.append('glfwGetWindowPos')
    __GLFW_API_ARGS_MAP['glfwGetWindowPos'] = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetWindowPos'] = None

    __GLFW_API_NAMES.append('glfwSetWindowPos')
    __GLFW_API_ARGS_MAP['glfwSetWindowPos'] = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowPos'] = None

    __GLFW_API_NAMES.append('glfwGetWindowSize')
    __GLFW_API_ARGS_MAP['glfwGetWindowSize'] = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetWindowSize'] = None

    __GLFW_API_NAMES.append('glfwSetWindowSizeLimits')
    __GLFW_API_ARGS_MAP['glfwSetWindowSizeLimits'] = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowSizeLimits'] = None

    __GLFW_API_NAMES.append('glfwSetWindowAspectRatio')
    __GLFW_API_ARGS_MAP['glfwSetWindowAspectRatio'] = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowAspectRatio'] = None

    __GLFW_API_NAMES.append('glfwSetWindowSize')
    __GLFW_API_ARGS_MAP['glfwSetWindowSize'] = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowSize'] = None

    __GLFW_API_NAMES.append('glfwGetFramebufferSize')
    __GLFW_API_ARGS_MAP['glfwGetFramebufferSize'] = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetFramebufferSize'] = None

    __GLFW_API_NAMES.append('glfwGetWindowFrameSize')
    __GLFW_API_ARGS_MAP['glfwGetWindowFrameSize'] = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetWindowFrameSize'] = None

    __GLFW_API_NAMES.append('glfwIconifyWindow')
    __GLFW_API_ARGS_MAP['glfwIconifyWindow'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwIconifyWindow'] = None

    __GLFW_API_NAMES.append('glfwRestoreWindow')
    __GLFW_API_ARGS_MAP['glfwRestoreWindow'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwRestoreWindow'] = None

    __GLFW_API_NAMES.append('glfwMaximizeWindow')
    __GLFW_API_ARGS_MAP['glfwMaximizeWindow'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwMaximizeWindow'] = None

    __GLFW_API_NAMES.append('glfwShowWindow')
    __GLFW_API_ARGS_MAP['glfwShowWindow'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwShowWindow'] = None

    __GLFW_API_NAMES.append('glfwHideWindow')
    __GLFW_API_ARGS_MAP['glfwHideWindow'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwHideWindow'] = None

    __GLFW_API_NAMES.append('glfwFocusWindow')
    __GLFW_API_ARGS_MAP['glfwFocusWindow'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwFocusWindow'] = None

    __GLFW_API_NAMES.append('glfwRequestWindowAttention') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwRequestWindowAttention'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwRequestWindowAttention'] = None

    __GLFW_API_NAMES.append('glfwGetWindowMonitor')
    __GLFW_API_ARGS_MAP['glfwGetWindowMonitor'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetWindowMonitor'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowMonitor')
    __GLFW_API_ARGS_MAP['glfwSetWindowMonitor'] = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowMonitor'] = None

    __GLFW_API_NAMES.append('glfwGetWindowAttrib')
    __GLFW_API_ARGS_MAP['glfwGetWindowAttrib'] = [ctypes.c_void_p, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwGetWindowAttrib'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwSetWindowAttrib') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwSetWindowAttrib'] = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwSetWindowAttrib'] = None

    __GLFW_API_NAMES.append('glfwSetWindowUserPointer')
    __GLFW_API_ARGS_MAP['glfwSetWindowUserPointer'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowUserPointer'] = None

    __GLFW_API_NAMES.append('glfwGetWindowUserPointer')
    __GLFW_API_ARGS_MAP['glfwGetWindowUserPointer'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetWindowUserPointer'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowPosCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowPosCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowPosCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowSizeCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowSizeCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowSizeCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowCloseCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowCloseCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowCloseCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowRefreshCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowRefreshCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowRefreshCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowFocusCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowFocusCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowFocusCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowIconifyCallback')
    __GLFW_API_ARGS_MAP['glfwSetWindowIconifyCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowIconifyCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetWindowMaximizeCallback') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwSetWindowMaximizeCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetWindowMaximizeCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetFramebufferSizeCallback')
    __GLFW_API_ARGS_MAP['glfwSetFramebufferSizeCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetFramebufferSizeCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwPollEvents')
    __GLFW_API_ARGS_MAP['glfwPollEvents'] = None
    __GLFW_API_RETVAL_MAP['glfwPollEvents'] = None

    __GLFW_API_NAMES.append('glfwWaitEvents')
    __GLFW_API_ARGS_MAP['glfwWaitEvents'] = None
    __GLFW_API_RETVAL_MAP['glfwWaitEvents'] = None

    __GLFW_API_NAMES.append('glfwWaitEventsTimeout')
    __GLFW_API_ARGS_MAP['glfwWaitEventsTimeout'] = [ctypes.c_double]
    __GLFW_API_RETVAL_MAP['glfwWaitEventsTimeout'] = None

    __GLFW_API_NAMES.append('glfwPostEmptyEvent')
    __GLFW_API_ARGS_MAP['glfwPostEmptyEvent'] = None
    __GLFW_API_RETVAL_MAP['glfwPostEmptyEvent'] = None

    __GLFW_API_NAMES.append('glfwGetInputMode')
    __GLFW_API_ARGS_MAP['glfwGetInputMode'] = [ctypes.c_void_p, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwGetInputMode'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwSetInputMode')
    __GLFW_API_ARGS_MAP['glfwSetInputMode'] = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwSetInputMode'] = None

    __GLFW_API_NAMES.append('glfwGetKeyName')
    __GLFW_API_ARGS_MAP['glfwGetKeyName'] = [ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwGetKeyName'] = ctypes.c_char_p

    __GLFW_API_NAMES.append('glfwGetKeyScancode') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetKeyScancode'] = [ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwGetKeyScancode'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwGetKey')
    __GLFW_API_ARGS_MAP['glfwGetKey'] = [ctypes.c_void_p, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwGetKey'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwGetMouseButton')
    __GLFW_API_ARGS_MAP['glfwGetMouseButton'] = [ctypes.c_void_p, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwGetMouseButton'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwGetCursorPos')
    __GLFW_API_ARGS_MAP['glfwGetCursorPos'] = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
    __GLFW_API_RETVAL_MAP['glfwGetCursorPos'] = None

    __GLFW_API_NAMES.append('glfwSetCursorPos')
    __GLFW_API_ARGS_MAP['glfwSetCursorPos'] = [ctypes.c_void_p, ctypes.c_double, ctypes.c_double]
    __GLFW_API_RETVAL_MAP['glfwSetCursorPos'] = None

    __GLFW_API_NAMES.append('glfwCreateCursor')
    __GLFW_API_ARGS_MAP['glfwCreateCursor'] = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwCreateCursor'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwCreateStandardCursor')
    __GLFW_API_ARGS_MAP['glfwCreateStandardCursor'] = [ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwCreateStandardCursor'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwDestroyCursor')
    __GLFW_API_ARGS_MAP['glfwDestroyCursor'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwDestroyCursor'] = None

    __GLFW_API_NAMES.append('glfwSetCursor')
    __GLFW_API_ARGS_MAP['glfwSetCursor'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetCursor'] = None

    __GLFW_API_NAMES.append('glfwSetKeyCallback')
    __GLFW_API_ARGS_MAP['glfwSetKeyCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetKeyCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetCharCallback')
    __GLFW_API_ARGS_MAP['glfwSetCharCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetCharCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetCharModsCallback')
    __GLFW_API_ARGS_MAP['glfwSetCharModsCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetCharModsCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetMouseButtonCallback')
    __GLFW_API_ARGS_MAP['glfwSetMouseButtonCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetMouseButtonCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetCursorPosCallback')
    __GLFW_API_ARGS_MAP['glfwSetCursorPosCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetCursorPosCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetCursorEnterCallback')
    __GLFW_API_ARGS_MAP['glfwSetCursorEnterCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetCursorEnterCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetScrollCallback')
    __GLFW_API_ARGS_MAP['glfwSetScrollCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetScrollCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSetDropCallback')
    __GLFW_API_ARGS_MAP['glfwSetDropCallback'] = [ctypes.c_void_p, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetDropCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwJoystickPresent')
    __GLFW_API_ARGS_MAP['glfwJoystickPresent'] = [ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwJoystickPresent'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwGetJoystickAxes')
    __GLFW_API_ARGS_MAP['glfwGetJoystickAxes'] = [ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetJoystickAxes'] = ctypes.POINTER(ctypes.c_float)

    __GLFW_API_NAMES.append('glfwGetJoystickButtons')
    __GLFW_API_ARGS_MAP['glfwGetJoystickButtons'] = [ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetJoystickButtons'] = ctypes.POINTER(ctypes.c_ubyte)

    __GLFW_API_NAMES.append('glfwGetJoystickHats') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetJoystickHats'] = [ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
    __GLFW_API_RETVAL_MAP['glfwGetJoystickHats'] = ctypes.POINTER(ctypes.c_ubyte)

    __GLFW_API_NAMES.append('glfwGetJoystickName')
    __GLFW_API_ARGS_MAP['glfwGetJoystickName'] = [ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwGetJoystickName'] = ctypes.c_char_p

    __GLFW_API_NAMES.append('glfwGetJoystickGUID') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetJoystickGUID'] = [ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwGetJoystickGUID'] = ctypes.c_char_p

    __GLFW_API_NAMES.append('glfwJoystickIsGamepad') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwJoystickIsGamepad'] = [ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwJoystickIsGamepad'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwSetJoystickCallback')
    __GLFW_API_ARGS_MAP['glfwSetJoystickCallback'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSetJoystickCallback'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwUpdateGamepadMappings') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwUpdateGamepadMappings'] = [ctypes.c_char_p]
    __GLFW_API_RETVAL_MAP['glfwUpdateGamepadMappings'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwGetGamepadName') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetGamepadName'] = [ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwGetGamepadName'] = ctypes.c_char_p

    __GLFW_API_NAMES.append('glfwGetGamepadState') # Available since GLFW 3.3
    __GLFW_API_ARGS_MAP['glfwGetGamepadState'] = [ctypes.c_int, ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetGamepadState'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwSetClipboardString')
    __GLFW_API_ARGS_MAP['glfwSetClipboardString'] = [ctypes.c_void_p, ctypes.c_char_p]
    __GLFW_API_RETVAL_MAP['glfwSetClipboardString'] = None

    __GLFW_API_NAMES.append('glfwGetClipboardString')
    __GLFW_API_ARGS_MAP['glfwGetClipboardString'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwGetClipboardString'] = ctypes.c_char_p

    __GLFW_API_NAMES.append('glfwGetTime')
    __GLFW_API_ARGS_MAP['glfwGetTime'] = None
    __GLFW_API_RETVAL_MAP['glfwGetTime'] = ctypes.c_double

    __GLFW_API_NAMES.append('glfwSetTime')
    __GLFW_API_ARGS_MAP['glfwSetTime'] = [ctypes.c_double]
    __GLFW_API_RETVAL_MAP['glfwSetTime'] = None

    __GLFW_API_NAMES.append('glfwGetTimerValue')
    __GLFW_API_ARGS_MAP['glfwGetTimerValue'] = None
    __GLFW_API_RETVAL_MAP['glfwGetTimerValue'] = ctypes.c_uint64

    __GLFW_API_NAMES.append('glfwGetTimerFrequency')
    __GLFW_API_ARGS_MAP['glfwGetTimerFrequency'] = None
    __GLFW_API_RETVAL_MAP['glfwGetTimerFrequency'] = ctypes.c_uint64

    __GLFW_API_NAMES.append('glfwMakeContextCurrent')
    __GLFW_API_ARGS_MAP['glfwMakeContextCurrent'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwMakeContextCurrent'] = None

    __GLFW_API_NAMES.append('glfwGetCurrentContext')
    __GLFW_API_ARGS_MAP['glfwGetCurrentContext'] = None
    __GLFW_API_RETVAL_MAP['glfwGetCurrentContext'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwSwapBuffers')
    __GLFW_API_ARGS_MAP['glfwSwapBuffers'] = [ctypes.c_void_p]
    __GLFW_API_RETVAL_MAP['glfwSwapBuffers'] = None

    __GLFW_API_NAMES.append('glfwSwapInterval')
    __GLFW_API_ARGS_MAP['glfwSwapInterval'] = [ctypes.c_int]
    __GLFW_API_RETVAL_MAP['glfwSwapInterval'] = None

    __GLFW_API_NAMES.append('glfwExtensionSupported')
    __GLFW_API_ARGS_MAP['glfwExtensionSupported'] = [ctypes.c_char_p]
    __GLFW_API_RETVAL_MAP['glfwExtensionSupported'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwGetProcAddress')
    __GLFW_API_ARGS_MAP['glfwGetProcAddress'] = [ctypes.c_char_p]
    __GLFW_API_RETVAL_MAP['glfwGetProcAddress'] = ctypes.c_void_p

    __GLFW_API_NAMES.append('glfwVulkanSupported')
    __GLFW_API_ARGS_MAP['glfwVulkanSupported'] = None
    __GLFW_API_RETVAL_MAP['glfwVulkanSupported'] = ctypes.c_int

    __GLFW_API_NAMES.append('glfwGetRequiredInstanceExtensions')
    __GLFW_API_ARGS_MAP['glfwGetRequiredInstanceExtensions'] = [ctypes.POINTER(ctypes.c_uint32)]
    __GLFW_API_RETVAL_MAP['glfwGetRequiredInstanceExtensions'] = ctypes.POINTER(ctypes.c_char_p)

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

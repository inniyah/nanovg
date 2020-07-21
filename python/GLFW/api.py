import ctypes
import GLFW

def glfwInit():
    return GLFW.library.__GLFW_LOADER.glfwInit()

def glfwTerminate():
    return GLFW.library.__GLFW_LOADER.glfwTerminate()

def glfwInitHint(hint, value):
    return GLFW.library.__GLFW_LOADER.glfwInitHint(hint, value)

def glfwGetVersion(major, minor, rev):
    return GLFW.library.__GLFW_LOADER.glfwGetVersion(major, minor, rev)

def glfwGetVersionString():
    return GLFW.library.__GLFW_LOADER.glfwGetVersionString()

def glfwGetError(description):
    return GLFW.library.__GLFW_LOADER.glfwGetError(description)

def glfwSetErrorCallback(cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetErrorCallback(cbfun)

def glfwGetMonitors(count):
    return GLFW.library.__GLFW_LOADER.glfwGetMonitors(count)

def glfwGetPrimaryMonitor():
    return GLFW.library.__GLFW_LOADER.glfwGetPrimaryMonitor()

def glfwGetMonitorPos(monitor, xpos, ypos):
    return GLFW.library.__GLFW_LOADER.glfwGetMonitorPos(monitor, xpos, ypos)

def glfwGetMonitorPhysicalSize(monitor, widthMM, heightMM):
    return GLFW.library.__GLFW_LOADER.glfwGetMonitorPhysicalSize(monitor, widthMM, heightMM)

def glfwGetMonitorContentScale(monitor, xscale, yscale):
    return GLFW.library.__GLFW_LOADER.glfwGetMonitorContentScale(monitor, xscale, yscale)

def glfwGetMonitorName(monitor):
    return GLFW.library.__GLFW_LOADER.glfwGetMonitorName(monitor)

def glfwSetMonitorUserPointer(monitor, pointer):
    return GLFW.library.__GLFW_LOADER.glfwSetMonitorUserPointer(monitor, pointer)

def glfwGetMonitorUserPointer(monitor):
    return GLFW.library.__GLFW_LOADER.glfwGetMonitorUserPointer(monitor)

def glfwSetMonitorCallback(cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetMonitorCallback(cbfun)

def glfwGetVideoModes(monitor, count):
    return GLFW.library.__GLFW_LOADER.glfwGetVideoModes(monitor, count)

def glfwGetVideoMode(monitor):
    return GLFW.library.__GLFW_LOADER.glfwGetVideoMode(monitor)

def glfwSetGamma(monitor, gamma):
    return GLFW.library.__GLFW_LOADER.glfwSetGamma(monitor, gamma)

def glfwGetGammaRamp(monitor):
    return GLFW.library.__GLFW_LOADER.glfwGetGammaRamp(monitor)

def glfwSetGammaRamp(monitor, ramp):
    return GLFW.library.__GLFW_LOADER.glfwSetGammaRamp(monitor, ramp)

def glfwDefaultWindowHints():
    return GLFW.library.__GLFW_LOADER.glfwDefaultWindowHints()

def glfwWindowHint(hint, value):
    return GLFW.library.__GLFW_LOADER.glfwWindowHint(hint, value)

def glfwWindowHintString(hint, value):
    return GLFW.library.__GLFW_LOADER.glfwWindowHintString(hint, value)

def glfwCreateWindow(width, height, title, monitor, share):
    return GLFW.library.__GLFW_LOADER.glfwCreateWindow(width, height, title, monitor, share)

def glfwDestroyWindow(window):
    return GLFW.library.__GLFW_LOADER.glfwDestroyWindow(window)

def glfwWindowShouldClose(window):
    return GLFW.library.__GLFW_LOADER.glfwWindowShouldClose(window)

def glfwSetWindowShouldClose(window, value):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowShouldClose(window, value)

def glfwSetWindowTitle(window, title):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowTitle(window, title)

def glfwSetWindowIcon(window, count, images):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowIcon(window, count, images)

def glfwGetWindowPos(window, xpos, ypos):
    return GLFW.library.__GLFW_LOADER.glfwGetWindowPos(window, xpos, ypos)

def glfwSetWindowPos(window, xpos, ypos):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowPos(window, xpos, ypos)

def glfwGetWindowSize(window, width, height):
    return GLFW.library.__GLFW_LOADER.glfwGetWindowSize(window, width, height)

def glfwSetWindowSizeLimits(window, minwidth, minheight, maxwidth, maxheight):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowSizeLimits(window, minwidth, minheight, maxwidth, maxheight)

def glfwSetWindowAspectRatio(window, numer, denom):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowAspectRatio(window, numer, denom)

def glfwSetWindowSize(window, width, height):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowSize(window, width, height)

def glfwGetFramebufferSize(window, width, height):
    return GLFW.library.__GLFW_LOADER.glfwGetFramebufferSize(window, width, height)

def glfwGetWindowFrameSize(window, left, top, right, bottom):
    return GLFW.library.__GLFW_LOADER.glfwGetWindowFrameSize(window, left, top, right, bottom)

def glfwGetWindowContentScale(window, xscale, yscale):
    return GLFW.library.__GLFW_LOADER.glfwGetWindowContentScale(window, xscale, yscale)

def glfwGetWindowOpacity(window):
    return GLFW.library.__GLFW_LOADER.glfwGetWindowOpacity(window)

def glfwSetWindowOpacity(window, opacity):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowOpacity(window, opacity)

def glfwIconifyWindow(window):
    return GLFW.library.__GLFW_LOADER.glfwIconifyWindow(window)

def glfwRestoreWindow(window):
    return GLFW.library.__GLFW_LOADER.glfwRestoreWindow(window)

def glfwMaximizeWindow(window):
    return GLFW.library.__GLFW_LOADER.glfwMaximizeWindow(window)

def glfwShowWindow(window):
    return GLFW.library.__GLFW_LOADER.glfwShowWindow(window)

def glfwHideWindow(window):
    return GLFW.library.__GLFW_LOADER.glfwHideWindow(window)

def glfwFocusWindow(window):
    return GLFW.library.__GLFW_LOADER.glfwFocusWindow(window)

def glfwRequestWindowAttention(window):
    return GLFW.library.__GLFW_LOADER.glfwRequestWindowAttention(window)

def glfwGetWindowMonitor(window):
    return GLFW.library.__GLFW_LOADER.glfwGetWindowMonitor(window)

def glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate)

def glfwGetWindowAttrib(window, attrib):
    return GLFW.library.__GLFW_LOADER.glfwGetWindowAttrib(window, attrib)

def glfwSetWindowAttrib(window, attrib, value):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowAttrib(window, attrib, value)

def glfwSetWindowUserPointer(window, pointer):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowUserPointer(window, pointer)

def glfwGetWindowUserPointer(window):
    return GLFW.library.__GLFW_LOADER.glfwGetWindowUserPointer(window)

def glfwSetWindowPosCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowPosCallback(window, cbfun)

def glfwSetWindowSizeCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowSizeCallback(window, cbfun)

def glfwSetWindowCloseCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowCloseCallback(window, cbfun)

def glfwSetWindowRefreshCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowRefreshCallback(window, cbfun)

def glfwSetWindowFocusCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowFocusCallback(window, cbfun)

def glfwSetWindowIconifyCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowIconifyCallback(window, cbfun)

def glfwSetWindowMaximizeCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowMaximizeCallback(window, cbfun)

def glfwSetFramebufferSizeCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetFramebufferSizeCallback(window, cbfun)

def glfwSetWindowContentScaleCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetWindowContentScaleCallback(window, cbfun)

def glfwPollEvents():
    return GLFW.library.__GLFW_LOADER.glfwPollEvents()

def glfwWaitEvents():
    return GLFW.library.__GLFW_LOADER.glfwWaitEvents()

def glfwWaitEventsTimeout(timeout):
    return GLFW.library.__GLFW_LOADER.glfwWaitEventsTimeout(timeout)

def glfwPostEmptyEvent():
    return GLFW.library.__GLFW_LOADER.glfwPostEmptyEvent()

def glfwGetInputMode(window, mode):
    return GLFW.library.__GLFW_LOADER.glfwGetInputMode(window, mode)

def glfwSetInputMode(window, mode, value):
    return GLFW.library.__GLFW_LOADER.glfwSetInputMode(window, mode, value)

def glfwRawMouseMotionSupported():
    return GLFW.library.__GLFW_LOADER.glfwRawMouseMotionSupported()

def glfwGetKeyName(key, scancode):
    return GLFW.library.__GLFW_LOADER.glfwGetKeyName(key, scancode)

def glfwGetKeyScancode(key):
    return GLFW.library.__GLFW_LOADER.glfwGetKeyScancode(key)

def glfwGetKey(window, key):
    return GLFW.library.__GLFW_LOADER.glfwGetKey(window, key)

def glfwGetMouseButton(window, button):
    return GLFW.library.__GLFW_LOADER.glfwGetMouseButton(window, button)

def glfwGetCursorPos(window, xpos, ypos):
    return GLFW.library.__GLFW_LOADER.glfwGetCursorPos(window, xpos, ypos)

def glfwSetCursorPos(window, xpos, ypos):
    return GLFW.library.__GLFW_LOADER.glfwSetCursorPos(window, xpos, ypos)

def glfwCreateCursor(image, xhot, yhot):
    return GLFW.library.__GLFW_LOADER.glfwCreateCursor(image, xhot, yhot)

def glfwCreateStandardCursor(shape):
    return GLFW.library.__GLFW_LOADER.glfwCreateStandardCursor(shape)

def glfwDestroyCursor(cursor):
    return GLFW.library.__GLFW_LOADER.glfwDestroyCursor(cursor)

def glfwSetCursor(window, cursor):
    return GLFW.library.__GLFW_LOADER.glfwSetCursor(window, cursor)

def glfwSetKeyCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetKeyCallback(window, cbfun)

def glfwSetCharCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetCharCallback(window, cbfun)

def glfwSetCharModsCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetCharModsCallback(window, cbfun)

def glfwSetMouseButtonCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetMouseButtonCallback(window, cbfun)

def glfwSetCursorPosCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetCursorPosCallback(window, cbfun)

def glfwSetCursorEnterCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetCursorEnterCallback(window, cbfun)

def glfwSetScrollCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetScrollCallback(window, cbfun)

def glfwSetDropCallback(window, cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetDropCallback(window, cbfun)

def glfwJoystickPresent(jid):
    return GLFW.library.__GLFW_LOADER.glfwJoystickPresent(jid)

def glfwGetJoystickAxes(jid, count):
    return GLFW.library.__GLFW_LOADER.glfwGetJoystickAxes(jid, count)

def glfwGetJoystickButtons(jid, count):
    return GLFW.library.__GLFW_LOADER.glfwGetJoystickButtons(jid, count)

def glfwGetJoystickHats(jid, count):
    return GLFW.library.__GLFW_LOADER.glfwGetJoystickHats(jid, count)

def glfwGetJoystickName(jid):
    return GLFW.library.__GLFW_LOADER.glfwGetJoystickName(jid)

def glfwGetJoystickGUID(jid):
    return GLFW.library.__GLFW_LOADER.glfwGetJoystickGUID(jid)

def glfwJoystickIsGamepad(jid):
    return GLFW.library.__GLFW_LOADER.glfwJoystickIsGamepad(jid)

def glfwSetJoystickCallback(cbfun):
    return GLFW.library.__GLFW_LOADER.glfwSetJoystickCallback(cbfun)

def glfwUpdateGamepadMappings(string):
    return GLFW.library.__GLFW_LOADER.glfwUpdateGamepadMappings(string)

def glfwGetGamepadName(jid):
    return GLFW.library.__GLFW_LOADER.glfwGetGamepadName(jid)

def glfwGetGamepadState(jid, state):
    return GLFW.library.__GLFW_LOADER.glfwGetGamepadState(jid, state)

def glfwSetClipboardString(window, string):
    return GLFW.library.__GLFW_LOADER.glfwSetClipboardString(window, string)

def glfwGetClipboardString(window):
    return GLFW.library.__GLFW_LOADER.glfwGetClipboardString(window)

def glfwGetTime():
    return GLFW.library.__GLFW_LOADER.glfwGetTime()

def glfwSetTime(time):
    return GLFW.library.__GLFW_LOADER.glfwSetTime(time)

def glfwGetTimerValue():
    return GLFW.library.__GLFW_LOADER.glfwGetTimerValue()

def glfwGetTimerFrequency():
    return GLFW.library.__GLFW_LOADER.glfwGetTimerFrequency()

def glfwMakeContextCurrent(window):
    return GLFW.library.__GLFW_LOADER.glfwMakeContextCurrent(window)

def glfwGetCurrentContext():
    return GLFW.library.__GLFW_LOADER.glfwGetCurrentContext()

def glfwSwapBuffers(window):
    return GLFW.library.__GLFW_LOADER.glfwSwapBuffers(window)

def glfwSwapInterval(interval):
    return GLFW.library.__GLFW_LOADER.glfwSwapInterval(interval)

def glfwExtensionSupported(extension):
    return GLFW.library.__GLFW_LOADER.glfwExtensionSupported(extension)

def glfwGetProcAddress(procname):
    return GLFW.library.__GLFW_LOADER.glfwGetProcAddress(procname)

def glfwVulkanSupported():
    return GLFW.library.__GLFW_LOADER.glfwVulkanSupported()

def glfwGetRequiredInstanceExtensions(count):
    return GLFW.library.__GLFW_LOADER.glfwGetRequiredInstanceExtensions(count)

# Python-GLFW : Yet another GLFW wrapper for Python
# Copyright (c) 2017-2019 vaiorabbit <http://twitter.com/vaiorabbit>
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

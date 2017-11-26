#if defined(__APPLE__)
# if defined(NANOVG_GL3_IMPLEMENTATION)
#  include <OpenGL/gl3.h>
# else
#  include <OpenGL/gl.h>
# endif
#elif defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include "windows.h"
# include <GL/gl.h>
# include <GL/glext.h>
#endif

#if defined(_WIN32)
PFNGLACTIVETEXTUREPROC             glActiveTexture              = NULL;
PFNGLATTACHSHADERPROC              glAttachShader               = NULL;
PFNGLBINDATTRIBLOCATIONPROC        glBindAttribLocation         = NULL;
PFNGLBINDBUFFERPROC                glBindBuffer                 = NULL;
PFNGLBUFFERDATAPROC                glBufferData                 = NULL;
PFNGLCOMPILESHADERPROC             glCompileShader              = NULL;
PFNGLCREATEPROGRAMPROC             glCreateProgram              = NULL;
PFNGLCREATESHADERPROC              glCreateShader               = NULL;
PFNGLDELETEBUFFERSPROC             glDeleteBuffers              = NULL;
PFNGLDELETEPROGRAMPROC             glDeleteProgram              = NULL;
PFNGLDELETESHADERPROC              glDeleteShader               = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC  glDisableVertexAttribArray   = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC   glEnableVertexAttribArray    = NULL;
PFNGLGENBUFFERSPROC                glGenBuffers                 = NULL;
PFNGLGETPROGRAMINFOLOGPROC         glGetProgramInfoLog          = NULL;
PFNGLGETPROGRAMIVPROC              glGetProgramiv               = NULL;
PFNGLGETSHADERINFOLOGPROC          glGetShaderInfoLog           = NULL;
PFNGLGETSHADERIVPROC               glGetShaderiv                = NULL;
PFNGLGETUNIFORMLOCATIONPROC        glGetUniformLocation         = NULL;
PFNGLLINKPROGRAMPROC               glLinkProgram                = NULL;
PFNGLSHADERSOURCEPROC              glShaderSource               = NULL;
PFNGLSTENCILOPSEPARATEPROC         glStencilOpSeparate          = NULL;
PFNGLUNIFORM1IPROC                 glUniform1i                  = NULL;
PFNGLUNIFORM2FVPROC                glUniform2fv                 = NULL;
PFNGLUNIFORM4FVPROC                glUniform4fv                 = NULL;
PFNGLUSEPROGRAMPROC                glUseProgram                 = NULL;
PFNGLVERTEXATTRIBPOINTERPROC       glVertexAttribPointer        = NULL;

PFNGLBINDBUFFERRANGEPROC        glBindBufferRange       = NULL;
PFNGLBINDVERTEXARRAYPROC        glBindVertexArray       = NULL;
PFNGLDELETEVERTEXARRAYSPROC     glDeleteVertexArrays    = NULL;
PFNGLGENERATEMIPMAPPROC         glGenerateMipmap        = NULL;
PFNGLGENVERTEXARRAYSPROC        glGenVertexArrays       = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC   glGetUniformBlockIndex  = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC    glUniformBlockBinding   = NULL;

#endif // defined(_WIN32)

void nvgSetupGL2()
{
#if defined(_WIN32)
    glActiveTexture            = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
    glAttachShader             = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
    glBindAttribLocation       = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
    glBindBuffer               = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
    glBufferData               = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
    glCompileShader            = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
    glCreateProgram            = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
    glCreateShader             = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
    glDeleteBuffers            = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
    glDeleteProgram            = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
    glDeleteShader             = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
    glEnableVertexAttribArray  = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
    glGenBuffers               = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
    glGetProgramInfoLog        = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
    glGetProgramiv             = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
    glGetShaderInfoLog         = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
    glGetShaderiv              = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
    glGetUniformLocation       = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
    glLinkProgram              = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
    glShaderSource             = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
    glStencilOpSeparate        = (PFNGLSTENCILOPSEPARATEPROC)wglGetProcAddress("glStencilOpSeparate");
    glUniform1i                = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
    glUniform2fv               = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
    glUniform4fv               = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
    glUseProgram               = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
    glVertexAttribPointer      = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
#endif // defined(_WIN32)
}

void nvgSetupGL3()
{
#if defined(_WIN32)
    nvgSetupGL2();
    glBindBufferRange      = (PFNGLBINDBUFFERRANGEPROC)wglGetProcAddress("glBindBufferRange");
    glBindVertexArray      = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
    glDeleteVertexArrays   = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
    glGenerateMipmap       = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
    glGenVertexArrays      = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
    glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)wglGetProcAddress("glGetUniformBlockIndex");
    glUniformBlockBinding  = (PFNGLUNIFORMBLOCKBINDINGPROC)wglGetProcAddress("glUniformBlockBinding");
#endif // defined(_WIN32)
}

#include "nanovg.h"
#include "nanovg.c"
#include "nanovg_gl.h"

/*
Python-NanoVG : A Python bindings of NanoVG
Copyright (c) 2017 vaiorabbit

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
 */

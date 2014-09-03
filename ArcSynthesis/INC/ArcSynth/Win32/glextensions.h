#pragma once
#include <ArcSynth/precompiled.h>

extern PFNGLATTACHSHADERPROC                glAttachShader;
extern PFNGLBINDBUFFERPROC                  glBindBuffer;
extern PFNGLBINDBUFFERBASEPROC              glBindBufferBase;
extern PFNGLBINDBUFFERRANGEPROC             glBindBufferRange;
extern PFNGLBINDVERTEXARRAYPROC             glBindVertexArray;
extern PFNGLBUFFERDATAPROC                  glBufferData;
extern PFNGLBUFFERSUBDATAPROC               glBufferSubData;
extern PFNGLCOMPILESHADERPROC               glCompileShader;
extern PFNGLCREATEPROGRAMPROC               glCreateProgram;
extern PFNGLCREATESHADERPROC                glCreateShader;
extern PFNGLDELETESHADERPROC                glDeleteShader;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC    glDisableVertexAttribArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC     glEnableVertexAttribArray;
extern PFNGLGENBUFFERSPROC                  glGenBuffers;
extern PFNGLGENVERTEXARRAYSPROC             glGenVertexArrays;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC     glGetActiveUniformBlockIV;
extern PFNGLGETACTIVEUNIFORMSIVPROC         glGetActiveUniformsIV;
extern PFNGLGETPROGRAMINFOLOGPROC           glGetProgramInfoLog;
extern PFNGLGETPROGRAMIVPROC                glGetProgramIV;
extern PFNGLGETSHADERINFOLOGPROC            glGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC                 glGetShaderIV;
extern PFNGLGETUNIFORMBLOCKINDEXPROC        glGetUniformBlockIndex;
extern PFNGLGETUNIFORMINDICESPROC           glGetUniformIndices;
extern PFNGLLINKPROGRAMPROC                 glLinkProgram;
extern PFNGLSHADERSOURCEPROC                glShaderSource;
extern PFNGLUNIFORMBLOCKBINDINGPROC         glUniformBlockBinding;
extern PFNGLUSEPROGRAMPROC                  glUseProgram;
extern PFNGLVERTEXATTRIBPOINTERPROC         glVertexAttribPointer;
extern PFNWGLCHOOSEPIXELFORMATARBPROC       wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribsARB;
extern PFNWGLSWAPINTERVALEXTPROC            wglSwapIntervalEXT;

bool LoadGLExtensions( void );
bool LoadTempGLExtensions( void );


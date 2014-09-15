#include <ArcSynth/precompiled.h>
#include <ArcSynth/Win32/glextensions.h>

PFNGLATTACHSHADERPROC               glAttachShader = NULL;
PFNGLBINDBUFFERPROC                 glBindBuffer = NULL;
PFNGLBINDBUFFERBASEPROC             glBindBufferBase = NULL;
PFNGLBINDBUFFERRANGEPROC            glBindBufferRange = NULL;
PFNGLBINDVERTEXARRAYPROC            glBindVertexArray = NULL;
PFNGLBUFFERDATAPROC                 glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC              glBufferSubData = NULL;
PFNGLCOMPILESHADERPROC              glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC              glCreateProgram = NULL;
PFNGLCREATESHADERPROC               glCreateShader = NULL;
PFNGLDELETESHADERPROC               glDeleteShader = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC   glDisableVertexAttribArray = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC    glEnableVertexAttribArray = NULL;
PFNGLGENBUFFERSPROC                 glGenBuffers = NULL;
PFNGLGENVERTEXARRAYSPROC            glGenVertexArrays = NULL;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC    glGetActiveUniformBlockIV = NULL;
PFNGLGETACTIVEUNIFORMSIVPROC        glGetActiveUniformsIV = NULL;
PFNGLGETPROGRAMINFOLOGPROC          glGetProgramInfoLog = NULL;
PFNGLGETPROGRAMIVPROC               glGetProgramIV = NULL;
PFNGLGETSHADERINFOLOGPROC           glGetShaderInfoLog = NULL;
PFNGLGETSHADERIVPROC                glGetShaderIV = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC       glGetUniformBlockIndex = NULL;
PFNGLGETUNIFORMINDICESPROC          glGetUniformIndices = NULL;
PFNGLGETUNIFORMLOCATIONPROC         glGetUniformLocation = NULL;
PFNGLLINKPROGRAMPROC                glLinkProgram = NULL;
PFNGLSHADERSOURCEPROC               glShaderSource = NULL;
PFNGLUNIFORM3FPROC                  glUniform3f = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC        glUniformBlockBinding = NULL;
PFNGLUSEPROGRAMPROC                 glUseProgram = NULL;
PFNGLVERTEXATTRIBPOINTERPROC        glVertexAttribPointer = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC      wglChoosePixelFormatARB = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC   wglCreateContextAttribsARB = NULL;
PFNWGLSWAPINTERVALEXTPROC           wglSwapIntervalEXT = NULL;

bool LoadGLExtensions( void )
{
    glAttachShader = ( PFNGLATTACHSHADERPROC )wglGetProcAddress( "glAttachShader" );
    if( glAttachShader == NULL )
    {
        return false;
    }

    glBindBuffer = ( PFNGLBINDBUFFERPROC )wglGetProcAddress( "glBindBuffer" );
    if( glBindBuffer == NULL )
    {
        return false;
    }

    glBindBufferBase = ( PFNGLBINDBUFFERBASEPROC )wglGetProcAddress( "glBindBufferBase" );
    if( glBindBufferBase == NULL )
    {
        return false;
    }

    glBindBufferRange = ( PFNGLBINDBUFFERRANGEPROC )wglGetProcAddress( "glBindBufferRange" );
    if( glBindBufferRange == NULL )
    {
        return false;
    }

    glBindVertexArray = ( PFNGLBINDVERTEXARRAYPROC )wglGetProcAddress( "glBindVertexArray" );
    if( glBindVertexArray == NULL )
    {
        return false;
    }

    glBufferData = ( PFNGLBUFFERDATAPROC )wglGetProcAddress( "glBufferData" );
    if( glBufferData == NULL )
    {
        return false;
    }

    glBufferSubData = ( PFNGLBUFFERSUBDATAPROC )wglGetProcAddress( "glBufferSubData" );
    if( glBufferSubData == NULL )
    {
        return false;
    }

    glCreateProgram = ( PFNGLCREATEPROGRAMPROC )wglGetProcAddress( "glCreateProgram" );
    if( glCreateProgram == NULL )
    {
        return false;
    }

    glCompileShader = ( PFNGLCOMPILESHADERPROC )wglGetProcAddress( "glCompileShader" );
    if( glCompileShader == NULL )
    {
        return false;
    }

    glCreateShader = ( PFNGLCREATESHADERPROC )wglGetProcAddress( "glCreateShader" );
    if( glCreateShader == NULL )
    {
        return false;
    }

    glDeleteShader = ( PFNGLDELETESHADERPROC )wglGetProcAddress( "glDeleteShader" );
    if( glDeleteShader == NULL )
    {
        return false;
    }
    
    glDisableVertexAttribArray = ( PFNGLDISABLEVERTEXATTRIBARRAYPROC )wglGetProcAddress( "glDisableVertexAttribArray" );
    if( glDisableVertexAttribArray == NULL )
    {
        return false;
    }

    glEnableVertexAttribArray = ( PFNGLENABLEVERTEXATTRIBARRAYPROC )wglGetProcAddress( "glEnableVertexAttribArray" );
    if( glEnableVertexAttribArray == NULL )
    {
        return false;
    }

    glGenBuffers = ( PFNGLGENBUFFERSPROC )wglGetProcAddress( "glGenBuffers" );
    if( glGenBuffers == NULL )
    {
        return false;
    }

    glGenVertexArrays = ( PFNGLGENVERTEXARRAYSPROC )wglGetProcAddress( "glGenVertexArrays" );
    if( glGenVertexArrays == NULL )
    {
        return false;
    }

    glGetActiveUniformBlockIV = ( PFNGLGETACTIVEUNIFORMBLOCKIVPROC )wglGetProcAddress( "glGetActiveUniformBlockiv" );
    if( glGetActiveUniformBlockIV == NULL )
    {
        return false;
    }

    glGetActiveUniformsIV = ( PFNGLGETACTIVEUNIFORMSIVPROC )wglGetProcAddress( "glGetActiveUniformsiv" );
    if( glGetActiveUniformsIV == NULL )
    {
        return false;
    }

    glGetProgramInfoLog = ( PFNGLGETPROGRAMINFOLOGPROC )wglGetProcAddress( "glGetProgramInfoLog" );
    if( glGetProgramInfoLog == NULL )
    {
        return false;
    }

    glGetProgramIV = ( PFNGLGETPROGRAMIVPROC )wglGetProcAddress( "glGetProgramiv" );
    if( glGetProgramIV == NULL )
    {
        return false;
    }

    glGetShaderInfoLog = ( PFNGLGETSHADERINFOLOGPROC )wglGetProcAddress( "glGetShaderInfoLog" );
    if( glGetShaderInfoLog == NULL )
    {
        return false;
    }

    glGetShaderIV = ( PFNGLGETSHADERIVPROC )wglGetProcAddress( "glGetShaderiv" );
    if( glGetProgramIV == NULL )
    {
        return false;
    }

    glGetUniformBlockIndex = ( PFNGLGETUNIFORMBLOCKINDEXPROC )wglGetProcAddress( "glGetUniformBlockIndex" );
    if( glGetUniformBlockIndex == NULL )
    {
        return false;
    }

    glGetUniformIndices = ( PFNGLGETUNIFORMINDICESPROC )wglGetProcAddress( "glGetUniformIndices" );
    if( glGetUniformIndices == NULL )
    {
        return false;
    }
    
    glGetUniformLocation = ( PFNGLGETUNIFORMLOCATIONPROC )wglGetProcAddress( "glGetUniformLocation" );
    if( glGetUniformLocation == NULL )
    {
        return false;
    }

    glLinkProgram = ( PFNGLLINKPROGRAMPROC )wglGetProcAddress( "glLinkProgram" );
    if( glLinkProgram == NULL )
    {
        return false;
    }

    glShaderSource = ( PFNGLSHADERSOURCEPROC )wglGetProcAddress( "glShaderSource" );
    if( glShaderSource == NULL )
    {
        return false;
    }


    glUniform3f = ( PFNGLUNIFORM3FPROC )wglGetProcAddress( "glUniform3f" );
    if( glUniform3f == NULL )
    {
        return false;
    }

    glUniformBlockBinding = ( PFNGLUNIFORMBLOCKBINDINGPROC )wglGetProcAddress( "glUniformBlockBinding" );
    if( glUniformBlockBinding == NULL )
    {
        return false;
    }

    glUseProgram = ( PFNGLUSEPROGRAMPROC )wglGetProcAddress( "glUseProgram" );
    if( glUseProgram == NULL )
    {
        return false;
    }

    glVertexAttribPointer = ( PFNGLVERTEXATTRIBPOINTERPROC )wglGetProcAddress( "glVertexAttribPointer" );
    if( glVertexAttribPointer == NULL )
    {
        return false;
    }

    wglChoosePixelFormatARB = ( PFNWGLCHOOSEPIXELFORMATARBPROC )wglGetProcAddress( "wglChoosePixelFormatARB" );
    if( wglChoosePixelFormatARB == NULL )
    {
        return false;
    }

    wglCreateContextAttribsARB = ( PFNWGLCREATECONTEXTATTRIBSARBPROC )wglGetProcAddress( "wglCreateContextAttribsARB" );
    if( wglCreateContextAttribsARB == NULL )
    {
        return false;
    }

    wglSwapIntervalEXT = ( PFNWGLSWAPINTERVALEXTPROC )wglGetProcAddress( "wglSwapIntervalEXT" );
    if( wglSwapIntervalEXT == NULL )
    {
        return false;
    }

    return true;
}

bool LoadTempGLExtensions( void )
{
    wglChoosePixelFormatARB = ( PFNWGLCHOOSEPIXELFORMATARBPROC )wglGetProcAddress( "wglChoosePixelFormatARB" );
    if( wglChoosePixelFormatARB == NULL )
    {
        return false;
    }
    
    wglCreateContextAttribsARB = ( PFNWGLCREATECONTEXTATTRIBSARBPROC )wglGetProcAddress( "wglCreateContextAttribsARB" );
    if( wglCreateContextAttribsARB == NULL )
    {
        return false;
    }

    return true;
}


#include <ArcSynth/precompiled.h>
#include <ArcSynth/OpenGl/glrenderer.h>
#include <ArcSynth/logger.h>

GLRenderer::GLRenderer( std::shared_ptr<Configuration> config_ptr, std::shared_ptr<Logger> logger_ptr )
{
    hWnd = NULL;
    config = config_ptr;
    logger = logger_ptr;
}

bool GLRenderer::Initialize( HWND h_wnd )
{
    GLenum result;
    PIXELFORMATDESCRIPTOR pixel_format_descriptor;

    unsigned int format_count;
    std::string vendor_name;
    std::string renderer_name;

    // Double buffered OpenGL accelerated context, with 32-bit color, 24 bit depth, and 8-bit stencil.
    int attribute_list_int[] =
    {
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_SWAP_METHOD_ARB, WGL_SWAP_EXCHANGE_ARB,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };

    deviceContext = GetDC( h_wnd );
    if( NULL == deviceContext )
    {
        logger->Log( LOG_TYPE::CRITICAL, "Renderer Initialization Error", "Could not get device context." );
        return false;
    }

    int pixel_format;
    result = wglChoosePixelFormatARB( deviceContext, attribute_list_int, NULL, 1, &pixel_format, &format_count );
    if( GL_TRUE != result )
    {
        logger->Log( LOG_TYPE::CRITICAL, "Renderer Initialization Error", "Could not choose the pixel format." );
        return false;
    }

    result = SetPixelFormat( deviceContext, pixel_format, &pixel_format_descriptor );
    if( GL_TRUE != result )
    {
        logger->Log( LOG_TYPE::CRITICAL, "Renderer Initialization Error", "Error setting the pixel format." );
        return false;
    }

    // OpenGL 3.3 core context
    int attribute_list[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    renderContext = wglCreateContextAttribsARB( deviceContext, 0, attribute_list );
    if( NULL == renderContext )
    {
        logger->Log( LOG_TYPE::CRITICAL, "Renderer Initialization Error", "Error creating rendering context." );
        return false;
    }

    result = wglMakeCurrent( deviceContext, renderContext );
    if( GL_TRUE != result )
    {
        logger->Log( LOG_TYPE::CRITICAL, "Renderer Initialization Error", "Error making rendering context current." );
        return false;
    }

    // load the extensions
    if( LoadGLExtensions() == false )
    {
        return false;
    }

    // For now we don't want any culling or depth testing
    // Just get the triangles on the screen
    glClearDepth( 1.0 );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );
    glCullFace( GL_BACK );

    // Clockwise triangles face forward
    glFrontFace( GL_CW );

    auto get_vendor = const_cast< GLubyte * >( glGetString( GL_VENDOR ) );
    vendor_name = std::string( reinterpret_cast< char * >( get_vendor ) );
    auto get_renderer = const_cast< GLubyte * >( glGetString( GL_RENDERER ) );
    renderer_name = std::string( reinterpret_cast< char * >( get_renderer ) );

    wglSwapIntervalEXT( 1 );

    hWnd = h_wnd;

    return true;
}

void GLRenderer::Draw( void )
{
    SwapBuffers( deviceContext );
}

void GLRenderer::Shutdown( void )
{
    // Release the context
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext( renderContext );
    wglDeleteContext( tempRenderContext );
    tempRenderContext = NULL;
    renderContext = NULL;
    ReleaseDC( hWnd, deviceContext );
    deviceContext = NULL;
    logger->Log( LOG_TYPE::INFO, "Render Shutdown", "device and render contexts deleted." );
}

bool GLRenderer::initializeTemporaryExtensions( HWND h_wnd )
{
    GLenum result;
    PIXELFORMATDESCRIPTOR pixel_format_descriptor;

    // Create a temporary context while we load the extensions
    deviceContext = GetDC( h_wnd );
    if( NULL == deviceContext )
    {
        logger->Log( LOG_TYPE::CRITICAL, "Renderer Initialization Error", "Could not create temporary device context." );
        return false;
    }

    result = SetPixelFormat( deviceContext, 1, &pixel_format_descriptor );
    if( GL_TRUE != result )
    {
        logger->Log( LOG_TYPE::CRITICAL, "Renderer Initialization Error", "Could not set temporary pixel format." );
        return false;
    }

    tempRenderContext = wglCreateContext( deviceContext );
    if( NULL == tempRenderContext )
    {
        logger->Log( LOG_TYPE::CRITICAL, "Renderer Initialization Error", "Could not set create temporary OpenGL context." );
        return false;
    }

    result = wglMakeCurrent( deviceContext, tempRenderContext );
    if( GL_TRUE != result )
    {
        logger->Log( LOG_TYPE::CRITICAL, "Renderer Initialization Error", "Could not set make temporary OpenGL context current." );
        return false;
    }

    if( LoadTempGLExtensions() == false )
    {
        logger->Log( LOG_TYPE::CRITICAL, "Renderer Initialization Error", "Could not load temporary OpenGL extensions." );
        return false;
    }

    // Release the temporary context.
    wglMakeCurrent( NULL, NULL );
    ReleaseDC( h_wnd, deviceContext );
    deviceContext = NULL;
    logger->Log( LOG_TYPE::INFO, "Renderer Initialization", "Loaded temporary OpenGL extensions." );
}

void GLRenderer::SetClearColor( glm::vec3 targetColor )
{
    glClearColor( targetColor.r, targetColor.g, targetColor.b, 1.0f );
}

void GLRenderer::resizeViewport( int width, int height )
{
    glViewport( 0, 0, width, height );
}
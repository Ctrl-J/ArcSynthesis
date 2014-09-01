#include <precompiled.h>
#include <graphics_configuration.h>

GraphicsConfiguration::GraphicsConfiguration( const std::string &default_renderer,
                                              bool default_fullscreen,
                                              bool default_sync,
                                              glm::ivec2 default_window_dimensions)
{
    defaultRenderer = default_renderer;
    currentRenderer = default_renderer;

    defaultFullscreen = default_fullscreen;
    isFullscreen = default_fullscreen;
    
    defaultSync = default_sync;
    vSync = default_sync;
    
    defaultWindowDimensions = default_window_dimensions;
    currentWindowDimensions = default_window_dimensions;

    screenDimensions = glm::ivec2( 0, 0 );
    windowPosition = glm::ivec2( 0, 0 );
}

std::string GraphicsConfiguration::GetRenderer( void )
{
    return currentRenderer;
}

void GraphicsConfiguration::SetRenderer( const std::string &other )
{
    currentRenderer = other;
}

bool GraphicsConfiguration::GetFullscreen( void )
{
    return isFullscreen;
}

void GraphicsConfiguration::SetFullscreen( bool fullscreen )
{
    isFullscreen = fullscreen;
}

bool GraphicsConfiguration::GetVSync()
{
    return vSync;
}

void GraphicsConfiguration::SetVSync( bool v_sync )
{
    vSync = v_sync;
}

glm::ivec2 GraphicsConfiguration::GetWindowDimensions( void )
{
    return currentWindowDimensions;
}

void GraphicsConfiguration::SetWindowDimensions( const glm::ivec2 &dimensions )
{
    currentWindowDimensions = dimensions;
}

int GraphicsConfiguration::GetWindowWidth( void )
{
    return currentWindowDimensions.x;
}

void GraphicsConfiguration::SetWindowWidth( int width )
{
    if( width < 100 )
    {
        width = defaultWindowDimensions.x;
    }

    currentWindowDimensions.x = width;
}

int GraphicsConfiguration::GetWindowHeight( void )
{
    return currentWindowDimensions.y;
}

void GraphicsConfiguration::SetWindowHeight( int height )
{
    if( height < 100 )
    {
        height = defaultWindowDimensions.y;
    }

    currentWindowDimensions.y = height;
}
    
glm::ivec2 GraphicsConfiguration::GetWindowPosition( void )
{
    return windowPosition;
}

void GraphicsConfiguration::SetWindowPosition( const glm::ivec2 &position )
{
    // We do the bounds checking per axis, so do it on the axis functions
    SetWindowXPosition( position.x );
    SetWindowYPosition( position.y );
}

int GraphicsConfiguration::GetWindowXPosition( void )
{
    return windowPosition.x;
}

void GraphicsConfiguration::SetWindowXPosition( int x )
{
    // If the screen has a size it will be set (default is zero, so if it's not set then don't bother bounds checking.)
    if( screenDimensions.x > 0 )
    {
        if( x < 0 )
        {
            x = 0;
        }
        else if(x > screenDimensions.x)
        {
            x = screenDimensions.x;
        }
    }

    windowPosition.x = x;
}

int GraphicsConfiguration::GetWindowYPosition( void )
{
    return windowPosition.y;
}

void GraphicsConfiguration::SetWindowYPosition( int y )
{
    // If the screen has a size it will be set (default is zero, so if it's not set then don't bother bounds checking.)
    if( screenDimensions.y > 0 )
    {
        if( y < 0 )
        {
            y = 0;
        }
        else if(y > screenDimensions.y)
        {
            y = screenDimensions.y;
        }
    }

    windowPosition.y = y;
}
    
glm::ivec2 GraphicsConfiguration::GetScreenDimensions( void )
{
    return screenDimensions;
}

void GraphicsConfiguration::SetScreenDimensions( const glm::ivec2 &dimensions )
{
    SetScreenWidth( dimensions.x );
    SetScreenHeight( dimensions.y );
}

int GraphicsConfiguration::GetScreenWidth( void )
{
    return screenDimensions.x;
}

void GraphicsConfiguration::SetScreenWidth( int width )
{
    if( width < 0 )
    {
        width = 0;
    }
   
    screenDimensions.x = width;
}

int GraphicsConfiguration::GetScreenHeight( void )
{
    return screenDimensions.y;
}

void GraphicsConfiguration::SetScreenHeight( int height )
{
    if( height < 0 )
    {
        height = 0;
    }

    screenDimensions.y = height;
}

double GraphicsConfiguration::GetCurrentAspectRatio( void )
{
    return static_cast< double >( currentWindowDimensions.x ) / currentWindowDimensions.y;
}
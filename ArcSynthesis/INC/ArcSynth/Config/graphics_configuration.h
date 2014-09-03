#pragma once
#include <ArcSynth/precompiled.h>

class GraphicsConfiguration
{
public:
    GraphicsConfiguration( const std::string &default_renderer,
                           bool default_fullscreen,
                           bool default_sync,
                           glm::ivec2 default_window_dimensions );

    std::string GetRenderer( void );
    void SetRenderer( const std::string &other );

    bool GetFullscreen( void );
    void SetFullscreen( bool fullscreen );
    
    bool GetVSync( void );
    void SetVSync( bool v_sync );

    glm::ivec2 GetWindowDimensions( void );
    glm::ivec2 GetDefaultWindowDimensions( void );
    void SetWindowDimensions( const glm::ivec2 &dimensions );

    int GetWindowWidth( void );
    int GetDefaultWindowWidth( void );
    void SetWindowWidth( int width );

    int GetWindowHeight( void );
    int GetDefaultWindowHeight( void );
    void SetWindowHeight( int height );
    
    glm::ivec2 GetWindowPosition( void );
    void SetWindowPosition( const glm::ivec2 &position );

    int GetWindowXPosition( void );
    void SetWindowXPosition( int x );

    int GetWindowYPosition( void );
    void SetWindowYPosition( int y );

    glm::ivec2 GetScreenDimensions( void );
    void SetScreenDimensions( const glm::ivec2 &dimensions );

    int GetScreenWidth( void );
    void SetScreenWidth( int width );
    
    int GetScreenHeight( void );
    void SetScreenHeight( int height );

    double GetCurrentAspectRatio( void );
    
private:
    std::string defaultRenderer;
    std::string currentRenderer;

    bool defaultFullscreen;
    bool isFullscreen;
    
    bool defaultSync;
    bool vSync;

    glm::ivec2 currentWindowDimensions;
    glm::ivec2 defaultWindowDimensions;
    glm::ivec2 screenDimensions;
    glm::ivec2 windowPosition;
};

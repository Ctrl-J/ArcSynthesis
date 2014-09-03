#pragma once
#include <ArcSynth/precompiled.h>

class Logger;
class Configuration;

class GLRenderer
{
    friend class Application;
public:
    GLRenderer( std::shared_ptr<Configuration> config_ptr, std::shared_ptr<Logger> logger_ptr );

    bool Initialize( HWND h_wnd );
    void Draw( void );
    void Shutdown( void );


    void SetClearColor( glm::vec3 targetColor );

private:
    bool initializeTemporaryExtensions( HWND h_wnd );
    void resizeViewport( int width, int height );
    
    HWND hWnd;
    HDC deviceContext;
    HGLRC renderContext;
    HGLRC tempRenderContext;

    std::shared_ptr<Configuration> config;
    std::shared_ptr<Logger> logger;
};
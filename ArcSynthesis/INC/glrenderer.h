#pragma once
#include <precompiled.h>

class GLRenderer
{
    friend class Application;
public:
    GLRenderer( void );

    bool Initialize( HWND h_wnd );
    void Draw( void );
    void Shutdown( void );

    void SetClearColor( glm::vec3 targetColor );

private:
    bool initializeTemporaryExtensions( HWND h_wnd );
    
    HWND hWnd;
    HDC deviceContext;
    HGLRC renderContext;
    HGLRC tempRenderContext;
};
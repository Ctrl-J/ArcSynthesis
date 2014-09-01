#pragma once
#include <precompiled.h>

#include <glrenderer.h>
#include <keyboard.h>
#include <timer.h>
#include <config.h>

class Application
{
public:

    // Constructor just sets some defaults.
    Application( const std::wstring &set_name );
    ~Application( void );

    // Rule of three, and there's no reason to copy the application.
    Application( const Application &other ) = delete;
    Application &operator= ( const Application &other ) = delete;

    // Initializes the all of the application systems.
    bool Initialize( void );

    // Handles the main loop and windows message pump
    bool Run( void );

    // Cleans up anything that is not automatically cleaned up
    void Shutdown( void );

    // Accessor for internal initialization status
    bool IsInitialized( void ) const;
    
    // Handles any application relevant Win32 messages
    LRESULT CALLBACK WindowProc( HWND handle, UINT message, WPARAM w_param, LPARAM l_param );

private:
    // Creates the Win32 application window and makes the appropriate calls
    // to make sure that the context is set up properly
    bool initializeWindow( void );

    // Logic step wrapper. So that we can insert state updates into the main loop.
    void step( void );
    // Draws the scene.
    void draw( void );

    // Not yet implemented. This will resize the current window to the size 
    // specified, handling any viewport changes. Possibly going to throw
    // window fullscreen toggling into here?
    bool resizeWindow( unsigned int width, unsigned int height );

    // Cleans up the window and destroys the OpenGL context
    void shutdownWindow( void );

    std::wstring applicationName;
    std::wstring className;

    HINSTANCE hInstance;
    HWND hWnd;
    
    // Keyboard input
    std::shared_ptr<Keyboard> keyboard;

    // OpenGL renderer
    std::shared_ptr<GLRenderer> renderer;

    // Timer with accumulator and constant-step
    std::shared_ptr<Timer> timer;
    double maxFrameTime;
    double lastTime;
    double accumulatedTime;
    double timeStep;

    std::shared_ptr<Configuration> config;

    bool initialized;
    bool done;
    bool changedResolution;

    bool windowActivated;
    bool windowInitialized;

    glm::vec3 color;
    glm::vec3 speed;
};
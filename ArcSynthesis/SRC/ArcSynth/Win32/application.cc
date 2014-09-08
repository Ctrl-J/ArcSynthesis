#include <ArcSynth/precompiled.h>
#include <ArcSynth/Win32/application.h>
#include <ArcSynth/Chapters/chapter_zero.h>
#include <ArcSynth/Chapters/chapter_one.h>
#include <ArcSynth/Chapters/chapter_two.h>

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    if (msg == WM_NCCREATE) 
    {
        LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
	}

    Application *app = NULL;
    app = (Application *)GetWindowLongPtr( hWnd, GWLP_USERDATA );
    if( app != NULL )
    {
        return app->WindowProc( hWnd, msg, wParam, lParam );
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}


Application::Application( const std::wstring &set_name )
{
    if( set_name.size() <= 0 )
    {
        applicationName = L"GL_application";
    }
    else
    {
        applicationName = set_name;
    }

    className = set_name + L"_class";

    maxFrameTime = 0.0625;

    lastTime = 0.0;
    accumulatedTime = 0.0;
    timeStep = 0.008;

    initialized = false;
    done = false;
    changedResolution = false;

    windowActivated = false;
    windowInitialized = false;

    keyboard = nullptr;
    renderer = nullptr;
    timer = nullptr;
    config = nullptr;
    currentChapter = nullptr;
}

Application::~Application( void )
{
    // gotta love smart pointers
}

bool Application::Initialize( void )
{
    config = std::make_shared<Configuration>();
    config->LoadConfiguration( "config.xml" );

    logger = std::make_shared<Logger>();
    logger->Initialize( config->SystemConfig()->GetLogFolder(), LOG_TYPE::INFO, LOG_TYPE::CRITICAL );

    renderer = std::make_shared<GLRenderer>( config, logger );
    if( initializeWindow() == false )
    {
        MessageBox( NULL, L"Failed to initialize window.", L"SYSTEM ERROR", MB_OK | MB_ICONERROR );
        initialized = false;
        windowActivated = false;

        return false;
    }
    
    keyboard = std::make_shared<Keyboard>( logger );

    timer = std::make_shared<Timer>();
    timer->SetTime();

    currentChapter = std::make_shared<ChapterTwo>( "chapterTwo.xml", config, keyboard, logger );
    currentChapter->Initialize();

    initialized = true;

    return true;
}

bool Application::Run( void )
{
    MSG message;
    ZeroMemory( &message, sizeof( message ) );

    while( done == false )
    {
        if( PeekMessage( &message, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }

        if( ( WM_QUIT == message.message ) || ( false == initialized ) )
        {
            done = true;
            break;
        }

        // ESC is the default quit. Probably will change this later once
        // I need a more robust state system.
        if( keyboard->IsKeydown( VK_ESCAPE ) )
        {
            done = true;
            break;
        }

        if( keyboard->IsKeyPressed( VK_NEXT ) )
        {
            toggleFullscreen();
            continue;
        }

        // Fixed time-step, full speed render. To accomplish this, we
        // use an accumulator.

        // First, we get the time since the last render.
        double frame_time = timer->GetDeltaTime();
        if( maxFrameTime < frame_time )
        {
            frame_time = maxFrameTime;
        }

        // Then we add it to the accumulator.
        accumulatedTime += frame_time;

        // We then subtract off fixed chunks of time and simulate according
        // to that time step. This gives us a fixed simulation time-step, while
        // allowing us to render with a variable time-step.
        while( accumulatedTime > timeStep )
        {
            accumulatedTime -= timeStep;
            step();
        }

        draw();
    }

    return true;
}

void Application::step( void )
{
    currentChapter->Step( timeStep );
}

void Application::draw( void )
{
    currentChapter->Draw();
    renderer->Draw();
}

void Application::Shutdown( void )
{
    currentChapter->Shutdown();
    renderer->Shutdown();
    shutdownWindow();
}

bool Application::initializeWindow( void )
{
    hInstance = GetModuleHandle( NULL );

    // Standard windows boilerplate
    WNDCLASSEX wcx;
    ZeroMemory( &wcx, sizeof( wcx ) );

    wcx.cbClsExtra = 0;
    wcx.cbWndExtra = 0;
    wcx.hbrBackground = ( HBRUSH )GetStockObject( GRAY_BRUSH );
    wcx.hCursor = LoadCursor( NULL, IDC_CROSS );
    wcx.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wcx.hIconSm = wcx.hIcon;
    wcx.hInstance = hInstance;
    wcx.lpfnWndProc = WndProc;
    wcx.lpszClassName = className.c_str();
    wcx.lpszMenuName = NULL;
    wcx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcx.cbSize = sizeof( wcx );

    RegisterClassEx( &wcx );

    // The following code assumes we only have one monitor and are displaying on the primary monitor
    glm::ivec2 screenDimensions;
    int value = GetSystemMetrics( SM_CXSCREEN );
    screenDimensions.x = value;
    
    value = GetSystemMetrics( SM_CYSCREEN );
    screenDimensions.y = value;

    config->GraphicsConfig()->SetScreenDimensions( screenDimensions );

    std::stringstream message;
    // Here we create a temporary window so that we can initialize the OpenGL extension methods used to create
    // the context we want.
    HWND temp_h_wnd = CreateWindowEx( NULL, className.c_str(), applicationName.c_str(), WS_POPUP, 100, 100, 100, 100,
                                      NULL, NULL, hInstance, this );
    if( NULL == temp_h_wnd )
    {
        logger->Log( LOG_TYPE::ERR, "Initialization Error", "Error creating temporary window handle." );
        return false;
    }
    ShowWindow( temp_h_wnd, SW_HIDE );
    if( renderer->initializeTemporaryExtensions( temp_h_wnd ) == false )
    {
        DestroyWindow( temp_h_wnd );
        temp_h_wnd = NULL;
        
        logger->Log( LOG_TYPE::ERR, "Initialization Error", "Error loading temporary OpenGL function pointers." );
        return false;
    }
    
    if( config->GraphicsConfig()->GetFullscreen() == false )
    {
        // The following code sets up a windowed display that is centered on the screen
        if( config->GraphicsConfig()->GetWindowWidth() > (screenDimensions.x - 20) )
        {
            config->GraphicsConfig()->SetWindowWidth( screenDimensions.x - 20 );
        }
        if( config->GraphicsConfig()->GetWindowHeight() > (screenDimensions.y - 20) )
        {
            config->GraphicsConfig()->SetWindowHeight( screenDimensions.y - 20 );
        }

    	int x_position = ( screenDimensions.x - config->GraphicsConfig()->GetWindowWidth() ) / 2;
    	int y_position = ( screenDimensions.y - config->GraphicsConfig()->GetWindowHeight() ) / 2;

    	config->GraphicsConfig()->SetWindowPosition( glm::ivec2( x_position, y_position ) );
        message << "Initial window set to windowed mode at ( " << x_position << ", " << y_position << " ) with dimensions "
            << config->GraphicsConfig()->GetWindowWidth() << "x" << config->GraphicsConfig()->GetWindowHeight();
    }
    else
    {
        // Otherwise we do a fullscreen window.
        config->GraphicsConfig()->SetWindowDimensions( screenDimensions );
        config->GraphicsConfig()->SetWindowPosition( glm::ivec2( 0, 0 ) );
        message << "Initial window set to fullscreen mode with dimensions " << screenDimensions.x << "x" << screenDimensions.y;
    }

    // And now we can finally create the target context
    hWnd = CreateWindowEx( NULL, 
                           className.c_str(), 
                           applicationName.c_str(), 
                           WS_POPUP, 
                           config->GraphicsConfig()->GetWindowXPosition(), 
                           config->GraphicsConfig()->GetWindowYPosition(),
                           config->GraphicsConfig()->GetWindowWidth(),
                           config->GraphicsConfig()->GetWindowHeight(),
                           NULL, 
                           NULL, 
                           hInstance, 
                           this );
    if( NULL == hWnd )
    {
        logger->Log( LOG_TYPE::ERR, "Initialization Error", "Error creating window handle." );
        return false;
    }

    logger->Log( LOG_TYPE::INFO, "Window Created", message.str() );
    windowActivated = false;
    if( renderer->Initialize( hWnd ) == false )
    {
        DestroyWindow( hWnd );
        hWnd = NULL;
        logger->Log( LOG_TYPE::ERR, "Initialization Error", "Error initializing renderer." );

        return false;
    }

    logger->Log( LOG_TYPE::INFO, "Renderer Initialized", "Initialization of render context complete." );

    // Destroy the temporary window
    DestroyWindow( temp_h_wnd );
    temp_h_wnd = NULL;


    // And we're done!
    ShowWindow( hWnd, SW_SHOW );
    SetFocus( hWnd );
    SetForegroundWindow( hWnd );

    windowActivated = true;
    windowInitialized = true;

    return true;
}

bool Application::resizeWindow( unsigned int width, unsigned int height )
{
    // First set the dimensions. This also handles sizing the dimensions( window will never be smaller than 100x100 )
    config->GraphicsConfig()->SetWindowDimensions( glm::ivec2( width, height ) );
    glm::ivec2 windowDimensions = config->GraphicsConfig()->GetWindowDimensions();
    glm::ivec2 screeenDimensions = config->GraphicsConfig()->GetScreenDimensions();

    // note, these will work fine for fullscreen as well, because screen width - fullscreen window size = 0
    int x = ( screeenDimensions.x - windowDimensions.x ) / 2;
    int y = ( screeenDimensions.y - windowDimensions.y ) / 2;

    resizeWindow( x, y, windowDimensions.x, windowDimensions.y );

    return true;
}

bool Application::resizeWindow( unsigned int x, unsigned int y, unsigned int width, unsigned int height )
{
    // We call set window dim/pos which handles the constraints, then retrieve the constrained values.
    config->GraphicsConfig()->SetWindowDimensions( glm::ivec2( width, height ) );
    int windowWidth = config->GraphicsConfig()->GetWindowWidth();
    int windowHeight = config->GraphicsConfig()->GetWindowHeight();
    int screenWidth = config->GraphicsConfig()->GetScreenWidth();
    int screenHeight = config->GraphicsConfig()->GetScreenHeight();

    config->GraphicsConfig()->SetWindowPosition( glm::ivec2( x, y ) );
    int xPos = config->GraphicsConfig()->GetWindowXPosition();
    int yPos = config->GraphicsConfig()->GetWindowYPosition();
    
    ShowWindow( hWnd, SW_HIDE );
    SetWindowPos( hWnd, HWND_TOP,
                  xPos, yPos,
                  windowWidth,
                  windowHeight,
                  SWP_SHOWWINDOW );
    renderer->resizeViewport( windowWidth, windowHeight );

    ShowWindow( hWnd, SW_SHOW );

    std::stringstream message;
    message << "Resized window to " << windowWidth << "x" << windowHeight << " at position (" << xPos << ", " << yPos << ")";
    logger->Log( LOG_TYPE::INFO, "Resized window", message.str() );

    return true;
}

void Application::shutdownWindow( void )
{
    renderer->Shutdown();

    // If we maximized the window, reset the display back to default
    if( changedResolution == true )
    {
        ChangeDisplaySettings( NULL, 0 );
    }

    // Cleans up the window properly
    DestroyWindow( hWnd );
    UnregisterClass( className.c_str(), hInstance );
    hInstance = NULL;

    logger->Log( LOG_TYPE::INFO, "Window Shutdown", "Window cleanup completed." );
}

void Application::toggleFullscreen( void )
{
    bool wasFullscreen = config->GraphicsConfig()->GetFullscreen();
    config->GraphicsConfig()->SetFullscreen( !wasFullscreen );
    std::string message;
    if( wasFullscreen == false )
    {
        // was fullscreen -> windowed
        resizeWindow( config->GraphicsConfig()->GetScreenWidth(),
                      config->GraphicsConfig()->GetScreenHeight() );
        message = "Switched from fullscreen to windowed mode.";
    }
    else
    {
        // was windowed -> fullscreen
        resizeWindow( config->GraphicsConfig()->GetDefaultWindowWidth(),
                      config->GraphicsConfig()->GetDefaultWindowHeight() );
        message = "Switched from windowed to fullscreen mode.";
    }

    logger->Log( LOG_TYPE::INFO, "Fullscreen toggle", message );
}

bool Application::IsInitialized( void ) const
{
    return initialized;
}

LRESULT CALLBACK Application::WindowProc( HWND handle, UINT message, WPARAM w_param, LPARAM l_param )
{
    unsigned int key_code = 0;
    switch( message )
    {
    case WM_CLOSE:
        PostQuitMessage( 0 );
        return 0;
    case WM_KEYDOWN:
        key_code = static_cast< unsigned int >( w_param );
        if( ( key_code >= 0 ) && ( key_code < 256 ) )
        {
            // On the first keydown
            if( ( l_param & ( 1 << 30 ) ) == 0 )
            {
                keyboard->setKeyPressed( key_code, true);
            }
            
            if( keyboard->IsKeydown(key_code) )
            {
                keyboard->setKeyPressed(key_code, false);
            }

            keyboard->setKeyDown( key_code );
        }
        break;
    case WM_KEYUP:
        key_code = static_cast< unsigned int >( w_param );
        if( ( key_code >= 0 ) && ( key_code < 256 ) )
        {
            keyboard->setKeyUp( key_code );
        }
        break;
    case WM_ACTIVATE:
        if( true == windowInitialized )
        {
            // These lines handle the always-on-top behavior. In other words, if the window is active,
            // then it's at the top of the window Z-order, otherwise it's at the bottom.
            if( true == windowActivated )
            {
                windowActivated = false;
                SetWindowPos( hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
            }
            else
            {
                windowActivated = true;
                SetWindowPos( hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
            }
        }
        break;
    default:
        break;
    }
    return DefWindowProc( handle, message, w_param, l_param );
}
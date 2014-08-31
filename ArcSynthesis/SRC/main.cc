#include <precompiled.h>
#include <application.h>

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmd_line, INT cmd_show )
{
    std::shared_ptr<Application> application = std::make_shared<Application>( L"Redbook Learning" );
    if( application == nullptr )
    {
        MessageBox( NULL, L"Error allocating application", L"UH OH", MB_OK | MB_ICONERROR );
        return -1;
    }

    if( application->Initialize() == false )
    {
        MessageBox( NULL, L"Error initializing application", L"UH OH", MB_OK | MB_ICONERROR );
        return -2;
    }

    application->Run();

    application->Shutdown();


    return 0;
}
#pragma once
#include <precompiled.h>
#include <graphics_configuration.h>
#include <system_configuration.h>

class Configuration
{
public:
    Configuration();

    bool LoadConfiguration( const std::string &set_filename );
    
    std::shared_ptr<GraphicsConfiguration> GraphicsConfig( void );
    std::shared_ptr<SystemConfiguration> SystemConfig( void );

private:
    std::string filename;
    bool isLoaded;
    std::shared_ptr<GraphicsConfiguration> graphicsConfig;
    std::shared_ptr<SystemConfiguration> systemConfig;

    bool loadGraphics(const rapidxml::xml_document<> *xml_doc);
    bool loadSystem(const rapidxml::xml_document<> *xml_doc);
};
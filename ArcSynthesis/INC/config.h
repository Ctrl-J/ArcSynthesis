#pragma once
#include <precompiled.h>
#include <graphics_configuration.h>

class Configuration
{
public:
    Configuration();

    bool LoadConfiguration( const std::string &set_filename );
    
    std::shared_ptr<GraphicsConfiguration> GraphicsConfig( void );

private:
    std::string filename;
    bool isLoaded;
    std::shared_ptr<GraphicsConfiguration> graphics_config;

    bool loadGraphics(const rapidxml::xml_document<> *xml_doc);
};
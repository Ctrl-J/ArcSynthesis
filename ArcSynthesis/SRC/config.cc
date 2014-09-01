#include <precompiled.h>
#include <config.h>

Configuration::Configuration( void )
{
    isLoaded = false;
    graphicsConfig = nullptr;
    systemConfig = nullptr;
}

bool Configuration::LoadConfiguration( const std::string &set_filename )
{
    // if the configuration is already loaded, don't do anything. We're fine.
    if( ( filename.compare( set_filename ) == 0 ) && ( isLoaded == true) )
    {
        return true;
    }

    filename = set_filename;
    rapidxml::file<> *xml_file = new rapidxml::file<>( filename.c_str() );
    rapidxml::xml_document<> *xml_document = new rapidxml::xml_document<>();
    xml_document->parse<0>( xml_file->data() );

    if( loadGraphics( xml_document ) == false )
    {
        isLoaded = false;
        return false;
    }
    
    if( loadSystem( xml_document ) == false )
    {
        isLoaded = false;
        return false;
    }

    isLoaded = true;
    return true;
}

std::shared_ptr<GraphicsConfiguration> Configuration::GraphicsConfig( void )
{
    return graphicsConfig;
}

std::shared_ptr<SystemConfiguration> Configuration::SystemConfig( void )
{
    return systemConfig;
}

bool Configuration::loadGraphics( const rapidxml::xml_document<> *xml_document )
{
    if( xml_document == NULL )
    {
        return false;
    }

    rapidxml::xml_node<> *node = xml_document->first_node( "configuration" );
    if( node == NULL )
    {
        return false;
    }

    node = node->first_node( "graphics" );
    if( node == NULL )
    {
        return false;
    }

    std::string renderer;
    bool fullscreen;
    int width;
    int height;
    bool v_sync;

    std::string node_name;
    std::string node_value;

    for( rapidxml::xml_node<> *property_node = node->first_node(); 
         property_node != NULL; 
         property_node = property_node->next_sibling() )
    {
        node_name = property_node->name();
        node_value = property_node->value();
        if( node_name.compare( "fullscreen" ) == 0 )
        {
            if( node_value.compare( "True" ) == 0 )
            {
                fullscreen = true;
            }
            else
            {
                fullscreen = false;
            }
        }
        else if( node_name.compare( "renderer" ) == 0 )
        {
            renderer = node_value;
        }
        else if( node_name.compare( "width" ) == 0 )
        {
            try
            {
                width = std::stoi( node_value );
            }
            catch( std::invalid_argument )
            {
                width = 800;
            }
        }
        else if( node_name.compare( "height" ) == 0 )
        {
            try
            {
                height = std::stoi( node_value );
            }
            catch( std::invalid_argument )
            {
                height = 480;
            }
        }
        else if( node_name.compare( "vsync" ) == 0 )
        {
            if( node_value.compare( "True" ) == 0 )
            {
                v_sync = true;
            }
            else
            {
                v_sync = false;
            }
        }
    }

    graphicsConfig = std::make_shared<GraphicsConfiguration>
                      ( 
                          renderer,
                          fullscreen,
                          v_sync,
                          glm::ivec2(width, height)
                      );
    return true;
}

bool Configuration::loadSystem( const rapidxml::xml_document<> *xml_doc )
{
    if( xml_doc == NULL )
    {
        return false;
    }

    rapidxml::xml_node<> *node = xml_doc->first_node( "configuration" );
    if( node == NULL )
    {
        return false;
    }

    node = node->first_node( "system" );
    if( node == NULL )
    {
        return false;
    }

    std::string data_folder;
    std::string log_folder;

    std::string node_name;
    std::string node_value;

    for( rapidxml::xml_node<> *property_node = node->first_node(); 
         property_node != NULL; 
         property_node = property_node->next_sibling() )
    {
        node_name = property_node->name();
        node_value = property_node->value();
        if( node_name.compare( "datafolder" ) == 0 )
        {
            data_folder = node_value;
        }
        else if( node_name.compare( "logfolder" ) == 0 )
        {
            log_folder = node_value;
        }

    }

    systemConfig = std::make_shared<SystemConfiguration>
                   ( 
                       data_folder,
                       log_folder
                   );

    return true;
}
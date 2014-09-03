#include <ArcSynth/precompiled.h>
#include <ArcSynth/Config/config.h>
#include <ArcSynth/Config/chapter_data.h>
#include <ArcSynth/OpenGl/shader.h>
#include <ArcSynth/logger.h>

ChapterData::ChapterData( std::shared_ptr<Configuration> config_ptr, std::shared_ptr<Logger> logger_ptr )
{
    config = config_ptr;
    logger = logger_ptr;
    isLoaded = false;
}

bool ChapterData::LoadData( const std::string &set_filename )
{
    if( ( filename.compare( set_filename ) == 0 ) && ( isLoaded == true ) )
    {
        return true;
    }

    filename = config->SystemConfig()->GetDataFolder() + set_filename;
    rapidxml::file<> *xml_file = new rapidxml::file<>( filename.c_str() );
    rapidxml::xml_document<> *xml_document = new rapidxml::xml_document<>();
    xml_document->parse<0>( xml_file->data() );

    if( loadShaders( xml_document ) == false )
    {
        isLoaded = false;
        return false;
    }

    isLoaded = true;
    return true;
}

std::vector<Shader> ChapterData::GetShaders( void )
{
    return shaders;
}

int ChapterData::GetShaderCount( void ) const
{
    return shaders.size();
}


bool ChapterData::loadShaders( const rapidxml::xml_document<> *xml_doc )
{
    if( xml_doc == NULL )
    {
        return false;
    }

    rapidxml::xml_node<> *node = xml_doc->first_node( "data" );
    if( node == NULL )
    {
        return false;
    }

    node = node->first_node( "shaders" );
    if( node == NULL )
    {
        return false;
    }

    std::string shader_name;
    std::string vertex_code;
    std::string fragment_code;

    std::string outer_node_name;
    std::string outer_node_value;
    std::string attribute_name;
    std::string attribute_value;
    std::string inner_node_name;
    std::string inner_node_value;

    for( rapidxml::xml_node<> *shader_set = node->first_node( "shader" );
         shader_set != NULL;
         shader_set = shader_set->next_sibling() )
    {
        outer_node_name = shader_set->name();
        if( outer_node_name.compare( "shader" ) != 0 )
        {
            continue;
        }

        for( rapidxml::xml_attribute<> *property_attribute = shader_set->first_attribute();
             property_attribute != NULL;
             property_attribute = property_attribute->next_attribute() )
        {
            attribute_name = property_attribute->name();
            attribute_value = property_attribute->value();

            if( attribute_name.compare( "Name" ) == 0 )
            {
                shader_name = attribute_value;
            }
        }

        for( rapidxml::xml_node<> *property_node = shader_set->first_node();
             property_node != NULL;
             property_node = property_node->next_sibling() )
        {
            inner_node_name = property_node->name();
            inner_node_value = property_node->value();
            if( inner_node_name.compare( "vertexcode" ) == 0 )
            {
                vertex_code = inner_node_value;
            }
            else if( inner_node_name.compare( "fragmentcode" ) == 0 )
            {
                fragment_code = inner_node_value;
            }
        }

        Shader shader = Shader( logger );
        if( shader.Initialize( shader_name, vertex_code, fragment_code ) == false )
        {
            logger->Log( LOG_TYPE::ERR, "Loading Shaders", "Error loading shader (" + shader_name + ")" );
            logger->Log( LOG_TYPE::INFO, "Vertex Shader Code:\n", shader.GetVertexShaderCode() );
            logger->Log( LOG_TYPE::INFO, "Fragment Shader Code:\n", shader.GetFragmentShaderCode() );
            continue;
        }

        shaders.push_back( shader );
    }

    return true;
}


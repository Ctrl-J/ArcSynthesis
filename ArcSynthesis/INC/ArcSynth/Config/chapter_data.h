#pragma once
#include <ArcSynth/precompiled.h>
#include <ArcSynth/OpenGL/shader.h>

class Configuration;
class Logger;

class ChapterData
{
public:
    ChapterData(std::shared_ptr<Configuration> config_ptr, std::shared_ptr<Logger> logger_ptr );

    bool LoadData( const std::string &set_filename );

    std::vector<Shader> GetShaders( void );
    int GetShaderCount( void ) const;
    
private:
    std::string filename;
    bool isLoaded;

    std::vector<Shader> shaders;

    bool loadShaders(const rapidxml::xml_document<> *xml_doc);

    std::shared_ptr<Configuration> config;
    std::shared_ptr<Logger> logger;
};

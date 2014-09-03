#include <ArcSynth/precompiled.h>
#include <ArcSynth/Config/system_configuration.h>

SystemConfiguration::SystemConfiguration( const std::string &data_folder, const std::string &log_folder )
{
    dataFolder = data_folder;
    logFolder = log_folder;
}

std::string SystemConfiguration::GetDataFolder( void )
{
    return dataFolder;
}

std::string SystemConfiguration::GetLogFolder( void )
{
    return logFolder;
}
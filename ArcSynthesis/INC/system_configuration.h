#pragma once
#include <precompiled.h>

class SystemConfiguration
{
public:
    SystemConfiguration( const std::string &data_folder, const std::string &log_folder );

    std::string GetDataFolder( void );
    std::string GetLogFolder( void );

private:
    std::string dataFolder;
    std::string logFolder;
};

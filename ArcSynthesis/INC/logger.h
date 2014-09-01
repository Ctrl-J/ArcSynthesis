#pragma once
#include <precompiled.h>

enum class LOG_TYPE
{
    INFO = 0,
    WARNING,
    ERR,
    CRITICAL,
    NUM_LOG_TYPES
};

class Logger
{
public:
    Logger();

    void Initialize( const std::string &set_directory, LOG_TYPE minimum_log_level, LOG_TYPE maximum_log_level );
    void Log( LOG_TYPE type, const std::string &title, const std::string &message );

private:

    std::string getTimestamp( void );

    std::string filename;
    LOG_TYPE minLogLevel;
    LOG_TYPE maxLogLevel;
};
#include <ArcSynth/precompiled.h>
#include <ArcSynth/logger.h>

Logger::Logger( void )
{
}

void Logger::Initialize( const std::string &target_directory, LOG_TYPE minimum_log_level, LOG_TYPE maximum_log_level )
{
    filename = target_directory + getTimestamp() + ".log";
    minLogLevel = minimum_log_level;
    maxLogLevel = maximum_log_level;
}

void Logger::Log( LOG_TYPE type, const std::string &title, const std::string &message )
{
    if( ( type < minLogLevel ) || ( type > maxLogLevel ) )
    {
        return;
    }


    std::stringstream output_line;
    output_line << "[";
    switch( type )
    {
    case LOG_TYPE::INFO:
        output_line << "INFO - " << getTimestamp() << "]     ";
        break;
    case LOG_TYPE::WARNING:
        output_line << "WARNING - " << getTimestamp() << "]  ";
        break;
    case LOG_TYPE::ERR:
        output_line << "ERROR - " << getTimestamp() << "]    ";
        break;
    case LOG_TYPE::CRITICAL:
        output_line << "CRITICAL - " << getTimestamp() << "] ";
        break;
    default:
    case LOG_TYPE::NUM_LOG_TYPES:
        output_line << "UNKNOWN - " << getTimestamp() << "]  ";
        break;
    }
    output_line << title << ": " << message;

    std::ofstream file = std::ofstream( filename, std::ios::out | std::ios::app );
    file << output_line.str() << std::endl;
    file.close();
}

std::string Logger::getTimestamp( void )
{
    std::time_t system_time;
    system_time = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
    std::tm time = *std::localtime( &system_time );

    std::stringstream output;
    output << std::put_time( &time, "%Y-%m-%dT%H%M%S" );

    return output.str();
}

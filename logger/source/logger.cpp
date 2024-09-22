#include "logger.h"

namespace logger {

GlobalConfig global_config;

NullOstream null_ostream;
LoggerBase logger_base_null(null_ostream, LoggerConfig());



LoggerBase& logger::Logger::operator<< ( LoggerBase& (*log_manip)(LoggerBase&) ) {
    LoggerBase* base;
    if (LoggerBase::m_config.level <= global_config.level)
        base = this;
    else 
        base = &logger_base_null;
    return *base << (*log_manip);
}

LoggerBase& logger::Logger::operator<< ( std::ostream& (*std_manip)(std::ostream&) ) {
    LoggerBase* base;
    if (LoggerBase::m_config.level <= global_config.level)
        base = this;
    else 
        base = &logger_base_null;
    return *base << (*std_manip);
}

} // namespace logger
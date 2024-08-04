#include "logger.h"

namespace logger {

NullOstream null_ostream;
LoggerBase logger_base_null(Level::none_, null_ostream);

Config global_config;
Level global_level = Level::debug_;

Logger debug(std::cout, Level::debug_);
Logger info (std::cout, Level::info_);
Logger warn (std::cout, Level::warn_);
Logger error(std::cerr, Level::error_);
Logger fatal(std::cerr, Level::fatal_);


LoggerBase& logger::Logger::operator<< ( LoggerBase& (*log_manip)(LoggerBase&) ) {
    LoggerBase* base;
    if (LoggerBase::level <= global_config.level)
        base = this;
    else 
        base = &logger_base_null;
    return *base << (*log_manip);
}

LoggerBase& logger::Logger::operator<< ( std::ostream& (*std_manip)(std::ostream&) ) {
    LoggerBase* base;
    if (LoggerBase::level <= global_config.level)
        base = this;
    else 
        base = &logger_base_null;
    return *base << (*std_manip);
}

} // namespace logger
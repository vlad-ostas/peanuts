#pragma once

#include "logger_base.h"

namespace logger {

/// @brief Global logger config - global log level, enable-disable colors state.
struct GlobalConfig {
    Level level = Level::Debug;
    bool  color = true;
};



/// @brief Null output destination for Logger.
extern LoggerBase logger_base_null;

/// @brief Global logger config - all loggers use this config to format it's output.
extern GlobalConfig global_config;

/// @brief Logger levels logic, checks if global logger level approves this logger and just passes it to it's LoggerBase part.
/// If global logger level disaproves this logger, than all logs go to a null LoggerBase.
class Logger : public LoggerBase {
public:
    Logger()                          = delete;
    Logger(const Logger&)             = delete;
    Logger& operator= (const Logger&) = delete;

    Logger(std::ostream& ostream_, const LoggerConfig& logger_config_) : LoggerBase(ostream_, logger_config_) {}

public:
    LoggerBase& operator<< ( LoggerBase& (*log_manip)(LoggerBase&) );
    LoggerBase& operator<< ( std::ostream& (*std_manip)(std::ostream&) );

    inline Logger& operator<< (const LoggerConfig& new_logger_config) {
        LoggerBase::_config = new_logger_config; 
        return *this;
    }

    template <typename T>
    inline LoggerBase& operator<< (const T& input) {
        LoggerBase* base;
        if (LoggerBase::_config.level <= global_config.level) {
            base = this;
        }
        else 
            base = &logger_base_null;
        return *base << input;
    }
};

} // namespace logger
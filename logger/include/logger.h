#pragma once

#include <iostream>

namespace logger {

/// @brief Log level enumerator, planning to put it into a LoggerConfig structure in future.
enum Level 
    { none_, fatal_, error_, warn_, info_, debug_ };

/// @brief Log level char* array, indexes are compatible with Level enum
const char* const level_name[] = 
    { "none", "fatal", "error", "warning", "info", "debug" };

/// @brief Global logger config - includes log level, coloring state, head fields state, etc.
struct Config {
    Level level = Level::debug_;

    // TODO(Qquookkaa): all functionlity below
    bool color = true;

    bool head_level  = true;    // [warning]
    bool head_date   = true;    // [03.08.2024
    bool head_time   = true;    // 22:41
    bool head_ms     = true;    // .241]
    bool head_thread = true;    // [140113018054400]                    NOTE(Qquookkaa): needs to be passed as a parameter
    bool head_func   = true;    // [void furniture::drawer(scene&)]     NOTE(Qquookkaa): can use __func__
};

/// @brief Global logger config - all loggers use this config to format it's output.
extern Config global_config;



/// @brief NullOstream object is only needed for a logger::none object, so all input goes nowhere.
class NullOstream : public std::ostream {
    class NullBuffer : public std::streambuf {
    public:
        int overflow( int c ) { return c; }
    } null_buffer;
public:
    NullOstream() : std::ostream( &null_buffer ) {}
};

/// @brief Logger base logic, all manipulations here.
class LoggerBase {
protected:
    Level level;

private:
    std::ostream* ostream_ptr;


public:
    LoggerBase()                              = delete;
    LoggerBase(const LoggerBase&)             = delete;
    LoggerBase& operator= (const LoggerBase&) = delete;

    LoggerBase(Level level_, std::ostream& ostream_) : level(level_), ostream_ptr(&ostream_) {}

public:
    inline LoggerBase& operator<< ( LoggerBase& (*log_manip)(LoggerBase&) ) {
        return log_manip(*this);
    }
    
    inline LoggerBase& operator<< ( std::ostream& (*std_manip)(std::ostream&) ) {
        *ostream_ptr << (*std_manip);
        return *this;
    }

    template <typename T>
    inline LoggerBase& operator<< (const T& input) {
        *ostream_ptr << input;
        return *this;
    }

    friend LoggerBase& head(LoggerBase& base);
};



/// @brief Null output destination for Logger.
extern LoggerBase logger_base_null;

/// @brief Logger levels logic, checks if global logger level approves this logger and just passes it to it's LoggerBase part.
/// If global logger level disaproves this logger, than all logger goes to a null LoggerBase.
class Logger : private LoggerBase {
public:
    Logger()                          = delete;
    Logger(const Logger&)             = delete;
    Logger& operator= (const Logger&) = delete;

    Logger(std::ostream& ostream_, Level level_) : LoggerBase(level_, ostream_) {}

public:
    LoggerBase& operator<< ( LoggerBase& (*log_manip)(LoggerBase&) );
    LoggerBase& operator<< ( std::ostream& (*std_manip)(std::ostream&) );

    template <typename T>
    inline LoggerBase& operator<< (const T& input) {
        LoggerBase* base;
        if (LoggerBase::level <= global_config.level) {
            base = this;
        }
        else 
            base = &logger_base_null;
        return *base << input;
    }
};

extern Logger debug;    // defaults: std::cout, level 5 (logger::Level::debug_)
extern Logger info;     // defaults: std::cout, level 4 (logger::Level::info_)
extern Logger warn;     // defaults: std::cout, level 3 (logger::Level::warn_)
extern Logger error;    // defaults: std::cerr, level 2 (logger::Level::error_)
extern Logger fatal;    // defaults: std::cerr, level 1 (logger::Level::fatal_)

} // namespace logger
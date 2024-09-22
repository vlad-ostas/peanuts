#pragma once

#include <iostream>
#include <unordered_map>

namespace logger {

/// @brief Text colors.
enum class Color {
    White,
    Red,
    Orange,
    Yellow,
    Green,
    LightBlue,
    DarkBlue,
    Violet,
    Pink 
};

/// @brief Get text colors as const char*.
inline const char* color_name(Color enum_color) {
    static const char* const color_name[] = {
        "WHITE",
        "RED",
        "ORANGE",
        "YELLOW",
        "GREEN",
        "LIGHT BLUE",
        "DARK BLUE",
        "VIOLET",
        "PINK"
    };

    const char* str_color = color_name[static_cast<size_t>(enum_color)];
    return str_color;
}


/// @brief Log levels enumerator.
enum class Level {
    None,
    Fatal,
    Error,
    Warning,
    Info,
    Debug,
    Verbose
};

/// @brief Get log levels as const char*.
inline const char* level_name(Level enum_level) {
    static const char* const level_name[] = {
        "NONE",
        "FATAL",
        "ERROR",
        "WARNING",
        "INFO",
        "DEBUG",
        "VERBOSE"
    };

    const char* str_level = level_name[static_cast<size_t>(enum_level)];
    return str_level;
}



/// @brief Global logger config - global log level, enable-disable colors state.
struct GlobalConfig {
    Level level = Level::Debug;
    bool  color = true;
};

/// @brief Local logger config - 
struct LoggerConfig {
    Level level      = Level::None;
    Color color      = Color::White;
    bool head_time   = false;    // [03-08-2024 22:41.241]
    bool head_level  = false;    // [WARNING]
    bool head_thread = false;    // [thr 140113018054400]
};



/// @brief NullOstream object is only needed for a logger::none object, so all input goes nowhere.
class NullOstream : public std::ostream {
    class NullBuffer : public std::streambuf {
    public:
        int overflow( int c ) { return c; }
    } null_buffer;
public:
    NullOstream() : std::ostream( &null_buffer ) {}
};

/// @brief Logger base logic, all manipulations and configs here.
class LoggerBase {
public:
    LoggerBase()                              = delete;
    LoggerBase(const LoggerBase&)             = delete;
    LoggerBase& operator= (const LoggerBase&) = delete;

    LoggerBase(std::ostream& ostream_, const LoggerConfig& logger_config_) : m_ostream_ptr(&ostream_), m_config(logger_config_) {}

public:
    inline LoggerBase& operator<< ( LoggerBase& (*log_manip)(LoggerBase&) ) {
        return log_manip(*this);
    }
    
    inline LoggerBase& operator<< ( std::ostream& (*std_manip)(std::ostream&) ) {
        *m_ostream_ptr << (*std_manip);
        return *this;
    }

    template <typename T>
    inline LoggerBase& operator<< (const T& input) {
        *m_ostream_ptr << input;
        return *this;
    }

    inline LoggerBase& operator<< (const LoggerConfig& new_logger_config) {
        m_config = new_logger_config; 
        return *this;
    }

    void print_configuration() const;

    friend LoggerBase& head(LoggerBase& base);

protected:
    LoggerConfig m_config;

private:
    std::ostream* m_ostream_ptr;
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
        LoggerBase::m_config = new_logger_config; 
        return *this;
    }

    template <typename T>
    inline LoggerBase& operator<< (const T& input) {
        LoggerBase* base;
        if (LoggerBase::m_config.level <= global_config.level) {
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
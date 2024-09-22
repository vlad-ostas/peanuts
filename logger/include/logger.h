#pragma once

#include <iostream>

namespace logger {

/// @brief Text colors.
enum Color
    { white, red, orange, yellow, green, l_blue, d_blue, violet, pink };

/// @brief Text colors char* array, indexes are compatible with Color enum.
const char* const color_name[] =
    { "WHITE", "RED", "ORANGE", "YELLOW", "GREEN", "LIGHT BLUE", "DARK BLUE", "VIOLET", "PINK" };

/// @brief Log level enumerator.
enum Level 
    { none_, fatal_, error_, warn_, info_, debug_ };

/// @brief Log level char* array, indexes are compatible with Level enum.
const char* const level_name[] = 
    { "NONE", "FATAL", "ERROR", "WARNING", "INFO", "DEBUG" };



/// @brief Global logger config - global log level, enable-disable colors state.
struct GlobalConfig {
    Level level = Level::debug_;
    bool  color = true;
};

/// @brief Local logger config - 
struct LoggerConfig {
    Level level      = Level::none_;
    Color color      = Color::white;
    bool head_time   = false;    // [03-08-2024 22:41.241]
    bool head_level  = false;    // [WARNING]
    bool head_thread = false;    // [thr 140113018054400]
};

/// @brief Global logger config - all loggers use this config to format it's output.
extern GlobalConfig global_config;

/// @brief Local logger default configs for default loggers.
extern const LoggerConfig defaults_none;
extern const LoggerConfig defaults_debug;
extern const LoggerConfig defaults_info;
extern const LoggerConfig defaults_warn;
extern const LoggerConfig defaults_error;
extern const LoggerConfig defaults_fatal;


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
protected:
    LoggerConfig m_config;

private:
    std::ostream* m_ostream_ptr;

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
};



/// @brief Null output destination for Logger.
extern LoggerBase logger_base_null;

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


// UNICODE ANSI EXIT CODES FOR COLORES

#define LOGGER_ALL_RESET        "\u001b[0m"
#define LOGGER_PAINT_RESET      "\u001b[39m"
#define LOGGER_PAINT_WHITE      "\u001b[37m"
#define LOGGER_PAINT_RED        "\u001b[38;5;196m"
#define LOGGER_PAINT_ORANGE     "\u001b[38;5;208m"
#define LOGGER_PAINT_YELLOW     "\u001b[38;5;226m"
#define LOGGER_PAINT_GREEN      "\u001b[38;5;46m"
#define LOGGER_PAINT_LIGHT_BLUE "\u001b[38;5;51m"
#define LOGGER_PAINT_DARK_BLUE  "\u001b[38;5;20m"
#define LOGGER_PAINT_VIOLET     "\u001b[38;5;93m"
#define LOGGER_PAINT_PINK       "\u001b[38;5;201m"
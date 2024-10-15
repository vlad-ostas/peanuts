#pragma once

#include <iostream>
#include <unordered_map>
#include <thread>

namespace logger {

/// @brief Text colors.
enum class Color { White, Red, Orange, Yellow, Green, LightBlue, DarkBlue, Violet, Pink };

/// @brief Get text colors as const char*.
inline const char* color_name(Color enum_color) {
    static const char* const color_name[] = { "WHITE", "RED", "ORANGE", "YELLOW", "GREEN", "LIGHT BLUE", "DARK BLUE", "VIOLET", "PINK" };

    const char* str_color = color_name[static_cast<size_t>(enum_color)];
    return str_color;
}


/// @brief Log levels enumerator.
enum class Level { None, Fatal, Error, Warning, Info, Debug, Verbose };

/// @brief Get log levels as const char*.
inline const char* level_name(Level enum_level) {
    static const char* const level_name[] = { "NONE", "FATAL", "ERROR", "WARNING", "INFO", "DEBUG", "VERBOSE" };

    const char* str_level = level_name[static_cast<size_t>(enum_level)];
    return str_level;
}



/// @brief Local logger config - insides of LoggerBase.
struct LoggerConfig {
    std::string get_info() const;

public:
    Level level      = Level::None;
    Color color      = Color::White;
    bool head_time   = false;    // [03-08-2024 22:41.241]
    bool head_level  = false;    // [WARNING]
    bool head_thread = false;    // [thr 140113018054400]
};



/// @brief NullOstream object is needed for a logger::none object, so all input goes nowhere.
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

    LoggerBase(std::ostream& ostream_, const LoggerConfig& logger_config_) : _ostream_ptr(&ostream_), _config(logger_config_) {}

public:
    inline LoggerBase& operator<< ( LoggerBase& (*log_manip)(LoggerBase&) ) {
        return log_manip(*this);
    }
    
    inline LoggerBase& operator<< ( std::ostream& (*std_manip)(std::ostream&) ) {
        *_ostream_ptr << (*std_manip);
        return *this;
    }

    template <typename T>
    inline LoggerBase& operator<< (const T& input) {
        *_ostream_ptr << input;
        return *this;
    }

    inline LoggerBase& operator<< (const LoggerConfig& new_logger_config) {
        _config = new_logger_config; 
        return *this;
    }

    inline void print_configuration() const {
        *_ostream_ptr << _config.get_info();
    }

    friend LoggerBase& set_color    (LoggerBase& base);
    friend LoggerBase& head_time    (LoggerBase& base);
    friend LoggerBase& head_level   (LoggerBase& base);
    friend LoggerBase& head_thread  (LoggerBase& base);
    friend LoggerBase& head         (LoggerBase& base);

protected:
    LoggerConfig _config;

private:
    std::ostream* _ostream_ptr;
};

}   // namespace logger
#include "logger.h"

namespace logger {

// struct LoggerConfig            { Level level,    Color color,    bool head_time,  bool head_level,  bool head_thread };
const LoggerConfig defaults_none  { Level::none_ ,  Color::white ,  false,           false,            false            };
const LoggerConfig defaults_debug { Level::debug_,  Color::white ,  true,            true,             true             };
const LoggerConfig defaults_info  { Level::info_ ,  Color::green ,  true,            true,             true             };
const LoggerConfig defaults_warn  { Level::warn_ ,  Color::yellow,  true,            true,             true             };
const LoggerConfig defaults_error { Level::error_,  Color::orange,  true,            true,             true             };
const LoggerConfig defaults_fatal { Level::fatal_,  Color::red   ,  true,            true,             true             };

GlobalConfig global_config;



Logger debug(std::cout, defaults_debug);
Logger info (std::cout, defaults_info);
Logger warn (std::cout, defaults_warn);
Logger error(std::cerr, defaults_error);
Logger fatal(std::cerr, defaults_fatal);

NullOstream null_ostream;
LoggerBase logger_base_null(null_ostream, defaults_none);



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

void LoggerBase::print_configuration() const {
    if (m_config.level > global_config.level) {
        return;
    }
    *m_ostream_ptr << "Level:\t\t" << level_name(m_config.level) << '\n'
                 << "Color:\t\t" << color_name(m_config.color) << '\n'
                 << "Head time:\t"   << ((m_config.head_time)   ? "ON" : "OFF") << '\n'
                 << "Head level:\t"  << ((m_config.head_level)  ? "ON" : "OFF") << '\n'
                 << "Head thread:\t" << ((m_config.head_thread) ? "ON" : "OFF") << std::endl;
}

} // namespace logger

// struct LoggerConfig {
//     Level level      = Level::none_;
//     Color color      = Color::white;
//     bool head_level  = false;    // [WARNING]
//     bool head_time   = false;    // [03-08-2024 22:41.241]
//     bool head_thread = false;    // [thr 140113018054400]
// };
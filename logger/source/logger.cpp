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
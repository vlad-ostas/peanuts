#include "manipulator.h"

#include <chrono>
#include <thread>

namespace logger{

LoggerBase& head(LoggerBase& base) {
    if (global_config.color) 
        switch (base.m_config.color)
        {
        case Color::white:
            base << LOGGER_PAINT_WHITE;      break;
        case Color::red:
            base << LOGGER_PAINT_RED;        break;
        case Color::orange:
            base << LOGGER_PAINT_ORANGE;     break;
        case Color::yellow:
            base << LOGGER_PAINT_YELLOW;     break;
        case Color::green:
            base << LOGGER_PAINT_GREEN;      break;
        case Color::l_blue:
            base << LOGGER_PAINT_LIGHT_BLUE; break;
        case Color::d_blue:
            base << LOGGER_PAINT_DARK_BLUE;  break;
        case Color::violet:
            base << LOGGER_PAINT_VIOLET;     break;
        case Color::pink:
            base << LOGGER_PAINT_PINK;       break;
        }

    if (base.m_config.head_time) {
        base << "[" << std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()} << "] ";
    }

    if (base.m_config.head_level) {
        base << "[" << level_name[base.m_config.level] << "] ";
    }

    if (base.m_config.head_thread) {
        base << "[thr " << std::this_thread::get_id() << "] ";
    }

    return base;
}

LoggerBase& endl(LoggerBase& base) {
    base << LOGGER_ALL_RESET << std::endl;
    return base;
}

} // namespace logger
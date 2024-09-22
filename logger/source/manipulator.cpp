#include "manipulator.h"
#include "format.h"

#include <chrono>
#include <thread>

namespace logger{

LoggerBase& head(LoggerBase& base) {
    if (global_config.color) 
        switch (base.m_config.color)
        {
        case Color::White:
            base << LOGGER_PAINT_WHITE;
            break;
        case Color::Red:
            base << LOGGER_PAINT_RED;
            break;
        case Color::Orange:
            base << LOGGER_PAINT_ORANGE;
            break;
        case Color::Yellow:
            base << LOGGER_PAINT_YELLOW;
            break;
        case Color::Green:
            base << LOGGER_PAINT_GREEN;
            break;
        case Color::LightBlue:
            base << LOGGER_PAINT_LIGHT_BLUE;
            break;
        case Color::DarkBlue:
            base << LOGGER_PAINT_DARK_BLUE;
            break;
        case Color::Violet:
            base << LOGGER_PAINT_VIOLET;
            break;
        case Color::Pink:
            base << LOGGER_PAINT_PINK;
            break;
        default:
            break;
        }

    if (base.m_config.head_time) {
        base << "[" << std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()} << "] ";  // TODO: make configurable, make code clean
    }

    if (base.m_config.head_level) {
        base << "[" << level_name(base.m_config.level) << "] ";
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
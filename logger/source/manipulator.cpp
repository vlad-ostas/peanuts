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
            base << format::ANSI::white;
            break;
        case Color::Red:
            base << format::ANSI::red;
            break;
        case Color::Orange:
            base << format::ANSI::orange;
            break;
        case Color::Yellow:
            base << format::ANSI::yellow;
            break;
        case Color::Green:
            base << format::ANSI::green;
            break;
        case Color::LightBlue:
            base << format::ANSI::light_blue;
            break;
        case Color::DarkBlue:
            base << format::ANSI::dark_blue;
            break;
        case Color::Violet:
            base << format::ANSI::violet;
            break;
        case Color::Pink:
            base << format::ANSI::pink;
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
    base << format::ANSI::reset_all << std::endl;
    return base;
}

} // namespace logger
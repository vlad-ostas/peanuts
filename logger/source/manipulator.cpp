#include "manipulator.h"

#include "format.h"

#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>

namespace logger {

namespace {
    std::string color_exit_code(Color color_enum) {
        std::string answer;
        switch (color_enum)
        {
        case Color::White:
            answer = format::ANSI::white;
            break;
        case Color::Red:
            answer = format::ANSI::red;
            break;
        case Color::Orange:
            answer = format::ANSI::orange;
            break;
        case Color::Yellow:
            answer = format::ANSI::yellow;
            break;
        case Color::Green:
            answer = format::ANSI::green;
            break;
        case Color::LightBlue:
            answer = format::ANSI::light_blue;
            break;
        case Color::DarkBlue:
            answer = format::ANSI::dark_blue;
            break;
        case Color::Violet:
            answer = format::ANSI::violet;
            break;
        case Color::Pink:
            answer = format::ANSI::pink;
            break;
        default:
            break;
        }

        return answer;
    }
}

LoggerBase& set_color(LoggerBase& base) {
    if (global_config.color) {
        base << color_exit_code(base.m_config.color);
    }

    return base;
}


LoggerBase& reset_color(LoggerBase& base) {
    if (global_config.color) {
        base << format::ANSI::reset_color;
    }
    return base;
}

LoggerBase& head_time(LoggerBase& base) {
    std::stringstream message;

    if (base.m_config.head_time) {
        message << "[" << std::setw(33) << std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()} << "]";  // TODO: make configurable, make code clean   TODO: Make auto-generating size numbers
    }

    base << std::move(message).str();
    return base;
}

LoggerBase& head_level(LoggerBase& base) {
    std::stringstream message;

    if (base.m_config.head_level) {
        message << "[";

        if (global_config.color) {
            message << color_exit_code(base.m_config.color) << std::setw(7) << level_name(base.m_config.level) << format::ANSI::reset_color;
        }
        else {
            message << std::setw(7) << level_name(base.m_config.level);
        }

        message << "]";
    }

    base << std::move(message).str();
    return base;
}

LoggerBase& head_thread(LoggerBase& base) {
    std::stringstream message;

    if (base.m_config.head_thread) {
        message << "[thr " << std::setw(6) << std::this_thread::get_id() << "]";
    }

    base << std::move(message).str();
    return base;
}

LoggerBase& head(LoggerBase& base) {
    base << head_time << head_level << head_thread << ' ';
    return base;
}


LoggerBase& endl(LoggerBase& base) {
    base << format::ANSI::reset_all << std::endl;
    return base;
}

} // namespace logger
#pragma once

#include "logger.h"

namespace logger {

// struct LoggerConfig            { Level level,    Color color,    bool head_time,  bool head_level,  bool head_thread };
const LoggerConfig defaults_none  { Level::None,    Color::White,   false,           false,            false            };
const LoggerConfig defaults_debug { Level::Debug,   Color::White,   true,            true,             true             };
const LoggerConfig defaults_info  { Level::Info,    Color::Green,   true,            true,             true             };
const LoggerConfig defaults_warn  { Level::Warning, Color::Yellow,  true,            true,             true             };
const LoggerConfig defaults_error { Level::Error,   Color::Orange,  true,            true,             true             };
const LoggerConfig defaults_fatal { Level::Fatal,   Color::Red,     true,            true,             true             };

Logger debug  (std::cout, defaults_debug);
Logger info   (std::cout, defaults_info);
Logger warning(std::cout, defaults_warn);
Logger error  (std::cerr, defaults_error);
Logger fatal  (std::cerr, defaults_fatal);

}   // namespace logger
#pragma once

#include "logger.h"


namespace logger {

extern const LoggerConfig defaults_none;
extern const LoggerConfig defaults_verbose;
extern const LoggerConfig defaults_debug;
extern const LoggerConfig defaults_info;
extern const LoggerConfig defaults_warn;
extern const LoggerConfig defaults_error;
extern const LoggerConfig defaults_fatal;

extern Logger verbose;  // defaults: std::cout, level 6 (logger::Level::Verbose)
extern Logger debug;    // defaults: std::cout, level 5 (logger::Level::Debug)
extern Logger info;     // defaults: std::cout, level 4 (logger::Level::Info)
extern Logger warning;  // defaults: std::cout, level 3 (logger::Level::Warning)
extern Logger error;    // defaults: std::cerr, level 2 (logger::Level::Error)
extern Logger fatal;    // defaults: std::cerr, level 1 (logger::Level::Fatal)

}   // namespace logger
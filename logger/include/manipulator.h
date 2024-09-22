#pragma once

#include "logger.h"

#include <string>

namespace logger {

/// @brief Print head info log, example: "[warning][03.08.2024 22:41:34.241][thread 140113018054400]"
/// @param base source object
/// @return Source object
LoggerBase& head(LoggerBase& base);

/// @brief Put endline symbols (ANSI color codes) and send std::cout manipulator to ostream
/// @param base source object
/// @return Source object
LoggerBase& endl(LoggerBase& base);

} // namespace logger



// constexpr const char* cut_file_name(const char* path) {
//     const char* file = path;
//     while (*path++) {
//         if (*path == '/' || *path == '\\') {
//             file = path + 1;
//         }
//     }
//     return file;
// }

// #define LOGGER_CALL_FUNCTION (std::string("[") + __builtin_FUNCTION() + "] ")
// #define LOGGER_CALL_LINE     (std::string("[") + cut_file_name(__builtin_FILE()) + ":" + std::to_string(__builtin_LINE()) + "] ")

// #define STATIC_HEAD LOGGER_CALL_FUNCTION << LOGGER_CALL_LINE 

// #define DEBUG_MSG   logger::debug << logger::head << STATIC_HEAD
// #define INFO_MSG    logger::info  << logger::head << STATIC_HEAD 
// #define WARN_MSG    logger::warn  << logger::head << STATIC_HEAD 
// #define ERROR_MSG   logger::error << logger::head << STATIC_HEAD
// #define FATAL_MSG   logger::fatal << logger::head << STATIC_HEAD
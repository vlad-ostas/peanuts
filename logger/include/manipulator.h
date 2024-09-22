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



/* Next definitions help you get external debug info like function names and source file with line number. Next code example shall explain:
CODE:                                                                                                       RESULT:
logger::debug << "Some logger message, using only logger" << std::endl;                                     Some logger message, using only logger
logger::debug << STATIC_HEAD << "Some logger message, using logger with STATIC_HEAD define" << std::endl;   [main] [D:\Coding\Projects\peanuts\logger\test\test.cpp 11] Some logger message, using logger with STATIC_HEAD define
logger::debug << logger::head << "Some logger message, using logger with head manipulator" << std::endl;    [2024-08-10 14:05:16.714] [DEBUG] [thr 8900] Some logger message, using logger with head manipulator
DEBUG_MSG << "Some logger message, using DEBUG_MSG define" << std::endl;                                    [2024-08-10 14:05:16.714] [DEBUG] [thr 8900] [main] [D:\Coding\Projects\peanuts\logger\test\test.cpp 11] Some logger message, using DEBUG_MSG define
*/

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
#pragma once

#include "logger.h"

#include <string>

namespace logger {

/// @brief Put std::endl into a target std::ostream object
/// @param base source object
/// @return Source object
inline LoggerBase& endl(LoggerBase& base) {
    base << std::endl;
    return base;
}

/// @brief Print head info log, example: "[warning][03.08.2024 22:41:34.241][thread 140113018054400]"
/// @param base source object
/// @return Source object
LoggerBase& head(LoggerBase& base);

} // namespace logger

#define LOGGER_CALL_FUNCTION (logger::global_config.head_func ? (std::string("[") + __builtin_FUNCTION()                                      + "]") : std::string())
#define LOGGER_CALL_LINE     (logger::global_config.head_func ? (std::string("[") + __builtin_FILE() + " " + std::to_string(__builtin_LINE()) + "]") : std::string())

#define DEBUG_MSG   logger::debug << logger::head << LOGGER_CALL_FUNCTION << LOGGER_CALL_LINE << " >>> "
#define INFO_MSG    logger::info  << logger::head << LOGGER_CALL_FUNCTION << LOGGER_CALL_LINE << " >>> "
#define WARN_MSG    logger::warn  << logger::head << LOGGER_CALL_FUNCTION << LOGGER_CALL_LINE << " >>> "
#define ERROR_MSG   logger::error << logger::head << LOGGER_CALL_FUNCTION << LOGGER_CALL_LINE << " >>> "
#define FATAL_MSG   logger::fatal << logger::head << LOGGER_CALL_FUNCTION << LOGGER_CALL_LINE << " >>> "
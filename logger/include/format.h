#pragma once

namespace logger {
namespace format {

// UNICODE ANSI EXIT CODES FOR COLORES

// #define LOGGER_PAINT_RESET      "\u001b[39m"
// #define LOGGER_PAINT_WHITE      "\u001b[37m"
// #define LOGGER_PAINT_RED        "\u001b[38;5;196m"
// #define LOGGER_PAINT_ORANGE     "\u001b[38;5;208m"
// #define LOGGER_PAINT_YELLOW     "\u001b[38;5;226m"
// #define LOGGER_PAINT_GREEN      "\u001b[38;5;46m"
// #define LOGGER_PAINT_LIGHT_BLUE "\u001b[38;5;51m"
// #define LOGGER_PAINT_DARK_BLUE  "\u001b[38;5;20m"
// #define LOGGER_PAINT_VIOLET     "\u001b[38;5;93m"
// #define LOGGER_PAINT_PINK       "\u001b[38;5;201m"

// #define LOGGER_ALL_RESET        "\u001b[0m"

namespace ANSI {

const char* const reset_color   = "\u001b[39m";
const char* const white         = "\u001b[37m";
const char* const red           = "\u001b[38;5;196m";
const char* const orange        = "\u001b[38;5;208m";
const char* const yellow        = "\u001b[38;5;226m";
const char* const green         = "\u001b[38;5;46m";
const char* const light_blue    = "\u001b[38;5;51m";
const char* const dark_blue     = "\u001b[38;5;20m";
const char* const violet        = "\u001b[38;5;93m";
const char* const pink          = "\u001b[38;5;201m";

const char* const reset_all     = "\u001b[0m";

}   // namespace ANSI

}   // namespace format
}   // namespace logger
#include "logger.h"
#include "manip.h"

void show_log_levels() {
    std::cout << "Show logger levels, current global logger level is " << logger::level_name[logger::global_config.level] << std::endl;

    DEBUG_MSG << "Debug message" << logger::endl;
    INFO_MSG  << "Info message"  << logger::endl;
    WARN_MSG  << "Warn message"  << logger::endl;
    ERROR_MSG << "Error message" << logger::endl;
    FATAL_MSG << "Fatal message" << logger::endl;
}



int main()
{

    // LOG LEVELS, ENDL, HEAD
    const logger::Level log_level_array [] = {
        logger::Level::none_,
        logger::Level::fatal_,
        logger::Level::error_,
        logger::Level::warn_,
        logger::Level::info_,
        logger::Level::debug_
    };

    for (auto cur_level : log_level_array) {
        logger::global_config.level = cur_level;
        show_log_levels();
    }

    DEBUG_MSG << "Hi!" << logger::endl;

    // GLOBAL CONFIG, LOCAL CONFIGS



    // COLORS

    

    return 0;
}
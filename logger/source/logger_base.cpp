#include "logger_base.h"

namespace logger {

std::string LoggerConfig::get_info() const {
    std::string answer;
    answer = std::string() + "Level:\t\t" + level_name(level) + '\n'
        + "Color:\t\t" + color_name(color) + '\n'
        + "Head time:\t"   + ((head_time)   ? "ON" : "OFF") + '\n'
        + "Head level:\t"  + ((head_level)  ? "ON" : "OFF") + '\n'
        + "Head thread:\t" + ((head_thread) ? "ON" : "OFF") + '\n';

    return answer;
}

}   // namespace logger
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

std::ostringstream& LoggerBase::get_current_log_buffer() {
    std::lock_guard lock(_buf_mtx);

    if (auto current_log_buffer_it = _log_buffers.find(std::this_thread::get_id()); 
        current_log_buffer_it != _log_buffers.end()) {
        return current_log_buffer_it->second;
    }

    auto emplace_result = _log_buffers.emplace( std::this_thread::get_id(), std::ostringstream() );

    if (!emplace_result.second) {
        throw std::runtime_error("couldn't create log buffer for current thread");  // TODO: get rid of exceptions inside logger
    }

    return emplace_result.first->second;
}

NullOstream null_ostream;

}   // namespace logger
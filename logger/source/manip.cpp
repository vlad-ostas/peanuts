#include "manip.h"

#include <chrono>
#include <thread>

namespace logger{

// TODO(Qquookkaa): need to make logger::head work, now it's just an imitation

inline std::string date() {
    std::string res("03.08.2024 ");
    return res;
}
inline std::string time() {
    std::string res("22:41:34");
    return res;
}
inline std::string ms() {
    std::string res(".241");
    return res;
}

LoggerBase& head(LoggerBase& base) {
    if (global_config.head_date || global_config.head_time || global_config.head_ms) {
        base << '[';

        auto cur_time = std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()};
        base << cur_time;

        // if (global_config.head_date)
        //     base << date();
        // if (global_config.head_time)
        //     base << time();
        // if (global_config.head_ms)
        //     base << ms();

        base << ']';
    }

    if (global_config.head_level) {
        base << '[' << level_name[base.level] << ']';
    }

    if (global_config.head_thread) {
        base << "[thr_id " << std::this_thread::get_id() << ']';
    }

    return base;
}

} // namespace logger
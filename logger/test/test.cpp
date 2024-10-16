#include "logger.h"
#include "manipulator.h"
#include "preset.h"

#include <thread>
#include <vector>

void log_all_levels() {
    logger::verbose << logger::head << "Verbose message" << logger::endl;
    logger::debug   << logger::head << "Debug message"   << logger::endl;
    logger::info    << logger::head << "Info message"    << logger::endl;
    logger::warning << logger::head << "Warn message"    << logger::endl;
    logger::error   << logger::head << "Error message"   << logger::endl;
    logger::fatal   << logger::head << "Fatal message"   << logger::endl;
}

const logger::Level log_level_array [] = {
    logger::Level::None,
    logger::Level::Fatal,
    logger::Level::Error,
    logger::Level::Warning,
    logger::Level::Info,
    logger::Level::Debug,
    logger::Level::Verbose
};


int main()
{
    std::cout << "\n==========LOG LEVELS===========" << std::endl;

    for (auto cur_level : log_level_array) {
        // logger::global_config.level = cur_level;
        logger::global_config.level = logger::Level::Verbose;

        std::cout << "\tCurrent log level is " << logger::level_name(cur_level) << ":" << std::endl;
        log_all_levels();
    }

    std::cout << "\n=======SWITCHING COLORS========" << std::endl;
    {
        logger::global_config.color = false;

        std::cout << "\tTurned log colors OFF:" << std::endl;
        log_all_levels();

        logger::global_config.color = true;

        std::cout << "\tTurned log colors ON:" << std::endl;
        log_all_levels();
    }

    std::cout << "\n=========LOGGER CONFIG=========" << std::endl;
    {
        std::cout << "Current logger::info configuration:" << std::endl;
        logger::info.print_configuration();
        logger::info << logger::head << "Example message here" << logger::endl;


        logger::LoggerConfig new_debug_config = {
            logger::Level::Info,
            logger::Color::Pink,
            false,
            false,
            false,
        };

        logger::info << new_debug_config;

        std::cout << "New logger::info configuration:" << std::endl;
        logger::info.print_configuration();
        logger::info << logger::head << "Example message here" << logger::endl;
    }

    std::cout << "\n=========MULTITHREADING========" << std::endl;
    {
        constexpr size_t THREAD_NUMBER = 4;
        constexpr size_t INPUT_NUMBER = 50;

        std::vector<std::thread> thr_vec;
        thr_vec.reserve(THREAD_NUMBER);

        for (size_t i = 0; i < THREAD_NUMBER; i++) {
            thr_vec.emplace_back([&](){
                for (size_t k = 0; k < INPUT_NUMBER; k++) {
                    logger::debug << std::this_thread::get_id();
                    // std::cout << std::this_thread::get_id();
                } 
                logger::debug << logger::endl;
                // std::cout << std::endl;
            });
        }

        for (size_t i = 0; i < THREAD_NUMBER; i++) {
            thr_vec[i].join();
        }
    }
    {
        constexpr size_t THREAD_NUMBER = 4;
        constexpr size_t INPUT_NUMBER = 50;

        std::vector<std::thread> thr_vec;
        thr_vec.reserve(THREAD_NUMBER);

        for (size_t i = 0; i < THREAD_NUMBER; i++) {
            thr_vec.emplace_back([&](){
                for (size_t k = 0; k < INPUT_NUMBER; k++) {
                    std::cout << std::this_thread::get_id();
                } 
                std::cout << std::endl;
            });
        }

        for (size_t i = 0; i < THREAD_NUMBER; i++) {
            thr_vec[i].join();
        }
    }

    return 0;
}
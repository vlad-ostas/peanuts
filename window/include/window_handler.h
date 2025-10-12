#pragma once

#include <cstdint>
#include <GLFW/glfw3.h>
#include <memory>


namespace settings
{
static constexpr unsigned int SCR_WIDTH  = 800;
static constexpr unsigned int SCR_HEIGHT = 600;
} // settings
//

// class WindowHandlerSingletone
// {
// public:
//     static WindowHandlerSingletone& getInstance()
//     {
//         static WindowHandlerSingletone instance;
//         return instance;
//     }
//
//     WindowHandlerSingletone(WindowHandlerSingletone const&) = delete;
//     void operator=(WindowHandlerSingletone const&) = delete;
// private:
//     WindowHandlerSingletone() = default;
// };

class WindowHandler
{
public:
    WindowHandler();
    WindowHandler(int32_t width, int32_t height);
    WindowHandler(int32_t width, int32_t height, GLFWframebuffersizefun callback);

    [[nodiscard]] std::shared_ptr<GLFWwindow> get_window_handler() const;

private:
    bool Initialize(int32_t width, int32_t height, GLFWframebuffersizefun callback);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    static const std::shared_ptr<GLFWwindow> m_window;
};

#pragma once

#include <cstdint>
#include <GLFW/glfw3.h>


namespace settings
{
static constexpr unsigned int SCR_WIDTH  = 800;
static constexpr unsigned int SCR_HEIGHT = 600;
} // settings

class WindowHandler
{
public:
    WindowHandler();
    WindowHandler(int32_t width, int32_t height);
    WindowHandler(int32_t width, int32_t height, GLFWframebuffersizefun callback);

    const GLFWwindow* get_window_handler() const;

private:
    bool Initialize(int32_t width, int32_t height, GLFWframebuffersizefun callback);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    static GLFWwindow* m_window;
};

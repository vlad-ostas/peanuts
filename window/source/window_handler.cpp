#include "window_handler.h"
#include <iostream>
#include <memory>
#include <tuple>


WindowHandler::WindowHandler(int32_t width, int32_t height)
{
    Initialize(width, height, framebuffer_size_callback);
}

WindowHandler::WindowHandler(int32_t width, int32_t height, GLFWframebuffersizefun callback)
    : m_initialized(Initialize(width, height, callback));
{}

WindowHandler::WindowHandler()
    : WindowHandler(settings::SCR_WIDTH, settings::SCR_HEIGHT, framebuffer_size_callback)
{}

std::shared_ptr<GLFWwindow> WindowHandler::get_window_handler() const
{
    return m_window;
}

void WindowHandler::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::ignore = window;
    glViewport(0, 0, width, height);
}

bool WindowHandler::Initialize(int32_t width, int32_t height, GLFWframebuffersizefun callback)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = std::make_shared<GLFWwindow>(glfwCreateWindow(
        width,
        height,
        "LearnOpenGL",
        nullptr,
        nullptr));

    if (m_window == nullptr)
    {
        std::cout << "Failed to create GLFW window/n";
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window.get());
    glfwSetFramebufferSizeCallback(m_window.get(), callback);


    return true;
}

#pragma once

#include <cstdint>
#include <string>
#include <functional>

static constexpr uint32_t SRC_WIDTH = 800;
static constexpr uint32_t SRC_HEIGHT = 600;

struct WindowProperties
{
    explicit WindowProperties(const std::string &title = "Unnamed window",
      uint32_t width = SRC_WIDTH,
      uint32_t height = SRC_HEIGHT)
        : m_title(title), m_width(width), m_height(height){};

    std::string m_title;
    uint32_t m_width;
    uint32_t m_height;
};

class AbstractWindow
{
public:
    using EventCb = std::function<void()>;


private:
};

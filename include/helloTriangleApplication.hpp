#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

class HelloTriangeApplication
{
public:
    static constexpr uint32_t WIN_WIDTH{800};
    static constexpr uint32_t WIN_HEIGHT{600};

    void run();

    ~HelloTriangeApplication();

private:
    void initWindow();
    void initVulkan();
    void createInstance();
    void mainLoop();

    std::vector<VkExtensionProperties> enumerateExtensions();
    bool isInVkExtensions(uint32_t count, const char **names, std::vector<VkExtensionProperties> extensions);

private:
    GLFWwindow *m_window;
    VkInstance m_vk_instance;
};
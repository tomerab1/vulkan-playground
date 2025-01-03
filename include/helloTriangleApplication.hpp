#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <optional>

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphcsFamily;
};

class HelloTriangeApplication
{
public:
    static constexpr uint32_t WIN_WIDTH{800};
    static constexpr uint32_t WIN_HEIGHT{600};
    static constexpr std::array<const char *, 1> validationLayers{"VK_LAYER_KHRONOS_validation"};

    void run();

    ~HelloTriangeApplication();

private:
    void initWindow();
    void initVulkan();
    void createInstance();
    void pickPhysicalDevice();
    void mainLoop();

    std::vector<VkExtensionProperties> enumerateExtensions();
    bool isInVkExtensions(const std::vector<const char *> &glfwExtensions, std::vector<VkExtensionProperties> vkExtensions);

    std::vector<VkLayerProperties> enumerateLayers();
    bool isValidationLayerSupported();

    std::vector<const char *> enumerateGlfwExtensions();

    std::vector<VkPhysicalDevice> enumeratePhysicalDevices();
    bool isDeviceSuitable(const VkPhysicalDevice &device);
    void pickBestPhysicalDevice(const std::vector<VkPhysicalDevice> &devices);
    int ratePhysicalDevice(const VkPhysicalDevice &device);

private:
    GLFWwindow *m_window;
    VkInstance m_vk_instance;
    VkPhysicalDevice m_phyDevice{VK_NULL_HANDLE};

#ifdef NDEBUG
    const bool enableValidationLayers{false};
#else
    const bool enableValidationLayers{true};
#endif
};
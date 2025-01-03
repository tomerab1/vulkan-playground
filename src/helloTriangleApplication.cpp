#include "helloTriangleApplication.hpp"

#include "dbg_logger.hpp"

#include <sstream>
#include <fmt/format.h>
#include <stdexcept>
#include <algorithm>

void HelloTriangeApplication::run()
{
    initWindow();
    initVulkan();
    mainLoop();
}

void HelloTriangeApplication::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Vulkan", nullptr, nullptr);

    if (!m_window)
    {
        throw std::runtime_error("Error: Could not create window");
    }
}

void HelloTriangeApplication::initVulkan()
{
    createInstance();
    pickPhysicalDevice();
}

void HelloTriangeApplication::createInstance()
{
    if (enableValidationLayers && !isValidationLayerSupported())
    {
        throw std::runtime_error("Error: validation layers requested, but not available!");
    }

    auto availExtensions = enumerateExtensions();
    auto glfwExtensions = enumerateGlfwExtensions();

    if (!isInVkExtensions(glfwExtensions, std::move(availExtensions)))
    {
        throw std::runtime_error("Error: Some of the glfw extensions are not supported by vulkan");
    }

    dbglog_info("{}", "Vulkan support all of GLFW extensions");

    VkApplicationInfo info{};
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName = "Hello Triangle";
    info.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
    info.pEngineName = "No Engine";
    info.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
    info.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &info;

    createInfo.enabledExtensionCount = glfwExtensions.size();
    createInfo.ppEnabledExtensionNames = glfwExtensions.data();

    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateInstance(&createInfo, nullptr, &m_vk_instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Error: Failed to create VkInstance");
    }

    dbglog_info("{}", "VkInstance created successfuly");
}

void HelloTriangeApplication::pickPhysicalDevice()
{
    const auto devices = enumeratePhysicalDevices();

    if (devices.size() == 0)
    {
        throw std::runtime_error("Error: Failed to find GPUs with Vulkan support");
    }
}

void HelloTriangeApplication::mainLoop()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
    }
}

std::vector<VkExtensionProperties> HelloTriangeApplication::enumerateExtensions()
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    std::stringstream ss;

    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    ss << "\nSupported extensions:\n";
    for (const auto &ex : extensions)
    {
        ss << "\t" << ex.extensionName << ":v" << ex.specVersion << '\n';
    }

    dbglog_info("{}", ss.str());
    return extensions;
}

bool HelloTriangeApplication::isInVkExtensions(const std::vector<const char *> &glfwExtensions, std::vector<VkExtensionProperties> vkExtensions)
{
    for (const auto &glfwExtension : glfwExtensions)
    {
        bool isFound{false};

        for (const auto &vkExtension : vkExtensions)
        {
            if (std::strcmp(vkExtension.extensionName, glfwExtension) == 0)
            {
                isFound = true;
                break;
            }
        }

        if (!isFound)
            return false;
    }

    return true;
}

std::vector<VkLayerProperties> HelloTriangeApplication::enumerateLayers()
{
    uint32_t layersCount{0};
    vkEnumerateInstanceLayerProperties(&layersCount, nullptr);
    std::vector<VkLayerProperties> layers(layersCount);
    std::stringstream ss;

    vkEnumerateInstanceLayerProperties(&layersCount, layers.data());

    ss << "\nSupported layers:\n";
    for (const auto &l : layers)
    {
        ss << "\t" << l.layerName << ":v" << l.specVersion << '\n';
    }

    dbglog_info("{}", ss.str());

    vkEnumerateInstanceLayerProperties(&layersCount, layers.data());
    return layers;
}

bool HelloTriangeApplication::isValidationLayerSupported()
{
    auto layers = enumerateLayers();

    for (const auto &requiredLayer : validationLayers)
    {
        bool isLayerFound{false};

        for (const auto &layer : layers)
        {
            if (std::strcmp(layer.layerName, requiredLayer) == 0)
            {
                isLayerFound = true;
                break;
            }
        }

        if (!isLayerFound)
            return false;
    }

    return true;
}

std::vector<const char *> HelloTriangeApplication::enumerateGlfwExtensions()
{
    uint32_t count{0};
    const auto **extensions = glfwGetRequiredInstanceExtensions(&count);
    std::stringstream ss;

    ss << "\nSupported glfw extensions:\n";
    for (std::size_t i{0}; i < count; i++)
    {
        ss << '\t' << extensions[i] << '\n';
    }

    dbglog_info("{}", ss.str());

    return std::vector<const char *>(extensions, extensions + count);
}

std::vector<VkPhysicalDevice> HelloTriangeApplication::enumeratePhysicalDevices()
{
    uint32_t deviceCount{0};
    vkEnumeratePhysicalDevices(m_vk_instance, &deviceCount, nullptr);

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_vk_instance, &deviceCount, devices.data());

    std::stringstream ss;

    ss << "\nAvailable physical devices:\n";
    VkPhysicalDeviceProperties props;
    for (const auto &dev : devices)
    {
        vkGetPhysicalDeviceProperties(dev, &props);
        ss << "\t" << props.deviceName << '\n';
    }

    dbglog_info("{}", ss.str());

    return devices;
}

bool HelloTriangeApplication::isDeviceSuitable(const VkPhysicalDevice &device)
{
    return true;
}

void HelloTriangeApplication::pickBestPhysicalDevice(const std::vector<VkPhysicalDevice> &devices)
{
    for (const auto &device : devices)
    {
        if (isDeviceSuitable(device))
        {
            m_phyDevice = device;
            break;
        }
    }

    if (m_phyDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("Error: Failed to find a suitable GPU");
    }
}

HelloTriangeApplication::~HelloTriangeApplication()
{
    dbglog_info("{}", "Destroying VkInstance");
    vkDestroyInstance(m_vk_instance, nullptr);

    dbglog_info("{}", "Destroying GLFWwindow");
    glfwDestroyWindow(m_window);

    dbglog_info("{}", "Termination GLFW");
    glfwTerminate();
}

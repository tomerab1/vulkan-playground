#include "helloTriangleApplication.hpp"

#include "logging.hpp"

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
}

void HelloTriangeApplication::createInstance()
{
    auto availExtensions = enumerateExtensions();
    uint32_t glfwExtensionCount{0};
    auto **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    if (!isInVkExtensions(glfwExtensionCount, glfwExtensions, std::move(availExtensions)))
    {
        throw std::runtime_error("Error: Some of the glfw extensions are not supported by vulkan");
    }

    APP_INFO("Vulkan support all of GLFW extensions");

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

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &m_vk_instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Error: Failed to create VkInstance");
    }

    APP_INFO("VkInstance created successfuly");
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

    APP_INFO(ss.str());
    return extensions;
}

bool HelloTriangeApplication::isInVkExtensions(uint32_t count, const char **names, std::vector<VkExtensionProperties> extensions)
{
    for (uint32_t i = 0; i < count; i++)
    {
        auto *currName = names[i];
        if (std::find_if(extensions.begin(), extensions.end(), [&currName](const VkExtensionProperties &prop)
                         { return std::strcmp(prop.extensionName, currName) == 0; }) == extensions.end())
        {
            return false;
        }
    }

    return true;
}

HelloTriangeApplication::~HelloTriangeApplication()
{
    APP_INFO("Destroying VkInstance");
    vkDestroyInstance(m_vk_instance, nullptr);
    APP_INFO("Destroying GLFWwindow");
    glfwDestroyWindow(m_window);
    APP_INFO("Termination GLFW");
    glfwTerminate();
}

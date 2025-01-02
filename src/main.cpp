#include "helloTriangleApplication.hpp"
#include "logging.hpp"

#include <fmt/format.h>
#include <cstdlib>

int main()
{
    HelloTriangeApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        APP_ERROR(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
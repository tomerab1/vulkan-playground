#include "helloTriangleApplication.hpp"
#include "dbg_logger.hpp"

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
        dbglog_error("{}", e.what());
        return EXIT_FAILURE;
    }
    catch (...)
    {
        dbglog_error("{}", "An unknown error as occurred");
    }

    return EXIT_SUCCESS;
}
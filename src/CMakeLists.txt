cmake_minimum_required(VERSION 3.10)

project(VulkanPlayground VERSION 1.0)

add_executable(main 
    main.cpp
    helloTriangleApplication.cpp
)

target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include/)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(main PRIVATE fmt::fmt)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(main PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(main PRIVATE glm::glm)

if(WIN32)
    set(Vulkan_INCLUDE_DIR "C:/VulkanSDK/1.3.296.0/Include")
    set(Vulkan_LIBRARY "C:/VulkanSDK/1.3.296.0/Lib/vulkan-1.lib")

    find_package(Vulkan REQUIRED)
    target_include_directories(main PRIVATE ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(main PRIVATE ${Vulkan_LIBRARIES})
else()
    target_link_libraries(
        main
        PRIVATE
        glfw
        vulkan
        dl
        pthread
        X11
        Xxf86vm
        Xrandr
        Xi
    )
endif()

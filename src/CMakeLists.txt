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
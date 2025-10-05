cmake_minimum_required(VERSION 3.14)
project(zenithsim VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)

add_library(zenithsim STATIC
            zenithsim/node.cpp
            zenithsim/evalfunction.cpp 
            zenithsim/clutils.cpp 
            zenithsim/circuit.cpp)

target_include_directories(zenithsim PUBLIC zenithsim)

add_executable(zenithsim_demo_cli demo/demo.cpp)
target_link_libraries(zenithsim_demo_cli PRIVATE zenithsim)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(imgui)

add_executable(zenithsim_gui
               app/main.cpp
               app/uinode.cpp
               app/uimanager.cpp
               ${imgui_SOURCE_DIR}/imgui.cpp
               ${imgui_SOURCE_DIR}/imgui_draw.cpp
               ${imgui_SOURCE_DIR}/imgui_tables.cpp
               ${imgui_SOURCE_DIR}/imgui_widgets.cpp
               ${imgui_SOURCE_DIR}/imgui_demo.cpp
               ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
               ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)


find_package(OpenGL REQUIRED)

target_link_libraries(zenithsim_gui
    PRIVATE
    zenithsim
    glfw
    OpenGL::GL
)

target_include_directories(zenithsim_gui PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    zenithsim
)

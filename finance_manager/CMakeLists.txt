# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(PersonalFinanceManager VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory
include_directories(include)

find_package(CURL REQUIRED)
# Add executable

add_executable(PersonalFinanceManager src/main.cpp src/ExpenseManager.cpp src/IncomeManager.cpp src/FileManager.cpp src/DataVisualizer.cpp src/Networking.cpp)

target_include_directories(PersonalFinanceManager PRIVATE include)
target_link_libraries(PersonalFinanceManager PRIVATE CURL::libcurl)

# Add source files
target_sources(PersonalFinanceManager PRIVATE
    include/ExpenseManager.h
    include/IncomeManager.h
    include/FileManager.h
)

# Add ImGui files
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)

add_library(ImGui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(ImGui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)

target_link_libraries(ImGui PRIVATE glfw OpenGL::GL)
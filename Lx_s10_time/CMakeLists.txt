cmake_minimum_required(VERSION 3.16)
project(Lx_s10_time LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

# 包含第三方库的头文件
include_directories("E:/Lanxin-MRDVS-1.3.50.0710/Lanxin-MRDVS/SDK/include")

# 链接第三方库文件
link_directories("E:/Lanxin-MRDVS-1.3.50.0710/Lanxin-MRDVS/SDK/lib/win_x64")



set(PROJECT_SOURCES
    main.cpp
    Lx_s10_time.ui
    Lx_s10_time.h
    Lx_s10_time.cpp
)

qt_add_executable(Lx_s10_time ${PROJECT_SOURCES})

set_target_properties(Lx_s10_time PROPERTIES WIN32_EXECUTABLE FALSE)


target_link_libraries(Lx_s10_time
    PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        LxCameraApi
)

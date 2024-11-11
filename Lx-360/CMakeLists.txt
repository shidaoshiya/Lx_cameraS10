cmake_minimum_required(VERSION 3.16)
project(Lx-360 LANGUAGES CXX)
# 强制在调试模式下使用 MDd
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
# 强制在发布模式下使用 MD
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
if(WIN32)
add_compile_options(-DNOMINMAX)
endif()


include(qt.cmake)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

find_package(PCL 1.14.1 QUIET)
find_package(VTK REQUIRED)

# 包含第三方库的头文件
#include_directories("F:/LivoxViewer_2.3.0_Win64 SDK/Livox-SDK2-master/include")
# 链接第三方库文件
#link_directories("F:/LivoxViewer_2.3.0_Win64 SDK/Livox-SDK2-master/built/sdk_core/Debug")
# 链接第三方库文件
#link_directories("F:/LivoxViewer_2.3.0_Win64 SDK/Livox-SDK2-master/built/sdk_core/Release")

#LV
set(CAMERA_BASE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../SDK")
include_directories("${CAMERA_BASE_PATH}/include")
#link_directories("${CAMERA_BASE_PATH}/lib/Debug")
link_directories("${CAMERA_BASE_PATH}/lib/Release")

qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    livox_lidar_api.h
    livox_lidar_def.h
    Lx360.ui
    Lx360.h
    Lx360.cpp
)

if(${PCL_FOUND})
    message("PCL_FOUND ${PCL_FOUND}")
    include_directories(${PCL_INCLUDE_DIRS})
    link_directories(${PCL_LIBRARY_DIRS})
    add_definitions(${PCL_DEFINITIONS})
    include_directories(${VTK_INCLUDE_DIRS})
endif()

add_executable(Lx-360 ${PROJECT_SOURCES})

set_target_properties(Lx-360 PROPERTIES WIN32_EXECUTABLE FALSE)

target_link_libraries(Lx-360
    PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    livox_lidar_sdk_static
    ${PCL_LIBRARIES}
    ${VTK_LIBRARIES}
)

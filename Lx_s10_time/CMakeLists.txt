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

if (WIN32)
    if(CMAKE_CL_64) 
        set(PLATFORM_PREFEX win_x64)
    else()
        set(PLATFORM_PREFEX win_x86)
    endif()
	set(CAMERA_BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../)
	include_directories(${CAMERA_BASE_PATH}/SDK/include)
	link_directories(${CAMERA_BASE_PATH}/SDK/lib/${PLATFORM_PREFEX})
elseif (UNIX)
	include_directories(/opt/Lanxin-MRDVS/include)
	link_directories(/opt/Lanxin-MRDVS/lib/)
	list(APPEND LIBS ${LIBS} pthread)
endif ()



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

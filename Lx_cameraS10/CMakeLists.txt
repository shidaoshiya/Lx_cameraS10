cmake_minimum_required(VERSION 3.16)
project(Lx_cameraS10 LANGUAGES CXX)

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

set(PROJECT_SOURCES
    main.cpp
    Lx_cameraS10.ui
    Lx_cameraS10.h
    Lx_cameraS10.cpp
)

find_package(OpenCV QUIET)

if (WIN32)
if(${OPENCV_FOUND})
      	message("OPENCV_FOUND " ${OpenCV_INCLUDE_DIRS})
    	message("find opencv " ${OpenCV_VERSION})
	include_directories(${OpenCV_INCLUDE_DIRS})
	link_directories(${OpenCV_LIB_DIR})
	list(APPEND LIBS ${LIBS} ${OpenCV_LIBS})
	add_definitions(-DHAS_OPENCV)
endif()
elseif (UNIX)
if(${OPENCV_FOUND})
find_package(OpenCV QUIET)
message("OPENCV_FOUND " ${OpenCV_INCLUDE_DIRS})
    include_directories(${OpenCV_INCLUDE_DIRS})
    link_directories(${OpenCV_DIR})
    add_definitions(-DHAS_OPENCV)
endif()
endif()

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

qt_add_executable(Lx_cameraS10 ${PROJECT_SOURCES})

set_target_properties(Lx_cameraS10 PROPERTIES WIN32_EXECUTABLE FALSE)


target_link_libraries(Lx_cameraS10
    PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        LxCameraApi
        ${LIBS}
)

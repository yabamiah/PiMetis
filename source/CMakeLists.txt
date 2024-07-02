cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
FetchContent_MakeAvailable(cpr)

find_package(nlohmann_json 3.2.0 REQUIRED)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

add_subdirectory(pi_metis_bot)
add_subdirectory(pi_metis_gui)
add_subdirectory(pi_metis_ia)
add_subdirectory(pi_metis_stream)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE
        pi_metis_bot
        pi_metis_ia
        pi_metis_gui
        pi_metis_stream        
        cpr::cpr nlohmann_json::nlohmann_json ${OpenCV_LIBS} ${GTKMM_LIBRARIES} ${GLIB_LIBRARIES})


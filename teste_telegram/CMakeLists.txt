cmake_minimum_required(VERSION 3.10)
project(TelegramBot)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
FetchContent_MakeAvailable(cpr)

find_package(nlohmann_json 3.2.0 REQUIRED)

# add_subdirectory(cpr)
# add_subdirectory(json)

# include_directories(cpr/include)
# include_directories(json/include)

add_executable(TelegramBot main.cpp telegram_bot.cpp)

target_link_libraries(TelegramBot PRIVATE cpr::cpr nlohmann_json::nlohmann_json)

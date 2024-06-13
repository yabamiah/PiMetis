cmake_minimum_required(VERSION 3.10)
project(TelegramBot)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
FetchContent_MakeAvailable(cpr)

find_package(nlohmann_json 3.2.0 REQUIRED)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(BotAndEyes bot_and_eyes.cpp teste_telegram/pi_metis_bot.cpp teste_ia/pi_metis_eyes.cpp)

target_link_libraries(BotAndEyes PRIVATE cpr::cpr nlohmann_json::nlohmann_json ${OpenCV_LIBS})

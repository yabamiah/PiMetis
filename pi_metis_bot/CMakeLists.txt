set(SRC_FILES
    pi_metis_bot.cpp
    pi_metis_bot.hpp)

add_library(pi_metis_bot ${SRC_FILES})
target_link_libraries(pi_metis_bot PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
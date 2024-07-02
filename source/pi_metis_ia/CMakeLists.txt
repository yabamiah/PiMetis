set(SRC_FILES
    pi_metis_eyes.cpp
    pi_metis_eyes.hpp
    frame_provider.cpp
    frame_provider.hpp)

add_library(pi_metis_ia ${SRC_FILES})
target_link_libraries(pi_metis_ia PRIVATE ${OpenCV_LIBS})

set(SRC_FILES
    tela_camera.cpp
    tela_camera.hpp
    tela_inicial.cpp
    tela_inicial.hpp
)

add_library(pi_metis_gui ${SRC_FILES})
target_link_libraries(pi_metis_gui PRIVATE ${OpenCV_LIBS} ${GTKMM_LIBRARIES} ${GLIB_LIBRARIES})

#include <gtkmm-3.0/gtkmm.h>
#include "opencv2/opencv.hpp"
#include <iostream>

#include "tela_camera.hpp"
#include "tela_inicial.hpp"

int main(int argc, char *argv[])
{
    Gtk::Main app(argc, argv);

    auto ti = TelaInicial::create();

    Gtk::Main::run(*ti);

    return 0;
}

#include <gtkmm-3.0/gtkmm.h>
#include "opencv2/opencv.hpp"
#include <iostream>

#include "teste.hpp"

std::mutex imagemMutex;
Glib::Dispatcher dispatcher;
volatile bool captureVideoFromCamera = false;
cv::VideoCapture camera;
cv::Mat frameGBR, frame;

int main(int argc, char *argv[])
{
    Gtk::Main app(argc, argv);

    auto ti = TelaTeste::create();

    if (ti != NULL)
    {
        dispatcher.connect([&]() {
            imagemMutex.lock();
            ti->atualizarImagem(frame);
            imagemMutex.unlock();
        });

        bool cameraInicializada = inicializarCamera(0);

        if (cameraInicializada)
        {
            captureVideoFromCamera = true;
            std::thread cameraThread = std::thread(&cameraloop);
            Gtk::Main::run(*ti);

            captureVideoFromCamera = false;
            cameraThread.join();
        }
    }

    if (camera.isOpened())
    {
        camera.release();
    }

    return 0;
}

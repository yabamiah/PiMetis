#ifndef TESTE_HPP
#define TESTE_HPP

#include <gtkmm-3.0/gtkmm.h>
#include "opencv2/opencv.hpp"
#include <mutex>
#include <thread>

void cameraloop();
bool inicializarCamera(int cameraIndex);

class TelaTeste : public Gtk::Window
{
	public:
		TelaTeste(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
		static TelaTeste* create();
		void pararCamera();
		void atualizarImagem(cv::Mat &frame);

	private:
		Gtk::Window *ti_window;
		Gtk::Image *tt_imagem2;
		Glib::RefPtr<Gtk::Builder> tt_builder;
};

extern std::mutex imagemMutex;
extern Glib::Dispatcher dispatcher;
extern volatile bool captureVideoFromCamera;
extern cv::VideoCapture camera;
extern cv::Mat frameGBR, frame;

#endif // TESTE_HPP

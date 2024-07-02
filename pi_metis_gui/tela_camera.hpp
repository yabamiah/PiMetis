#ifndef TELA_CAMERA_HPP
#define TELA_CAMERA_HPP

#include <gtkmm-3.0/gtkmm.h>
#include "opencv2/opencv.hpp"
#include <mutex>
#include <thread>
#include <chrono>

#include "tela_inicial.hpp"
#include "/home/yaba/Sandbox/PiMetis/pi_metis_ia/frame_provider.hpp"

// void cameraloop();
// bool inicializarCamera(int cameraIndex);

class TelaCamera : public Gtk::Window
{
	public:
		TelaCamera(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
		static TelaCamera* create(FrameProvider& provider);
		void update_frame_provider(FrameProvider* provider);
		// void pararCamera();
		void atualizarImagem(cv::Mat &frame);

	private:
        void on_tc_button1_clicked();

		Gtk::Window *tc_window;
		Gtk::Image *tc_imagem;
		Gtk::Button *tc_button1;
		Glib::RefPtr<Gtk::Builder> tc_builder;
		FrameProvider* frame_provider;
};

extern std::mutex imagemMutex;
extern Glib::Dispatcher dispatcher;
// extern volatile bool captureVideoFromCamera;
// extern cv::VideoCapture camera;
// extern cv::Mat frameGBR, frame;

#endif // TELA_CAMERA_HPP

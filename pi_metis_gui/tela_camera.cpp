#include "tela_camera.hpp"

// std::mutex imagemMutex;
// Glib::Dispatcher dispatcher;
// volatile bool captureVideoFromCamera;
// cv::VideoCapture camera;
// cv::Mat frameGBR, frame;

TelaCamera::TelaCamera(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade, FrameProvider& provider)
	: Gtk::Window(cobject), tc_builder(refGlade), frame_provider(provider)
{
	tc_builder->get_widget( "tc_imagem", tc_imagem );
	tc_builder->get_widget( "tc_button1", tc_button1 );

    tc_button1->signal_clicked().connect( sigc::mem_fun( *this, &TelaCamera::on_tc_button1_clicked ) );

    std::thread tela_camera_att_image_thread(&TelaCamera::atualizarImagem, this);
	tela_camera_att_image_thread.detach();
}

TelaCamera* TelaCamera::create(FrameProvider& provider)
{
	auto tc_builder = Gtk::Builder::create();

	tc_builder->add_from_file( "/home/yaba/Sandbox/PiMetis/pi_metis_gui/telaCamera.ui" );

	TelaCamera *win = nullptr;
	// win->set_frame_provider(provider);

	tc_builder->get_widget_derived( "tc_window", win, provider );

	if (!win)
	{
		throw std::runtime_error( "No \"window\" object in telaCamera.ui" );
	}

	return win;
}

void TelaCamera::atualizarImagem()
{
	while (1)
	{
		cv::Mat frame = this->frame_provider.get_frame();
		if (!frame.empty())
		{
			std::unique_lock<std::mutex> lock(imagemMutex);
			cv::Mat frameRGB;
			cv::cvtColor(frame, frameRGB, cv::COLOR_BGR2RGB);

			auto pixbuf = Gdk::Pixbuf::create_from_data(
				frameRGB.data,
				Gdk::COLORSPACE_RGB,
				false,
				8,
				frame.cols, 
				frame.rows, 
				frame.step
			);

			if (pixbuf)
			{
				Glib::RefPtr<Gdk::Pixbuf> copied_pixbuf = pixbuf->copy();
				lock.unlock();
				Glib::signal_idle().connect_once([this, copied_pixbuf]()
				{
					tc_imagem->set(copied_pixbuf);
					tc_imagem->queue_draw();	
				});
			}
			
			dispatcher.emit();
		}
	}
}

// void TelaCamera::pararCamera()
// {
// 	hide();
// }

void TelaCamera::on_tc_button1_clicked()
{
	auto ti_window = TelaInicial::create(this->frame_provider);
	hide();
	// camera.release();
	
	Gtk::Main::run(*ti_window);
}

// void cameraloop()
// {
// 	while(captureVideoFromCamera)
// 	{
// 		bool continueToGrabe = true;
		
// 		continueToGrabe = camera.read(frameGBR);
// 		if (continueToGrabe)
// 		{
// 			imagemMutex.lock();
// 			cv::cvtColor(frameGBR, frame, cv::COLOR_BGR2RGB);
// 			imagemMutex.unlock();
// 			dispatcher.emit();
// 		}
// 		if (!continueToGrabe)
// 		{
// 			captureVideoFromCamera = false;
// 			std::cerr << "Falha ao recuperar frame do dispositivo.\n";
// 		}
// 	}
// }

// bool inicializarCamera(int cameraIndex)
// {
// 	bool result = camera.open(cameraIndex, cv::CAP_V4L);

// 	if (result)
// 	{
// 		camera.set(cv::CAP_PROP_FRAME_WIDTH, 600);
// 		camera.set(cv::CAP_PROP_FRAME_HEIGHT, 400);
// 		camera.set(cv::CAP_PROP_FPS, 30);

// 		for (int i = 0; i < 3; i++)
// 		{
// 			camera.grab();
// 		}

// 		for (int i = 0; result && i < 3; i++)
// 		{
// 			result = result && camera.read(frameGBR);
// 		}
// 	}

// 	return result;
// }


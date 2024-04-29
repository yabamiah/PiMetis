#include "teste.hpp"

TelaTeste::TelaTeste(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	: Gtk::Window(cobject), tt_builder(refGlade)
{
	tt_builder->get_widget( "tt_imagem2", tt_imagem2);
}

TelaTeste* TelaTeste::create()
{
	auto ti_builder = Gtk::Builder::create();

	ti_builder->add_from_file( "teste-opencv.ui" );

	TelaTeste *win = nullptr;
	ti_builder->get_widget_derived( "telaTeste", win );

	if (!win)
	{
		throw std::runtime_error( "No \"window\" object in telaInicial.ui" );
	}

	return win;
}

void TelaTeste::atualizarImagem(cv::Mat &frame)
{
	if (!frame.empty())
	{
		tt_imagem2->set(Gdk::Pixbuf::create_from_data(frame.data, Gdk::COLORSPACE_RGB, false, 8, frame.cols, frame.rows, frame.step));
		tt_imagem2->queue_draw();
	}
}

void TelaTeste::pararCamera()
{
	hide();
}

void cameraloop()
{
	while(captureVideoFromCamera)
	{
		bool continueToGrabe = true;
		
		continueToGrabe = camera.read(frameGBR);
		if (continueToGrabe)
		{
			imagemMutex.lock();
			cv::cvtColor(frameGBR, frame, cv::COLOR_BGR2RGB);
			imagemMutex.unlock();
			dispatcher.emit();
		}
		if (!continueToGrabe)
		{
			captureVideoFromCamera = false;
			std::cerr << "Falha ao recuperar frame do dispositivo.\n";
		}
	}
}

bool inicializarCamera(int cameraIndex)
{
	bool result = camera.open(cameraIndex, cv::CAP_V4L);

	if (result)
	{
		camera.set(cv::CAP_PROP_FRAME_WIDTH, 500);
		camera.set(cv::CAP_PROP_FRAME_HEIGHT, 300);
		camera.set(cv::CAP_PROP_FPS, 30);

		for (int i = 0; i < 3; i++)
		{
			camera.grab();
		}

		for (int i = 0; result && i < 3; i++)
		{
			result = result && camera.read(frameGBR);
		}
	}

	return result;
}


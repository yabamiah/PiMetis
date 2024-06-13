#include "tela_camera.hpp"

TelaCamera::TelaCamera(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	: Gtk::Window(cobject), tc_builder(refGlade)
{
	tc_builder->get_widget( "tc_imagem", tc_imagem );
	tc_builder->get_widget( "tc_button1", tc_button1 );

    tc_button1->signal_clicked().connect( sigc::mem_fun( *this, &TelaCamera::on_tc_button1_clicked ) );
}

TelaCamera* TelaCamera::create()
{
	auto tc_builder = Gtk::Builder::create();

	tc_builder->add_from_file( "telaCamera.ui" );

	TelaCamera *win = nullptr;
	tc_builder->get_widget_derived( "tc_window", win );

	if (!win)
	{
		throw std::runtime_error( "No \"window\" object in telaCamera.ui" );
	}

	return win;
}

void TelaCamera::atualizarImagem(cv::Mat &frame)
{
	if (!frame.empty())
	{
		tc_imagem->set(Gdk::Pixbuf::create_from_data(frame.data, Gdk::COLORSPACE_RGB, false, 8, frame.cols, frame.rows, frame.step));
		tc_imagem->queue_draw();
	}
}

void TelaCamera::pararCamera()
{
	hide();
}

void TelaCamera::on_tc_button1_clicked()
{
	auto ti_window = TelaInicial::create();
	hide();
	camera.release();
	
	Gtk::Main::run(*ti_window);
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
		camera.set(cv::CAP_PROP_FRAME_WIDTH, 600);
		camera.set(cv::CAP_PROP_FRAME_HEIGHT, 400);
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


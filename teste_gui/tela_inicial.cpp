#include "tela_inicial.hpp"

std::mutex imagemMutex;
Glib::Dispatcher dispatcher;
volatile bool captureVideoFromCamera = false;
cv::VideoCapture camera;
cv::Mat frameGBR, frame;

TelaInicial::TelaInicial(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
    Gtk::Window(cobject), ti_builder(refGlade)    
{
    ti_builder->get_widget( "ti_button1", ti_button1 );
    ti_builder->get_widget( "ti_button2", ti_button2 );
    ti_builder->get_widget( "ti_button3", ti_button3 );
    ti_builder->get_widget( "ti_button4", ti_button4 );
    ti_builder->get_widget( "ti_dialog", ti_dialog);

    ti_button1->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button1_clicked ) );
    ti_button2->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button2_clicked ) );
    ti_button3->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button3_clicked ) );
    ti_button4->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button4_clicked ) );
}

TelaInicial* TelaInicial::create()
{
    auto ti_builder = Gtk::Builder::create();

    ti_builder->add_from_file( "telaInicial.ui" );

    TelaInicial *win = nullptr;
    ti_builder->get_widget_derived( "ti_window", win );

    if (!win)
    {
        throw std::runtime_error( "No \"window\" object in telaInicial.ui" );
    }

    return win;
}

void TelaInicial::on_ti_button1_clicked()
{
    close();
}

void TelaInicial::on_ti_button2_clicked()
{   
    ti_dialog->show();
    ti_dialog->present();
}

void TelaInicial::on_ti_button3_clicked()
{
    auto tc_window = TelaCamera::create();
    hide();

    Gtk::Main::run(*tc_window);

    bool cameraInicializada = inicializarCamera(0);
    dispatcher.connect([&]() {
        imagemMutex.lock();
        tc_window->atualizarImagem(frame);
        imagemMutex.unlock();
    });

    if (cameraInicializada)
    {
        captureVideoFromCamera = true;
        std::thread cameraThread = std::thread(&cameraloop);
        Gtk::Main::run(*tc_window);

        captureVideoFromCamera = false;
        cameraThread.join();
    }

    if (camera.isOpened())
    {
        camera.release();
    }
}

void TelaInicial::on_ti_button4_clicked()
{
    std::cout << "Tome\n";
}
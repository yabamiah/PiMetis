#include "tela_inicial.hpp"

std::mutex imagemMutex;
Glib::Dispatcher dispatcher;
// volatile bool captureVideoFromCamera = false;
// cv::VideoCapture camera;
// cv::Mat frameGBR, frame;

TelaInicial::TelaInicial(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
    Gtk::Window(cobject), ti_builder(refGlade)    
{
    ti_builder->get_widget( "ti_button1", ti_button1 );
    ti_builder->get_widget( "ti_button2", ti_button2 );
    ti_builder->get_widget( "ti_button3", ti_button3 );
    ti_builder->get_widget( "ti_button4", ti_button4 );

    ti_builder->get_widget( "ti_dialog1", ti_dialog1);
    ti_builder->get_widget( "ti_dialog2", ti_dialog2);

    ti_builder->get_widget( "ti_dialog2_entry", ti_dialog2_entry );
    ti_builder->get_widget( "ti_dialog2_button1", ti_dialog2_button1 );
    ti_builder->get_widget( "ti_dialog2_button2", ti_dialog2_button2 );

    ti_button1->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button1_clicked ) );
    ti_button2->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button2_clicked ) );
    ti_button3->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button3_clicked ) );
    ti_button4->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button4_clicked ) );

    ti_dialog2_button1->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_dialog2_button1_clicked ) );
    ti_dialog2_button2->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_dialog2_button2_clicked ) );
}

TelaInicial* TelaInicial::create()
{
    auto ti_builder = Gtk::Builder::create();

    ti_builder->add_from_file( "/home/yaba/Sandbox/PiMetis/pi_metis_gui/telaInicial.ui" );

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
    ti_dialog1->show();
    ti_dialog1->present();
}

void TelaInicial::on_ti_button3_clicked()
{
    pi_metis_eyes detector;
    FrameProvider frame_provider;

    detector.update_frame_provider(frame_provider);

    auto tc_window = TelaCamera::create(frame_provider);
    hide();

    Gtk::Main::run(*tc_window);

    // dispatcher.connect([&]() {
    //     imagemMutex.lock();
    //     tc_window->atualizarImagem(frame);
    //     imagemMutex.unlock();
    // });

    // if (!frame.empty())
    // {
    //     captureVideoFromCamera = true;
    //     Gtk::Main::run(*tc_window);

    //     captureVideoFromCamera = false;
    // }

    // if (camera.isOpened())
    // {
    //     camera.release();
    // }
}

void TelaInicial::on_ti_button4_clicked()
{
    ti_dialog2->show();
    ti_dialog2->present();
}

void TelaInicial::on_ti_dialog2_button1_clicked()
{
    ti_dialog2->close();
}

void TelaInicial::on_ti_dialog2_button2_clicked()
{
    std::string limit_person_str = ti_dialog2_entry->get_text();  
    this->limit_person = std::stoi(limit_person_str);
    ti_dialog2->close();
}

void TelaInicial::active_eyes_detect()
{
    if (!detection_thread.joinable())
    {
        detection_thread = std::thread(&pi_metis_eyes::pi_metis_detect, &eyes);
    }
}
#include "tela_inicial.hpp"

std::mutex imagemMutex;
Glib::Dispatcher dispatcher;
int static eyes_activate_value;
int *eyes_activate = &eyes_activate_value;
int limit_person = 3;
// volatile bool captureVideoFromCamera = false;
// cv::VideoCapture camera;
// cv::Mat frameGBR, frame;

TelaInicial::TelaInicial(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade, FrameProvider& provider) :
    Gtk::Window(cobject), ti_builder(refGlade), frame_provider(provider)    
{
    ti_builder->get_widget( "ti_button1", ti_button1 );
    ti_builder->get_widget( "ti_button2", ti_button2 );
    ti_builder->get_widget( "ti_button3", ti_button3 );
    ti_builder->get_widget( "ti_button4", ti_button4 );
    ti_builder->get_widget( "ti_button5", ti_button5 );
    ti_builder->get_widget( "ti_button6", ti_button6 );

    ti_builder->get_widget( "ti_dialog1", ti_dialog1);
    ti_builder->get_widget( "ti_dialog2", ti_dialog2);

    ti_builder->get_widget( "ti_dialog2_entry", ti_dialog2_entry );
    ti_builder->get_widget( "ti_dialog2_button1", ti_dialog2_button1 );
    ti_builder->get_widget( "ti_dialog2_button2", ti_dialog2_button2 );

    ti_button1->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button1_clicked ) );
    ti_button2->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button2_clicked ) );
    ti_button3->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button3_clicked ) );
    ti_button4->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button4_clicked ) );
    ti_button5->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button5_clicked ) );
    ti_button6->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_button6_clicked ) );

    ti_dialog2_button1->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_dialog2_button1_clicked ) );
    ti_dialog2_button2->signal_clicked().connect( sigc::mem_fun( *this, &TelaInicial::on_ti_dialog2_button2_clicked ) );

    if (*eyes_activate == 1)
    {
        ti_button5->hide();
        ti_button6->show(); 
    }
    else
    {
        ti_button6->hide();
        ti_button5->show();
    }
}


TelaInicial* TelaInicial::create(FrameProvider& provider)
{
    auto ti_builder = Gtk::Builder::create();

    ti_builder->add_from_file( "/home/yaba/Sandbox/PiMetis/pi_metis_gui/telaInicial.ui" );

    TelaInicial *win = nullptr;
    ti_builder->get_widget_derived( "ti_window", win, provider );

    if (!win)
    {
        throw std::runtime_error( "No \"window\" object in telaInicial.ui" );
    }

    return win;
}


void TelaInicial::on_ti_button1_clicked()
{
    system("pkill -9 -f ngrok");
    close();
}

void TelaInicial::on_ti_button2_clicked()
{   
    ti_dialog1->show();
    ti_dialog1->present();
}

void TelaInicial::on_ti_button3_clicked()
{
    auto tc_window = TelaCamera::create(this->frame_provider);
    hide();

    Gtk::Main::run(*tc_window);
}

void TelaInicial::on_ti_button4_clicked()
{
    ti_dialog2->show();
    ti_dialog2->present();
}

void TelaInicial::on_ti_button5_clicked()
{
    ti_button5->hide();
    ti_button6->show();
    *eyes_activate = 1;
}

void TelaInicial::on_ti_button6_clicked()
{
    ti_button6->hide();
    ti_button5->show();
    *eyes_activate = 0;
}

void TelaInicial::on_ti_dialog2_button1_clicked()
{
    ti_dialog2->close();
}

void TelaInicial::on_ti_dialog2_button2_clicked()
{
    std::string limit_person_str = ti_dialog2_entry->get_text();  
    limit_person = std::stoi(limit_person_str);
    ti_dialog2->close();
}

// void TelaInicial::active_eyes_detect()
// {
//     if (!detection_thread.joinable())
//     {
//         detection_thread = std::thread(&pi_metis_eyes::pi_metis_detect, &eyes);
//     }
// }
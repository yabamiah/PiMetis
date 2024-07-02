#include "pi_metis_lib.hpp"

void detection_loop(VideoStreamer& streamer)
{
    telegram_bot pi_metis_bot("7132288406:AAGr8jjVtgQbD1VptDYure0pTn98EcohxBQ", "835554428");

    while (true)
    {
        // std::cout << "Limite e count:" << limit_person << " " << person_counter.load() << std::endl;
        if (person_counter.load() >= limit_person)
        {
            std::cout << "Perigo\n";
            std::thread streamer_thread(&VideoStreamer::start, &streamer);
            streamer_thread.detach();

            pi_metis_bot.send_warning("O limite de pessoas foi ultrapassada.", "/home/yaba/Sandbox/PiMetis/source/pi_metis_ia/person.jpg");
            std::this_thread::sleep_for(std::chrono::seconds(30));

            streamer.stop();
        }

        if (object_counter.load() != 0)
        {
            std::cout << "Perigo\n";
            std::thread streamer_thread(&VideoStreamer::start, &streamer);
            streamer_thread.detach();

            pi_metis_bot.send_warning("Um objeto perigoso foi detectado.", "/home/yaba/Sandbox/PiMetis/source/pi_metis_ia/object.jpg");
            std::this_thread::sleep_for(std::chrono::seconds(30));
            
            streamer.stop();
        }
    }

}

int main(int argc, char *argv[])
{
    FrameProvider provider;
    pi_metis_eyes eyes;
    VideoStreamer streamer(provider);
    std::atomic_bool terminate_eyes_flag(false);

    std::thread frame_update_thread(&pi_metis_eyes::update_frame_provider, &eyes, std::ref(provider));
    std::thread eyes_detect_thread(&pi_metis_eyes::pi_metis_detect, &eyes, eyes_activate, std::ref(terminate_eyes_flag));
    std::thread warning_loop(detection_loop, std::ref(streamer));
    
    frame_update_thread.join();
    eyes_detect_thread.detach();
    warning_loop.detach();

    Gtk::Main app(argc, argv);

    auto ti = TelaInicial::create(provider);

    Gtk::Main::run(*ti);

    terminate_eyes_flag = true;
    
    return 0;
}
#include "pi_metis_lib.hpp"


int main(int argc, char *argv[])
{
    FrameProvider provider;
    pi_metis_eyes eyes;

    std::thread frame_update_thread(&pi_metis_eyes::update_frame_provider, &eyes, std::ref(provider));
    std::thread eyes_detect_thread(&pi_metis_eyes::pi_metis_detect, &eyes);
    

    VideoStreamer streamer(provider);
    std::thread streamer_thread(&VideoStreamer::start, &streamer);

    frame_update_thread.join();
    eyes_detect_thread.detach();
    streamer_thread.join();

    Gtk::Main app(argc, argv);

    auto ti = TelaInicial::create();

    Gtk::Main::run(*ti);
    return 0;
}
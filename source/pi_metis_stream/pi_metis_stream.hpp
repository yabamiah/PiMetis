#ifndef PI_METIS_STREAM_HPP
#define PI_METIS_STREAM_HPP

#include <opencv2/opencv.hpp>
#include "httplib.h"
#include <fstream>
#include <thread>
#include <string>
#include <iostream>
#include <vector>

#include "/home/yaba/Sandbox/PiMetis/source/pi_metis_ia/frame_provider.hpp"

class VideoStreamer 
{
    public:
        VideoStreamer(FrameProvider& provider);

        void start();
        void stop();

    private:
        FrameProvider& frame_provider;
        std::thread ngrokThread;
        httplib::Server svr;

        void handle_video_feed(httplib::Response &res);
        void handle_index(httplib::Response &res);

        void create_ngrok_server();
};

#endif // PI_METIS_STREAM_HPP

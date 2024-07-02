#include "pi_metis_stream.hpp"

VideoStreamer::VideoStreamer(FrameProvider& provider) 
    : frame_provider(provider) 
{ 
}

void VideoStreamer::start()
{
    if (!this->ngrokThread.joinable())
    {
        this->ngrokThread = std::thread(&VideoStreamer::create_ngrok_server, this);
        this->ngrokThread.join();
    }
    else
    {
        std::cerr << "Não foi possível criar o servidor ngrok.\n";
    }
    // std::thread ngrokThread(&VideoStreamer::create_ngrok_server, this);
    
    svr.Get("/", [this](const httplib::Request &, httplib::Response &res) {
        this->handle_index(res);
    });

    svr.Get("/video_feed", [this](const httplib::Request &, httplib::Response &res) {
        this->handle_video_feed(res);
    });

    svr.listen("localhost", 5000);
}

void VideoStreamer::stop()
{
    if (svr.is_running())
    {
        svr.stop();
        system("pkill -9 -f ngrok");
    }
}

void VideoStreamer::handle_video_feed(httplib::Response &res)
{
    res.set_content_provider(
                "multipart/x-mixed-replace; boundary=frame",
                [this](size_t offset, httplib::DataSink &sink) {
                    while (true) 
                    {
                        cv::Mat frame = this->frame_provider.get_frame();
                        // this->video >> frame;
                        std::vector<uchar> buf;
                        cv::imencode(".jpg", frame, buf);
                        std::string data(buf.begin(), buf.end());

                        std::string header = "--frame\r\nContent-Type: image/jpeg\r\n\r\n";
                        sink.write(header.data(), header.size());
                        sink.write(data.data(), data.size());
                        sink.write("\r\n", 2);

                        if (!sink.is_writable()) 
                        {
                            break;
                        }
                    }
                    return true;
                },
                [](bool success) 
                {
                }
    );
}

void VideoStreamer::handle_index(httplib::Response &res)
{
    res.set_content(R"(
                <!DOCTYPE html>
                <html>
                <head>
                    <title>Video Stream</title>
                </head>
                <body>
                    <h1>Video Stream</h1>
                    <img src="/video_feed" width="640" height="480" />
                </body>
                </html>
            )", "text/html");
}

void VideoStreamer::create_ngrok_server()
{
    system("pkill -9 -f ngrok");    
    system("ngrok http 5000 --log=stdout > /home/yaba/Sandbox/PiMetis/pi_metis_stream/ngrok.log &");
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::ifstream log_file("/home/yaba/Sandbox/PiMetis/pi_metis_stream/ngrok.log");
    std::string line;
    std::string public_url;

    while (std::getline(log_file, line)) 
    {
        if (line.find("url=") != std::string::npos) 
        {
            public_url = line.substr(line.find("url=") + 4);
            break;
        }
    }
    
    log_file.close();

    std::ofstream link_file("/home/yaba/Sandbox/PiMetis/servidor_link.txt", std::ios::out | std::ios::trunc);
    link_file << public_url;
    link_file.close();

    // std::cout << " * Link do servidor ngrok: " << public_url << " -> http://127.0.0.1:5000" << std::endl;
}
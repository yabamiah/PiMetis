#include <opencv2/opencv.hpp>
#include "httplib.h"
#include <fstream>
#include <thread>

using namespace cv;

VideoCapture video(0, CAP_V4L);

void handle_video_feed(const httplib::Request &, httplib::Response &res) {
    res.set_content_provider(
        "multipart/x-mixed-replace; boundary=frame",
        [](size_t offset, httplib::DataSink &sink) {
            while (true) {
                Mat frame;
                video >> frame;
                std::vector<uchar> buf;
                cv::imencode(".jpg", frame, buf);
                std::string data(buf.begin(), buf.end());

                std::string header = "--frame\r\nContent-Type: image/jpeg\r\n\r\n";
                sink.write(header.data(), header.size());
                sink.write(data.data(), data.size());
                sink.write("\r\n", 2);
                
                if (!sink.is_writable()) {
                    break;
                }
            }
            return true;
        },
        [](bool success) {
            // Optional: Handle resource release if needed
        });
}

void handle_index(const httplib::Request &, httplib::Response &res) {
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

void create_ngrok_server() {
    system("ngrok http 5000 --log=stdout > ngrok.log &");
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::ifstream log_file("ngrok.log");
    std::string line;
    std::string public_url;
    while (std::getline(log_file, line)) {
        if (line.find("url=") != std::string::npos) {
            public_url = line.substr(line.find("url=") + 4);
            break;
        }
    }
    log_file.close();

    std::ofstream link_file("../servidor_link.txt");
    link_file << public_url;
    link_file.close();

    std::cout << " * Link do servidor ngrok: " << public_url << " -> http://127.0.0.1:5000" << std::endl;
}

int main() {
    httplib::Server svr;

    svr.Get("/", handle_index);
    svr.Get("/video_feed", handle_video_feed);

    std::thread ngrokThread(create_ngrok_server);
    ngrokThread.join();

    svr.listen("localhost", 5000);

    return 0;
}

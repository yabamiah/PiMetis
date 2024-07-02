#include <iostream>
#include <opencv2/opencv.hpp>
#include "httplib.h"
#include <thread>
#include <mutex>
#include <unistd.h>
#include <regex>
#include <fstream>

using namespace cv;

Mat frame;
std::mutex frame_mutex;

void create_ngrok_server() {
    std::cout << "Iniciando ngrok..." << std::endl;
    system("ngrok http 8080 --log=stdout > ngrok.log &");
    printf("PID = %d\n", getpid());
}

void catch_server_link() {
    std::cout << "Capturando link do servidor..." << std::endl;
    std::ifstream file;
    std::string line;
    std::regex url_regex(R"(https://[a-zA-Z0-9\-]+\.ngrok-free\.app)");
    std::smatch url_match;
    bool url_found = false;

    // Esperar até que o URL esteja disponível no arquivo de log
    while (!url_found) {
        file.open("ngrok.log");
        if (file.is_open()) {
            while (std::getline(file, line)) {
                if (std::regex_search(line, url_match, url_regex)) {
                    std::string url = url_match[0];
                    std::ofstream out("../servidor_link.txt");
                    out << url;
                    out.close();
                    std::cout << " * Link do servidor ngrok: \"" << url << "\" -> \"http://127.0.0.1:5000\"" << std::endl;
                    url_found = true;
                    break;
                }
            }
            file.close();
        }
        break;
    }
}

void capture_frames() {
    VideoCapture cap(0, CAP_V4L); // Open the default camera

    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream" << std::endl;
        return;
    }

    while (true) {
        Mat temp_frame;
        cap >> temp_frame; // Capture a new frame
        if (temp_frame.empty()) {
            std::cerr << "Error capturing frame" << std::endl;
            continue;
        }

        // Lock the mutex and update the frame
        std::lock_guard<std::mutex> lock(frame_mutex);
        frame = temp_frame.clone();
    }
}

void send_frame(const httplib::Request& req, httplib::Response& res) {
    std::lock_guard<std::mutex> lock(frame_mutex);

    if (frame.empty()) {
        res.status = 500;
        res.set_content("No frame captured", "text/plain");
        return;
    }

    std::vector<uchar> buf;
    imencode(".jpg", frame, buf);

    res.set_content(reinterpret_cast<const char*>(buf.data()), buf.size(), "image/jpeg");
}

void send_html(const httplib::Request& req, httplib::Response& res) {
    std::string html = R"(
    <!DOCTYPE html>
    <html>
    <head>
        <title>Live Camera Feed</title>
    </head>
    <body>
        <h1>Live Camera Feed</h1>
        <img src="/frame.jpg" id="cameraFeed" alt="Camera Feed" style="max-width: 100%;">
        <script>
            function reloadImage() 
            {
                var img = document.getElementById('cameraFeed');
                img.src = '/frame.jpg?t=' + new Date().getTime();
            }
            setInterval(reloadImage, 1000); // Reload every 100 milliseconds
        </script>
    </body>
    </html>
    )";

    res.set_content(html, "text/html");
}

int main() {
    // Start the frame capture in a separate thread
    std::thread capture_thread(capture_frames);

    std::thread generate_ngrok(create_ngrok_server);
    sleep(3);
    std::thread catch_link(catch_server_link);

    // Create the HTTP server
    httplib::Server svr;

    svr.Get("/", send_html);
    svr.Get("/frame.jpg", send_frame);

    std::cout << "Starting server on http://localhost:8080" << std::endl;
    svr.listen("localhost", 8080);

    capture_thread.join();
    generate_ngrok.join();
    catch_link.join();
    return 0;
}
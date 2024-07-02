#ifndef PI_METIS_EYES_HPP
#define PI_METIS_EYES_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <csignal>
#include <chrono>
#include <thread>

#include <opencv2/opencv.hpp>
#include "frame_provider.hpp"

class pi_metis_eyes
{
    private:
        std::vector<std::string> nomes;
        std::ifstream class_names {"/home/yaba/Sandbox/PiMetis/teste_ia/coco.names"};
        std::vector<cv::Scalar> colors;
        
        cv::dnn::Net net;
        cv::dnn::DetectionModel model;
        cv::VideoCapture camera;

        std::chrono::time_point<std::chrono::steady_clock> last_person_detected;
        std::chrono::time_point<std::chrono::steady_clock> last_object_detected;

        cv::Mat current_frame;
        std::mutex frame_mutex;

        FrameProvider* frame_provider;

    public:
        pi_metis_eyes();
        ~pi_metis_eyes();
        cv::Mat get_frame();
        void update_frame_provider(FrameProvider& provider);
        void pi_metis_detect();
};

extern int person_counter;
extern int object_counter;

#endif // PI_METIS_EYES_HPP
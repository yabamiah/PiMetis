#ifndef PI_METIS_EYES_HPP
#define PI_METIS_EYES_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <csignal>
#include <chrono>
#include <thread>

#include <opencv2/opencv.hpp>

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

    public:
        pi_metis_eyes();
        ~pi_metis_eyes();
        void pi_metis_detect();
};

extern int person_counter;
extern int object_counter;

void person_signal_handler( int signal );
void object_signal_handler( int signal );

#endif // PI_METIS_EYES_HPP
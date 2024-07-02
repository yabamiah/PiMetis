#include "pi_metis_eyes.hpp"

int person_counter = 0;
int object_counter = 0;

pi_metis_eyes::pi_metis_eyes()
{
    bool cap = this->camera.open(0, cv::CAP_V4L);
    if (!cap)
    {
        std::cerr << "Erro ao abrir a câmera." << std::endl;
    }

    std::string linha;

    while (std::getline(this->class_names, linha))
    {
        this->nomes.push_back(linha);
    }

    this->net = cv::dnn::readNetFromDarknet("/home/yaba/Sandbox/PiMetis/pi_metis_ia/yolov4-tiny.cfg", "/home/yaba/Sandbox/PiMetis/pi_metis_ia/yolov4-tiny.weights");
    this->model = cv::dnn::DetectionModel(this->net);

    this->model.setInputParams( 1/255.0, cv::Size(416, 416), cv::Scalar(), true);

    this->colors = {cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255), cv::Scalar(255, 0, 0),
                    cv::Scalar(255, 255, 0), cv::Scalar(255, 0, 255), cv::Scalar(0, 255, 255)};

    // std::thread detecting(&pi_metis_eyes::pi_metis_detect, this);

    // detecting.detach();
}

pi_metis_eyes::~pi_metis_eyes()
{
    this->camera.release();
}

void pi_metis_eyes::pi_metis_detect()
{
    auto last_detected = std::chrono::steady_clock::now();

    this->last_person_detected = last_detected;
    this->last_object_detected = last_detected;

    while (true)
    {
        camera.read(this->current_frame);
        if (this->current_frame.empty())
        {
            std::cout << "Fim da transmissão\n";
            break;
        }

        std::vector<int> classes;
        std::vector<float> scores;
        std::vector<cv::Rect> boxes;

        person_counter = 0;
        object_counter = 0;

        model.detect(this->current_frame, classes, scores, boxes, 0.4, 0.4);
    
        for (int i = 0; i < classes.size(); i++)
        {
            const auto color = this->colors[i % this->colors.size()];
            cv::rectangle(this->current_frame, boxes[i], color, 2);

            char label[100];

            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<double> time_last_person_detection = now - last_person_detected;
            std::chrono::duration<double> time_last_object_detection = now - last_object_detected;
        
            if (this->nomes[classes[i]].compare("person") == 0)
            {    
                person_counter++;
                cv::imwrite("person.jpg", this->current_frame);

                // if (time_last_person_detection.count() >= 10)
                // {

                //     // std::raise(SIGUSR1);
                //     this->last_person_detected = now;
                // }
            }

            if (nomes[classes[i]].compare("knife") == 0 
                || nomes[classes[i]].compare("baseball bat") == 0 
                || nomes[classes[i]].compare("scissors") == 0)
            {
                object_counter++;
                cv::imwrite("object.jpg", this->current_frame);

                // if (time_last_object_detection.count() >= 30)
                // {
                //     // std::raise(SIGUSR2);
                //     this->last_object_detected = now;
                // }
            }

            if (nomes[classes[i]].compare("hide") != 0)
            {
                snprintf(label, sizeof(label), "%s: %.2f", nomes[classes[i]].c_str(), scores[i]);
    
                cv::putText(this->current_frame, label, cv::Point(boxes[i].x, boxes[i].y - 5), 
                            cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 1);   
            }
        }

        std::cout << "Count: " << person_counter << std::endl;
        fflush(stdout);

        if (this->frame_provider)
        {
            frame_provider->update_frame(this->current_frame);
        }

    }
}

cv::Mat pi_metis_eyes::get_frame()
{
    std::lock_guard<std::mutex> lock(this->frame_mutex);
    return this->current_frame.clone();
}

void pi_metis_eyes::update_frame_provider(FrameProvider& provider)
{
    this->frame_provider = &provider;
}
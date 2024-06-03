#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    std::vector<std::string> nomes;
    std::ifstream coco_names("coco.names");
    std::string linha;

    while (std::getline(coco_names, linha))
    {
        nomes.push_back(linha);
    }

    cv::dnn::Net net;
    net = cv::dnn::readNetFromDarknet("yolov4-tiny.cfg", "yolov4-tiny.weights");

    cv::dnn::DetectionModel model = cv::dnn::DetectionModel(net);
    model.setInputParams( 1/255.0, cv::Size(416, 416), cv::Scalar(), true);

	cv::VideoCapture camera;
    cv::Mat frame;
    bool cap = camera.open(0, cv::CAP_V4L);

    std::vector<cv::Scalar> colors = {cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255), cv::Scalar(255, 0, 0),
                                    cv::Scalar(255, 255, 0), cv::Scalar(255, 0, 255), cv::Scalar(0, 255, 255)};                                    

    while (true)
    {
        camera.read(frame);
        if (frame.empty())
        {
            std::cout << "Fim da transmissão\n";
            break;
        }

        // cap >> frame;

        std::vector<int> classes;
        std::vector<float> scores;
        std::vector<cv::Rect> boxes;

        model.detect(frame, classes, scores, boxes, 0.6, 0.4);

        for (int i = 0; i < classes.size(); i++)
        {
            const auto color = colors[i % colors.size()];
            cv::rectangle(frame, boxes[i], color, 2);

            char label[100];
            snprintf(label, sizeof(label), "%s: %.2f", nomes[classes[i]].c_str(), scores[i]);
	  
            cv::putText(frame, label, cv::Point(boxes[i].x, boxes[i].y - 5), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 1);
                
            cv::imshow("frame", frame);

            if(cv::waitKey(1) != -1)
            {
                camera.release();
                std::cout << "Terminado pelo usuário\n";
                break;
            }
        }
    }
    
    cv::destroyAllWindows();
    return 0;
}

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
        nomes.push_pack(linha);
    }

    cv::dnn::Net net cv::dnn::readNetFromDarknet("yolov4-tiny.weights", "yolov4-tiny.cfg");

    cv::dnn:DetectionModel model = cv::dnn::DetectionModel(net);
    model.setInputParams( 1/255.0, cv::Size(416, 416), cv::Scalar(), true);

	cv::VideoCapture camera;
    cv::Mat frame;
    bool cap = camera.open(0);

    std::vector<std::vector<int>> colors = {{0, 255, 0}, {0, 0, 255}, {255, 0, 0},
                   {255, 255, 0}, {255, 0, 255}, {0, 255, 255}};

    if (cap)
    {
        while (true)
        {
            bool ret = camera.read();
            cap >> frame;
            if (!ret)
            {
                break;
            }

            std::vector<int> classes;
            std::vector<float> scores;
            std::vector<cv::Rect> boxes;

            model.detect(frame, classes, scores, boxes, 0.6, 0.4);

            for (int i = 0; i < classes.size(); i++)
            {
                color = colors[i % colors.size()];

                cv::rectangle(frame, boxes[i], color);

                char label[100];
                snprintf(text, sizeof(label), "%s: %.2f", nomes[classes[i]].c_str(), scores[i]);
                cv::putText(frame, label, cv::Point(boxes[i].x, boxes[i].y - 10), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
                
                cv::imshow('frame', frame);

                auto key = (char) cv::waitKey(1);
                if (key == 27)
                    break;
            }
        }
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
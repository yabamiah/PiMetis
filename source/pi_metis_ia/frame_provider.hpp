#ifndef FRAME_PROVIDER_HPP
#define FRAME_PROVIDER_HPP

#include <opencv2/opencv.hpp>
#include <mutex>

class FrameProvider {
public:
    FrameProvider();

    void update_frame(const cv::Mat& new_frame);

    cv::Mat get_frame();

private:
    cv::Mat frame;
    std::mutex frame_mutex;
};

#endif // FRAME_PROVIDER_HPP

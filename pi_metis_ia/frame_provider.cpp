#include "frame_provider.hpp"

FrameProvider::FrameProvider() 
    : frame(), frame_mutex() 
{
}

void FrameProvider::update_frame(const cv::Mat& new_frame) 
{
    std::lock_guard<std::mutex> lock(frame_mutex);
    frame = new_frame.clone();    
}

cv::Mat FrameProvider::get_frame() 
{
    std::lock_guard<std::mutex> lock(frame_mutex);
    return frame.clone();    
}
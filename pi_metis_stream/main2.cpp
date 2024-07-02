#include "pi_metis_stream.hpp"

int main() 
{
    VideoStreamer streamer(0, CAP_V4L);
    streamer.start();
    return 0;
}
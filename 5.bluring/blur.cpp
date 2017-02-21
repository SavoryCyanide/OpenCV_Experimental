#include "opencv2/opencv.hpp"

using namespace cv;

Mat greenFilter(const Mat& src); //Prototype

int main(int argc, char** argv)
{
    VideoCapture cap;

    if(!cap.open(0))
        return 0;
    for(;;)
    {
        Mat frame;

        cap >> frame;
        if( frame.empty() ) 
            break; // end of video stream

        Mat onlyGreen = greenFilter(frame);

        imshow("Only green", onlyGreen);

        if( waitKey(1) == 27 ) 
            break; // stop capturing by pressing ESC 
    }
    return 0;
}

Mat greenFilter(const Mat& src)
{
    assert(src.type() == CV_8UC3);

    Mat greenOnly;
    inRange(src, Scalar(0, 50, 0), Scalar(20, 255, 20), greenOnly);

    return greenOnly;
}

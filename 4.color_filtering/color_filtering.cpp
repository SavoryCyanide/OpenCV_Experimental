#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;

Mat greenFilter(const Mat& src); //Prototype

int main(int argc, char** argv)
{
    VideoCapture cap;

    if(!cap.open(0))
        return 0;

     //Create trackbar
    namedWindow("Only green", 1);
    int maxRed = 0;
    createTrackbar("R", "Only green", &maxRed, 255);

    int maxGreen = 0;
    createTrackbar("G", "Only green", &maxGreen, 255);

    int maxBlue = 0;
    createTrackbar("B", "Only green", &maxBlue, 255);
    

    for(;;)
    {
        Mat frame;

        cap >> frame;
        if( frame.empty() ) 
            break; // end of video stream

        Mat onlyGreen = greenFilter(frame, maxRed, maxGreen, maxBlue);

        imshow("Only green", onlyGreen);
        imshow("Regular", frame);

        if( waitKey(1) == 32 )
        {
            imwrite("regular.jpg", frame);
            imwrite("filtered.jpg", onlyGreen);
            std::cout << "frame set saved";
        }

        if( waitKey(1) == 27 ) 
            break; // stop capturing by pressing ESC 
    }
    return 0;
}

Mat greenFilter(const Mat& src, int maxRed, int maxGreen, int maxBlue)
{
    assert(src.type() == CV_8UC3);

    Mat greenOnly;
    inRange(src, Scalar(80, 20, 10), Scalar(maxRed, maxGreen, maxBlue), greenOnly);

    return greenOnly;
}

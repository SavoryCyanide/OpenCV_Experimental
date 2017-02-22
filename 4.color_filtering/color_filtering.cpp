#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;

Mat greenFilter(const Mat& src, int maxRed, int maxGreen, int maxBlue, int minRed, int minGreen, int minBlue); //Prototype

int main(int argc, char** argv)
{
    VideoCapture cap;

    if(!cap.open(0))
        return 0;

    //Create trackbar
    namedWindow("Only green", 1);

    int minRed = 0;
    int minGreen = 0;
    int minBlue = 0;

    int maxRed = 255;
    int maxGreen = 255;
    int maxBlue = 255;

    createTrackbar("Min R", "Only green", &minRed, 255);
    createTrackbar("Max R", "Only green", &maxRed, 255);
    
    createTrackbar("Min G", "Only green", &minGreen, 255);
    createTrackbar("Max G", "Only green", &maxGreen, 255);

    createTrackbar("Min B", "Only green", &minBlue, 255);
    createTrackbar("Max B", "Only green", &maxBlue, 255);

    for(;;)
    {
        Mat frame;

        cap >> frame;
        if( frame.empty() ) 
            break; // end of video stream

        Mat onlyGreen = greenFilter(frame, maxRed, maxGreen, maxBlue, minRed, minGreen, minBlue);

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

Mat greenFilter(const Mat& src, int maxRed, int maxGreen, int maxBlue, int minRed, int minGreen, int minBlue)
{
    assert(src.type() == CV_8UC3);

    Mat greenOnly;
    inRange(src, Scalar(minRed, minGreen, minBlue), Scalar(maxRed, maxGreen, maxBlue), greenOnly);

    return greenOnly;
}

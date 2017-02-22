#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "processing.hpp"
#include <iostream>
using namespace cv;

//Prototypes
Mat colorFilter(const Mat& src, int maxRed, int maxGreen, int maxBlue, int minRed, int minGreen, int minBlue);


int main(int argc, char** argv)
{
    VideoCapture cap;

    if(!cap.open(0))
        return 0;

    //Create trackbar
    namedWindow("Color Filtered", 1);

    int minRed = 0;
    int minGreen = 0;
    int minBlue = 0;

    int maxRed = 179;
    int maxGreen = 255;
    int maxBlue = 255;

    createTrackbar("Min H", "Color Filtered", &minRed, 179);
    createTrackbar("Max H", "Color Filtered", &maxRed, 179);
    
    createTrackbar("Min S", "Color Filtered", &minGreen, 255);
    createTrackbar("Max S", "Color Filtered", &maxGreen, 255);

    createTrackbar("Min V", "Color Filtered", &minBlue, 255);
    createTrackbar("Max V", "Color Filtered", &maxBlue, 255);
    //

    for(;;)
    {
        Mat frame, blurred, filtered;

        cap >> frame;
        if( frame.empty() ) 
            break; // end of video stream

        blurred = blur(frame, kernel, 
        filtered = colorFilter(blurred, maxRed, maxGreen, maxBlue, minRed, minGreen, minBlue);

        imshow("Regular", frame);
        imshow("Blurred", blurred);
        imshow("Color Filtered", filtered);

        if( waitKey(1) == 32 )
        {
            imwrite("regular.jpg", frame);
            imwrite("filtered.jpg", filtered);
            std::cout << "frame set saved";
        }

        if( waitKey(1) == 27 ) 
            break; // stop capturing by holding ESC 
    }
    return 0;
}



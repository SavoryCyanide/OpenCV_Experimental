#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;

//Prototypes
Mat blur(const Mat& src);
Mat colorFilter(const Mat& src, int maxH, int maxS, int maxV, int minH, int minS, int minV);


int main(int argc, char** argv)
{
    VideoCapture cap;

    if(!cap.open(0))
        return 0;

    //Create trackbar
    namedWindow("Color Filtered", 1);
    namedWindow("Blurred", 1);

    int minH = 44;
    int minS = 0;
    int minV = 226;

    int maxH = 84;
    int maxS = 67;
    int maxV = 255;

    createTrackbar("Min H", "Color Filtered", &minH, 179);
    createTrackbar("Max H", "Color Filtered", &maxH, 179);
    
    createTrackbar("Min S", "Color Filtered", &minS, 255);
    createTrackbar("Max S", "Color Filtered", &maxS, 255);

    createTrackbar("Min V", "Color Filtered", &minV, 255);
    createTrackbar("Max V", "Color Filtered", &maxV, 255);

    //true = video , false = picture
    bool videoBool = false;
    String loadPic = "dark.jpg";

    for(;;)
    {
        Mat frame, blurred, filtered;

        if (videoBool == true)
            cap >> frame;
        else
            frame = imread(loadPic, 1);

        if( frame.empty() ) 
            break; // end of video stream

        blurred = blur(frame);
        filtered = colorFilter(blurred, maxH, maxS, maxV, minH, minS, minV);

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

//Blur
Mat blur(const Mat& src)
{
    Mat blurred;

    GaussianBlur(src, blurred, Size(15,15), 0, 0);

    return blurred;
}

//Color filter
Mat colorFilter(const Mat& src, int maxH, int maxS, int maxV, int minH, int minS, int minV)
{
    assert(src.type() == CV_8UC3);
    Mat hsv, filtered, res;

    cvtColor(src, hsv, CV_BGR2HSV); //Converts BGR to HSV for hues
    inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), filtered);
    bitwise_and(src,src,res,filtered = filtered); //Puts color in remaining pixels

    return res;
}

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
using namespace cv;
int main()
{
    VideoCapture cap(0);

    if(!cap.isOpened())
        return -1;

    std::cout << "VideoCapture initialized\n";

    Mat frame;
    std::cout << "Variable frame declared\n";

    cap >> frame;
    std::cout << "Data assigned to frame\n";

    imwrite("pic.jpg", frame);
    std::cout << "Frame saved\n";

    namedWindow("Image", CV_WINDOW_AUTOSIZE);
    std::cout << "Window created";

    imshow("Image", frame);
    std::cout << "Image displayed";

    return 0;
}

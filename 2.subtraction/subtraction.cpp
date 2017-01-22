#include <iostream>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;

int main()
{
    String pointless;
    Mat frame1, frame2, subtracted, cvtGray;
    VideoCapture cap(0);
    std::cout << "Initialized\n";

    //Capture and display unlit frame
    cap >> frame1;
    //namedWindow("Frame1", CV_WINDOW_AUTOSIZE);
    imwrite("frame1.jpg", frame1);
    //imshow("Frame1", frame1);
    std::cout << "Frame1\n";

    //Figure out how to get gpio working
    std::cin >> pointless; 

    //Capture and display lit frame
    cap >> frame2;
    //namedWindow("Frame2", CV_WINDOW_AUTOSIZE);
    imwrite("frame2.jpg", frame2);
    //imshow("Frame2", frame2);
    std::cout << "Frame2";

    //Process images and display results
    subtract(frame1, frame2, subtracted);
    //namedWindow("Subtracted", CV_WINDOW_AUTOSIZE);
    imwrite("subtracted.jpg", subtracted);
    //imshow("Subtracted", subtracted);
    std::cout << "Subtracted";

    //Convert subtracted image to gray (and blur)?
        //cvtColor(sourceImage, destination, option)
    cvtColor(subtracted, cvtGray, CV_BGR2GRAY);
    blur(cvtGray, cvtGray, Size(3,3));
    imwrite("gray/blur.jpg", cvtGray);
    std::cout << "Gray and blur";

    return 0;
}

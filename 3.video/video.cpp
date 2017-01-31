#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
int main() {
    cv::namedWindow( "Example3", cv::WINDOW_AUTOSIZE );
    cv::VideoCapture cap(0);
    cv::Mat frame;

    if(!videoCapture->isOpened())
        throw Exception();

    while( 1 )
    {
        cap >> frame;
        cv::imshow( "Example3", frame );
    }

    return 0;
}

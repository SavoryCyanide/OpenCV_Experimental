#ifndef PROCESSING_HPP
#define PROCESSING_HPP

//Blurred not complete
Mat blur(const Mat& src, kernel //
{
    Mat blurred;

    bilateralFilter(src, blurred, //

    return blurred;
}

Mat colorFilter(const Mat& src, int maxRed, int maxGreen, int maxBlue, int minRed, int minGreen, int minBlue)
{
    assert(src.type() == CV_8UC3);
    Mat hsv, filtered, res;

    cvtColor(src, hsv, CV_BGR2HSV); //Converts BGR to HSV for hues
    inRange(hsv, Scalar(minRed, minGreen, minBlue), Scalar(maxRed, maxGreen, maxBlue), filtered);
    bitwise_and(src,src,res,filtered = filtered); //Puts color in remaining pixels

    return res;
}

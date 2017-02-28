#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

//Prototypes
Mat blur(const Mat& src);
Mat colorFilter(const Mat& src, int maxH, int maxS, int maxV, int minH, int minS, int minV);
Mat contour(const Mat& src, int thresh);
Mat corners(const Mat& src, int thresh);


int main(int argc, char** argv)
{
    VideoCapture cap;

    if(!cap.open(0))
        return 0;

    //Create trackbar
    namedWindow("Color Filtered", 1);
    //namedWindow("Blurred", 1);
    namedWindow("Contour", 1);
    namedWindow("Corner", 1);

    //Starting HSV values
    int minH = 44;
    int minS = 0;
    int minV = 226;

    int maxH = 84;
    int maxS = 67;
    int maxV = 255;

    int cornerThresh = 235;

    createTrackbar("Min H", "Color Filtered", &minH, 179);
    createTrackbar("Max H", "Color Filtered", &maxH, 179);
    
    createTrackbar("Min S", "Color Filtered", &minS, 255);
    createTrackbar("Max S", "Color Filtered", &maxS, 255);

    createTrackbar("Min V", "Color Filtered", &minV, 255);
    createTrackbar("Max V", "Color Filtered", &maxV, 255);

    createTrackbar("Thresh", "Corner", &cornerThresh, 255);

    int contour_thresh = 450;
    createTrackbar("Contour Thresh", "Contour", &contour_thresh, 500);

    //true = video , false = picture
    bool videoBool = false;
    String loadPic = "dark.jpg";

    for(;;)
    {
        Mat frame, blurred, filtered, contoured, corner;

        if (videoBool == true)
            cap >> frame;
        else
            frame = imread(loadPic, 1);

        if (frame.empty())
        {
            cout << "Photo \"" + loadPic + "\" not found, exiting\n";
            break; // end of video stream
        }

        //PROCESSING/////////////////////////
        blurred = blur(frame);
        filtered = colorFilter(blurred, maxH, maxS, maxV, minH, minS, minV);
        contoured = contour(filtered, contour_thresh);
        corner = corners(contoured, cornerThresh);
        ////////////////////////////////////

        imshow("Regular", frame);
        //imshow("Blurred", blurred);
        imshow("Color Filtered", filtered);
        imshow("Contour", contoured);
        imshow("Corner", corner);

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
    bitwise_and(src, src, res, filtered = filtered); //Puts color in remaining pixels

    return res;
}

//Contour
Mat contour(const Mat& src, int thresh)
{
    Mat src_gray, canny_output;

    cvtColor(src, src_gray, CV_HSV2RGB);
    cvtColor(src_gray, src_gray, CV_RGB2GRAY);

    //imshow("Gray", src_gray);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny(src_gray , canny_output, thresh, thresh*2, 3 );

    imshow("canny output", canny_output);

    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

    /// Draw contours
    Mat drawing = Mat::zeros(src.rows, src.cols, CV_8UC3);

    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar(255, 255, 255);
        //drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }
//

    Mat threshold_output;
    threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );

    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    //vector<Point2f>center( contours.size() );
    //vector<float>radius( contours.size() );
    for( size_t i = 0; i < contours.size(); i++ )
    {
      approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
      boundRect[i] = boundingRect( Mat(contours_poly[i]) );
      //minEnclosingCircle( contours_poly[i], center[i], radius[i] );
    }

    for( size_t i = 0; i< contours.size(); i++ )
    {
      Scalar color = Scalar( 0, 255, 0 );
      //drawContours( drawing, contours_poly, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
      rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
      //circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
    }

    return drawing;
}


Mat corners(const Mat& source, int thresh)
{
  Mat src;

  cvtColor(source, src, CV_RGB2GRAY);

  Mat dst, dst_norm, dst_norm_scaled;
  dst = Mat::zeros( src.size(), CV_32FC1 );

  /// Detector parameters
  int blockSize = 2;
  int apertureSize = 3;
  double k = 0.04;

  /// Detecting corners
  cornerHarris( src, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

  /// Normalizing
  normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
  convertScaleAbs( dst_norm, dst_norm_scaled );

  /// Drawing a circle around corners
  for( int j = 0; j < dst_norm.rows ; j++ )
     { for( int i = 0; i < dst_norm.cols; i++ )
          {
            if( (int) dst_norm.at<float>(j,i) > thresh )
              {
               circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
              }
          }
     }

  return dst_norm_scaled;
}

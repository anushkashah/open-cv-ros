#include "ColorFilter.h"

using namespace std;
using namespace cv;

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    showResult();
}

void ColorFilter::split() {
    cv::split(_frame, _chans);
}

void ColorFilter::showResult() {
    // PROBLEM 1
    // cv::imshow("color", _frame);

    // PROBLEM 2: B
    // cv::imshow("blue", _chans[0]);
    // PROBLEM 2: G
    // cv::imshow("green", _chans[1]);
    // PROBLEM 2: R
    // cv::imshow("red", _chans[2]);

    // PROBLEM 3: Blue Subtraction
    // cv::imshow("blue subtraction", _sub);
    // PROBLEM 3: Blue Threshold
    // cv::imshow("blue threshold", _thresh);
    // PROBLEM 3: Blue Mask
    // cv::imshow("blue mask", _mask);
    // PROBLEM 3: Blue Image
    // cv::imshow("blue image", _blue_image);

    // PROBLEM 4: Green Subtraction
    // cv::imshow("green subtraction", _sub);
    // PROBLEM 4: Green Threshold
    // cv::imshow("green threshold", _thresh);
    // PROBLEM 4: Green Mask
    // cv::imshow("green mask", _mask);
    // PROBLEM 4: Green Image
    // cv::imshow("green image", _green_image);

    // PROBLEM 5: Red Subtraction
    // cv::imshow("red subtraction", _sub);
    // PROBLEM 5: Red Threshold
    // cv::imshow("red threshold", _thresh);
    // PROBLEM 5: Red Mask
    // cv::imshow("red mask", _mask);
    // PROBLEM 5: Red Image
    // cv::imshow("red image", _image);

    cv::imshow("all three", _all_image);
    waitKey(200);
}

void ColorFilter::findBlue() {
    subtract(_chans[0], _chans[2], _blue_sub);
    _blue_image = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1); 
    findColorHelper(_blue_sub, _blue_thresh, _blue_image, _blue_mask);
}

void ColorFilter::findGreen() {
    subtract(_chans[1], _chans[0], _green_sub);
    _green_image = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1); 
    findColorHelper(_green_sub, _green_thresh, _green_image, _green_mask);
}

void ColorFilter::findRed() {
    subtract(_chans[2], _chans[1], _red_sub);
    _red_image = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1); 
    findColorHelper(_red_sub, _red_thresh, _red_image, _red_mask);
}

void ColorFilter::findBGR() {
    _all_image = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    _all_mask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1); 

    cv::Mat red_blue_image = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    cv::Mat green_blue_image = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    cv::Mat red_blue_mask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    cv::Mat green_blue_mask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);

    cv::bitwise_or(_red_mask, _blue_mask, red_blue_mask);
    cv::bitwise_or(_blue_mask, _green_mask, green_blue_mask);
    cv::bitwise_or(red_blue_mask, green_blue_mask, _all_mask);

    cv::bitwise_or(_red_image, _blue_image, red_blue_image);
    cv::bitwise_or(_blue_image, _green_image, green_blue_image);
    cv::bitwise_or(red_blue_image, green_blue_image, _all_image);
    
    _frame.copyTo(_all_image, _all_mask);
}

void ColorFilter::findColorHelper(cv::Mat& sub, cv::Mat& thresh, cv::Mat& img, cv::Mat& mask) {
    threshold(sub, thresh, 50, 255, cv::THRESH_BINARY);
    
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if(contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    cv::Mat contourimage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    drawContours(contourimage, contours, maxSizeContour, cv::Scalar(255,255,255),
                    cv::LineTypes::FILLED, 8, hierarchy);

    mask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(mask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    img = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    _frame.copyTo(img, mask);

}
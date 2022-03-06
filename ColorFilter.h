#ifndef COLOR_FILTER_H
#define COLOR_FILTER_H

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

class ColorFilter {
protected:
    cv::Mat _frame;
    std::vector<cv::Mat> _chans;
    cv::Mat _blue_sub;
    cv::Mat _blue_thresh;
    cv::Mat _blue_mask;
    cv::Mat _blue_image;
    cv::Mat _red_sub;
    cv::Mat _red_thresh;
    cv::Mat _red_mask;
    cv::Mat _red_image;
    cv::Mat _green_sub;
    cv::Mat _green_thresh;
    cv::Mat _green_mask;
    cv::Mat _green_image;
    cv::Mat _all_image;
    cv::Mat _all_mask;

public:
    void processImage(cv::Mat img);

    void split();

    void findBlue();
    void findGreen();
    void findRed();
    void findBGR();

    void showResult();

private:
    void findColorHelper(cv::Mat& sub, cv::Mat& thresh, cv::Mat& img, cv::Mat& mask);
};

#endif
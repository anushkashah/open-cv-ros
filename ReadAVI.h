#ifndef READ_AVI_H
#define READ_AVI_H

#include <opencv2/opencv.hpp>

class ColorFilter;

class ReadAVI {
protected:
    ColorFilter &_cf;
    cv::VideoCapture _cap;
    cv::Mat _frame;

public:
    ReadAVI(std::string filename, ColorFilter &cf);
    void processFile();
    void getNextFrame();
    bool nextFrameEmpty();
};

#endif
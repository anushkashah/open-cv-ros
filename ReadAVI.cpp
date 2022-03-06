#include "ReadAVI.h"
#include "ColorFilter.h"

ReadAVI::ReadAVI(std::string filename, ColorFilter &cf) :
    _cf(cf), _cap(filename) {}

void ReadAVI::processFile() {
    getNextFrame();
    while(!nextFrameEmpty()) {
        _cf.processImage(_frame);
        getNextFrame();
    }
}

void ReadAVI::getNextFrame() {
    _cap >> _frame;
}

bool ReadAVI::nextFrameEmpty() {
    return _frame.empty();
}
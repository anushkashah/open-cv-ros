#include "ColorFilter.h"
#include "ReadAVI.h"

using namespace std;
using namespace cv;

int main(int arvc, char **argv) {
    ColorFilter cf;
    ReadAVI ra("./three_cups.avi", cf);
    ra.processFile();
}
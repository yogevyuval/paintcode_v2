#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED
#include <stdio.h>
#include "cv.h"
#include "highgui.h"
using namespace cv;
class Frame
{

public:
    Frame(int width, int height, int type);
    Frame(CvSize size, int type);
    int type;
    static const int CAM_FRAME_WIDTH = 640;
    static const int CAM_FRAME_HEIGHT = 480;
    static const int VIDEO = 0, STILL = 1;
    static IplImage* crop(IplImage* img, int x, int y, int width, int height);
    IplImage* getFrame();
    static IplImage* crop(IplImage* img, Rect r);
};

#endif // FRAME_H_INCLUDED


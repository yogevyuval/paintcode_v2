#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED
#include <opencv/cvaux.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cxcore.hpp>
#include <iostream>
#include "Motion.h"
#include "MotionHandler.h"
using namespace cv;
using namespace std;



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
    static void drawAndShow(Motion* m);
    void drawSquare(MotionHandler* mh);
private:
    IplImage curFrame;

};

#endif // FRAME_H_INCLUDED


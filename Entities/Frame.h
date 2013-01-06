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
    Frame(int width, int height);
    Frame(int width, int height, char* imgPath);
    int type;
    CvSize size;
    IplImage* still;
    static const int VIDEO = 0, STILL = 1;
    IplImage* getFrame();
    void drawAndShow(Motion* m);
    void drawStartSquare(MotionHandler* mh);
    void drawEndSquare(MotionHandler* mh);
private:
    IplImage curFrame;

};

#endif // FRAME_H_INCLUDED


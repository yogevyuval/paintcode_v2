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
    void drawAndShow(Motion* m); // shows a motion on a blank window
    void drawPendingSquare(MotionHandler* mh); // draws the squares for start/end on the current frame
    void drawCand(Candidate * cand); // paints a candidate on the current frame
    void drawMotion(MotionHandler * mh); // draws the notion so far on the current frame
private:
    IplImage* curFrame;
    IplImage* motionTrack;

};

#endif // FRAME_H_INCLUDED


//
//  MotionHandler.h
//  CvTest
//
//  Created by Yuval Yogev on 12/1/12.
//
//

#ifndef __CvTest__MotionHandler__
#define __CvTest__MotionHandler__

#include <iostream>
#include "Motion.h"
#include "Candidate.h"
#include <cvaux.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cxcore.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <iostream>
#include <deque>


using namespace cv;
using namespace std;

class MotionHandler {
public:
    static const int WAITING_FOR_START = 0, //The handler is waiting for the user to start the motion
        RECORDING = 1,         //We got the motion and we are now recording it
        FINISHED = -1;           //The user finished the motion and we can now provide the motion.
    static const int maxRecordSaves = 20; //maximum size of the deque
    Motion getMotion();
    void record();
    void feed(Candidate* cand);
    int getState();
    CvRect getStartSquare();
    CvRect getEndSquare();
    MotionHandler();
    void print();
    bool didStopInSquare(CvRect square);
    Candidate* getLastCandidate();
    bool isInSquare(CvRect rect,Candidate cand);

private:

    deque<Candidate *> recentRecords;
    Motion motion;
    CvRect startSquare;
    CvRect endSquare;
    int currentState;
    void updateState(); //This method will check the right things according to the current state.
    void waiting();
    bool checkForStart();
    bool checkForEnd();
    void recording(Candidate * c);
    void end();
    void addToDeque(Candidate* c);

};

#endif /* defined(__CvTest__MotionHandler__) */

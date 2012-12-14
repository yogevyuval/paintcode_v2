////
////  MotionHandler.h
////  CvTest
////
////  Created by Yuval Yogev on 12/1/12.
////
////
//
//#ifndef __CvTest__MotionHandler__
//#define __CvTest__MotionHandler__
//
//#include <iostream>
//#include "Motion.h"
//#include "Candidate.h"
//#include <cvaux.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <cxcore.hpp>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <assert.h>
//#include <math.h>
//#include <float.h>
//#include <limits.h>
//#include <time.h>
//#include <ctype.h>
//#include <math.h>
//#include <iostream>
//
//#endif /* defined(__CvTest__MotionHandler__) */
//
//class MotionHandler {
//public:
//    typedef enum{
//        WAITING_FOR_START, //The handler is waiting for the user to start the motion
//        RECORDING,         //We got the motion and we are now recording it
//        FINISHED           //The user finished the motion and we can now provide the motion.
//    }state;
//    //Motion getMotion(); I need the motion class for this.
//    void record();
//    void feed(Candidate cand);
//    state getState();
//
//private:
//    state currentState;
//    Rect toSearch = Rect(20,20,50 ,50);
//    void updateState(); //This method will check the right things according to the current state.
//    bool checkForStart(Candidate c);
//    bool checkForEnd();
//
//};


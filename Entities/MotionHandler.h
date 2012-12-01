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

#endif /* defined(__CvTest__MotionHandler__) */

class MotionHandler {
public:
    typedef enum{
        WAITING_FOR_START, //The handler is waiting for the user to start the motion
        RECORDING,         //We got the motion and we are now recording it
        WAITING_FOR_END,   //The handler is waiting for the user to end the motion
        FINISHED           //The user finished the motion and we can now provide the motion.
    }state;
    //Motion getMotion(); I need the motion class for this.
    void start();
    void feed(Candidate cand);
    state getState();
    
private:
    state currentState;
    void updateState(); //This method will check the right things according to the current state.
    bool checkForStart();
    bool checkForEnd();
    
};
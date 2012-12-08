////
////  MotionHandler.cpp
////  CvTest
////
////  Created by Yuval Yogev on 12/1/12.
////
////
//
//#include "MotionHandler.h"
//
//void MotionHandler::feed(Candidate cand)
//{
//    if(MotionHandler::currentState == MotionHandler::state.WAITING_FOR_START)
//    {
//        if(checkForStart(cand))
//            MotionHandler::currentState = MotionHandler::state.RECORDING;
//    }
//    else if(MotionHandler::currentState == MotionHandler::state.RECORDING){}
//    else if(MotionHandler::currentState == MotionHandler::state.FINISHED){}
//        return;
//}
//
//bool MotionHandler::checkForStart(Candidate c)
//{
//    float x = c.getX(), y = c.getY(), r = c.getRadius();
//    if(x > 20 && x < 70 && y > 20 && y < 70){
//        return true;
//    }
//    return false;
//}

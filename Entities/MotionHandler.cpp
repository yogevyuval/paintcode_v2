//
//  MotionHandler.cpp
//  CvTest
//
//  Created by Yuval Yogev on 12/1/12.
//
//

#include "MotionHandler.h"

MotionHandler::MotionHandler()
{
    currentState = MotionHandler::WAITING_FOR_START;
    toSearch = cvRect(20, 20, 50, 50);
    MotionHandler::m = Motion();
}

int MotionHandler::getState()
{
    return currentState;
}

void MotionHandler::feed(Candidate* cand)
{
    if(currentState == MotionHandler::WAITING_FOR_START)
    {
        if(checkForStart(cand))
            currentState = MotionHandler::RECORDING;
    }
    else if(currentState == MotionHandler::RECORDING){
        addToDeque(cand);
        //just for testing...
        if(!checkForStart(cand))
            currentState = MotionHandler::WAITING_FOR_START;
    }
    else if(currentState == MotionHandler::FINISHED){}
        return;
}

bool MotionHandler::checkForStart(Candidate* c)
{
    float x = c->getX(), y = c->getY(), r = c->getRadius();
    if(x > toSearch.x && x < toSearch.x + toSearch.width && y > toSearch.y && y < toSearch.y + toSearch.height){
        cout << "!!!" << endl;
        return true;
    }
    return false;
}

Motion MotionHandler::getMotion()
{
    return m;
}

CvRect MotionHandler::getSearchArea()
{
    return MotionHandler::toSearch;
}

void MotionHandler::addToDeque(Candidate * c)
{
    recentRecords.push_front(c);
        if(recentRecords.size() > maxRecordSaves)
        {
            recentRecords.pop_front();
        }
}

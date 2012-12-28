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
    startSquare = cvRect(150, 150, 150, 150);
    endSquare = cvRect(10, 10, 150, 150);
    MotionHandler::motion = Motion();
}

int MotionHandler::getState()
{
    return currentState;
}

void MotionHandler::feed(Candidate* cand)
{
    addToDeque(cand);
    if(currentState == MotionHandler::WAITING_FOR_START)
    {
        waiting();
    }
    else if(currentState == MotionHandler::RECORDING){
        recording(cand);
    }
    else if(currentState == MotionHandler::FINISHED){}
    print();
}


void MotionHandler::waiting(){
    if(checkForStart()){
        currentState = MotionHandler::RECORDING;
        cout << "Started!" << endl;
    }
}

void MotionHandler::recording(Candidate * cand){
    if(cand!=NULL){
        MotionHandler::motion.add(cand);
    }
    if(checkForEnd()){
        cout << "Finished" << endl;
        currentState = MotionHandler::FINISHED;
    }
}

bool MotionHandler::isInSquare(CvRect rect, Candidate cand){
    float x = cand.getX(), y = cand.getY(), r = cand.getRadius();
    return (!(x - r<rect.x || x + r>rect.x + rect.width ||
              y - r<rect.y || y + r>rect.y + rect.height));
}

bool MotionHandler::checkForStart()
{
    return didStopInSquare(startSquare);
}

bool MotionHandler::checkForEnd(){
    return didStopInSquare(endSquare);
}
bool MotionHandler::didStopInSquare(CvRect square){
    if(recentRecords.size() == 0){
        cout << "size is 0" << endl;
        return false;
    }
    int counter = 0;
    for (int i = 0; i<recentRecords.size(); i++) {
        Candidate * cand = recentRecords[i];
        if(isInSquare(square, *cand)){
            counter++;
        }
    }
    //>79% of candidates are inside the rect;
    return counter/recentRecords.size() > 0.79;
}

Motion MotionHandler::getMotion()
{
    return motion;
}

CvRect MotionHandler::getStartSquare()
{
    return MotionHandler::startSquare;
}

CvRect MotionHandler::getEndSquare()
{
    return MotionHandler::endSquare;
}

void MotionHandler::addToDeque(Candidate * c)
{
    if (c == NULL) {
//        recentRecords.pop_back();
        return;
    }
    recentRecords.push_front(c);
    if(recentRecords.size() > maxRecordSaves)
    {
        recentRecords.pop_back();
    }
}

void MotionHandler::print(){
//    deque<Candidate *>::iterator itr;
//    for(itr = recentRecords.begin();itr != recentRecords.end(); itr++){
//        Candidate * cand = *itr;
//        cout << cand->getX() << " ";
//    }
//    cout << endl;
    for (int i = 0; i<recentRecords.size(); i++) {
//        cout<< (*recentRecords[i]).getY() << " ";
//        cout<<recentRecords.size();
    }

}

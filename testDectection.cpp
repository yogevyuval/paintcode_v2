//
//  testDectection.cpp
//  CvTest
//
//  Created by Yuval Yogev on 11/24/12.
//
//

#include "Detection/Detector.h"
#include "Entities/Frame.h"
#include "Entities/Motion.h"
#include "Entities/MotionHandler.h"
#include <cmath>
#include <iostream>
#include <fstream>




float lastX1 = -1;
float lastY1 = -1;
IplImage* imgTrack;

void paint(IplImage * frame, Candidate * cand){
    if(cand==NULL)
        return;
    float x = cand->getX();
    float y = cand->getY();
    float r = cand->getRadius();
    int calcx = -1;
    int calcy = -1;
    float diffX = abs(x-lastX1);
    float diffY = abs(y-lastY1);
    
    if(diffX < 3)
        x = lastX1;
    
    if (diffY < 3) {
        y = lastY1;
    }
    
    if(lastX1>=0 && lastY1>=0 && x>=0 && y>=0)
        cvLine(imgTrack, cvPoint(x, y), cvPoint(lastX1, lastY1), cvScalar(0,0,255), 6);

    cvCircle( frame, cvPoint(cvRound(x),cvRound(y)),
             3, CV_RGB(0,255,0), -1, 8, 0 );
    cvCircle( frame, cvPoint(cvRound(x),cvRound(y)),
             cvRound(r), CV_RGB(255,0,0), 3, 8, 0 );
//    cvRectangle(frame, cvPoint(x-r/2,y-r/2), cvPoint(x+r/2, y+r/2), CV_RGB(0,255,0));
    
    lastX1 = x;
    lastY1 = y;
}

int main(int argc, char* argv[])
{
    Frame input = Frame(640, 480);
    IplImage* frame = input.getFrame();
    imgTrack=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U, 3);
    cvZero(imgTrack);
    CvSize size = cvGetSize(frame);
    Detector detector = Detector(size);
    cvNamedWindow( "TR", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "Camera", CV_WINDOW_AUTOSIZE );
    MotionHandler motionHandler = MotionHandler();
    while(1)
    {
        frame = input.getFrame();
        detector.processFrame(frame);
        Candidate* bestCand = detector.getBestCandidate();
        paint(frame, bestCand);
        motionHandler.feed(bestCand);
        CvScalar color;
        CvPoint start,end;
        if (motionHandler.getState()==MotionHandler::WAITING_FOR_START) {
            start = cvPoint(150,150);
            end = cvPoint(300,300);
            color = cvScalar(255,0,0);
        }
        else if(motionHandler.getState() == MotionHandler::RECORDING){
            start = cvPoint(10,10);
            end = cvPoint(160,160);
            color = cvScalar(0,0,255);
        }
        else if(motionHandler.getState() == MotionHandler::FINISHED){
            start = cvPoint(10,10);
            end = cvPoint(160,160);
            color = cvScalar(0,255,0);
        }
        
        cvRectangle(frame, start, end, color);
        
        cvAdd(frame, imgTrack, frame);
        cvShowImage( "TR", detector.getThresholdedFrame() );
        cvShowImage( "Camera", frame );
        cvMoveWindow("TR", 600, 50);

        if( (cvWaitKey(10) & 255) == 27 ) break;//ESC
    }
    cvDestroyWindow( "TR" );
    cvDestroyWindow( "Camera" );
    return 0;
}

//int main_detection(int argc, char* argv[])
//{
//
//    // Default capture size - 640x480
//
//    IplImage* frame = Frame::getFrame(Frame::VIDEO);
//    CvSize size = cvGetSize(frame);
//    Detector detector = Detector(size);
//    if( !frame )
//    {
//        fprintf( stderr, "ERROR: capture is NULL \n" );
//        getchar();
//        return -1;
//    }
//    cvNamedWindow( "Camera", CV_WINDOW_AUTOSIZE );
//    cvNamedWindow( "Filtered", CV_WINDOW_AUTOSIZE );
//
//    while(1)
//    {
//        // Get one frame
//        IplImage* frame = Frame::getFrame(Frame::VIDEO);
//        if( !frame )
//        {
//            fprintf( stderr, "ERROR: frame is null...\n" );
//            getchar();
//            break;
//        }
//        detector.processFrame(frame);
//        paint(frame, detector.getBestCandidate());
//        cvShowImage( "Filtered", detector.getThresholdedFrame() );
//        cvShowImage( "Camera", frame );
//
//        if( (cvWaitKey(10) & 255) == 27 ) break;
//    }
//    cvDestroyWindow( "mywindow" );
//    return 0;
//}

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
int main(int argc, char* argv[])
{
    Frame input = Frame(640, 480);
    IplImage* frame = input.getFrame();
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
        motionHandler.feed(bestCand);
        input.drawPendingSquare(&motionHandler);
        input.drawCand(bestCand);
        // I have no idea why, but this draws points instead of lines
        input.drawMotion(&motionHandler);

        cvShowImage( "TR", detector.getThresholdedFrame() );
        cvShowImage( "Camera", frame );
        cvMoveWindow("TR", 600, 50);

        if( (cvWaitKey(10) & 255) == 27 ) break;//ESC
    }
    cvDestroyWindow( "TR" );
    cvDestroyWindow( "Camera" );
    return 0;
}

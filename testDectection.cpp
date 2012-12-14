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
//    cvCircle( frame, cvPoint(cvRound(x),cvRound(y)),
//             cvRound(r), CV_RGB(255,0,0), 3, 8, 0 );
//    cvRectangle(frame, cvPoint(x-r/2,y-r/2), cvPoint(x+r/2, y+r/2), CV_RGB(0,255,0));
    
    lastX1 = x;
    lastY1 = y;
}

int main(int argc, char* argv[])
{
   
//    Motion myMotion= Motion();
    // Default capture size - 640x480

    CvCapture* capture = cvCaptureFromCAM( 0 );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 640 );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 480 );
    IplImage* frame = cvQueryFrame( capture );
    imgTrack=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U, 3);
    cvZero(imgTrack); //covert the image, 'imgTracking' to black
//    IplImage* frame = Frame::getFrame(Frame::VIDEO);
    CvSize size = cvGetSize(frame);
    Detector detector = Detector(size);
    if( !frame )
    {
        fprintf( stderr, "ERROR: capture is NULL \n" );
        getchar();
        return -1;
    }
    cvNamedWindow( "Camera", CV_WINDOW_AUTOSIZE );
//    cvNamedWindow( "Filtered", CV_WINDOW_AUTOSIZE );
    while(1)
    {

        // Get one frame
        IplImage* frame = cvQueryFrame( capture );

//        IplImage *roiImage = Frame::crop(frame, x,y,add,add);
        if( !frame )
        {
            fprintf( stderr, "ERROR: frame is null...\n" );
            getchar();
            break;
        }
        detector.processFrame(frame);
        paint(frame, detector.getBestCandidate());
//        cvRectangle(frame, cvPoint(x, y),cvPoint(x+add, y+add), CV_RGB(0,255,0));
//        cvShowImage( "Filtered", roiImage );
        cvAdd(frame, imgTrack, frame);
        cvShowImage( "Camera", frame );
//        cvShowImage( "TR", detector.getThresholdedFrame() );
//        myMotion.add(detector.getBestCandidate());
        if( (cvWaitKey(10) & 255) == 27 ) break;
//        if( cvWaitKey(10) == 'ESC' ) {
//            myMotion.save();
//        }

        
    }
    cvDestroyWindow( "mywindow" );
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

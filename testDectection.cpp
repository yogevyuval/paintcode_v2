//
//  testDectection.cpp
//  CvTest
//
//  Created by Yuval Yogev on 11/24/12.
//
//

#include "Detection/Detector.h"
#include "Entities/Frame.h"
void paint(IplImage * frame, Candidate * cand){
    if(cand==NULL)
        return;
    float x = cand->getX();
    float y = cand->getY();
    float r = cand->getRadius();

    if((x-r) < 300 || (x+r) > 410 || (y-r) < 100 || (y+r)>210)
        return

    cvCircle( frame, cvPoint(cvRound(x),cvRound(y)),
             3, CV_RGB(0,255,0), -1, 8, 0 );
    cvCircle( frame, cvPoint(cvRound(x),cvRound(y)),
             cvRound(r), CV_RGB(255,0,0), 3, 8, 0 );
    cvRectangle(frame, cvPoint(x-r/2,y-r/2), cvPoint(x+r/2, y+r/2), CV_RGB(0,255,0));
}

int main(int argc, char* argv[])
{

    int x = 300;
    int y = 100;
    int add = 130;

    // Default capture size - 640x480

    IplImage* frame = Frame::getFrame(Frame::VIDEO);
    CvSize size = cvGetSize(frame);
    Detector detector = Detector(size);
    if( !frame )
    {
        fprintf( stderr, "ERROR: capture is NULL \n" );
        getchar();
        return -1;
    }
    cvNamedWindow( "Camera", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "Filtered", CV_WINDOW_AUTOSIZE );
    while(1)
    {

        // Get one frame
        IplImage* frame = Frame::getFrame(Frame::VIDEO);
        IplImage *roiImage = Frame::crop(frame, x,y,add,add);
        if( !frame )
        {
            fprintf( stderr, "ERROR: frame is null...\n" );
            getchar();
            break;
        }
        detector.processFrame(frame);
        paint(frame, detector.getBestCandidate());
        cvRectangle(frame, cvPoint(x, y),cvPoint(x+add, y+add), CV_RGB(0,255,0));
        cvShowImage( "Filtered", roiImage );
        cvShowImage( "Camera", frame );

        if( (cvWaitKey(10) & 255) == 27 ) break;
    }
    cvDestroyWindow( "mywindow" );
    return 0;
}

int main_detection(int argc, char* argv[])
{

    // Default capture size - 640x480

    IplImage* frame = Frame::getFrame(Frame::VIDEO);
    CvSize size = cvGetSize(frame);
    Detector detector = Detector(size);
    if( !frame )
    {
        fprintf( stderr, "ERROR: capture is NULL \n" );
        getchar();
        return -1;
    }
    cvNamedWindow( "Camera", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "Filtered", CV_WINDOW_AUTOSIZE );

    while(1)
    {
        // Get one frame
        IplImage* frame = Frame::getFrame(Frame::VIDEO);
        if( !frame )
        {
            fprintf( stderr, "ERROR: frame is null...\n" );
            getchar();
            break;
        }
        detector.processFrame(frame);
        paint(frame, detector.getBestCandidate());
        cvShowImage( "Filtered", detector.getThresholdedFrame() );
        cvShowImage( "Camera", frame );

        if( (cvWaitKey(10) & 255) == 27 ) break;
    }
    cvDestroyWindow( "mywindow" );
    return 0;
}

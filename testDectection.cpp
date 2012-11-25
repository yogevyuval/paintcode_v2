//
//  testDectection.cpp
//  CvTest
//
//  Created by Yuval Yogev on 11/24/12.
//
//

#include "Detection/Detector.h"
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
    
    // Open capture device. 0 is /dev/video0, 1 is /dev/video1, etc.
    CvCapture* capture = cvCaptureFromCAM( 0 );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 640 );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 480 );
    IplImage* frame = cvQueryFrame( capture );
    CvSize size = cvGetSize(frame);
    Detector detector = Detector(size);
    if( !capture )
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
        IplImage* frame = cvQueryFrame( capture );
        
        Rect cropRect = Rect(x,y,add,add);
        cvSetImageROI(frame, cropRect);
        IplImage *roiImage = cvCreateImage(cvGetSize(frame), frame->depth,
                                           frame->nChannels);
        
        cvCopy(frame, roiImage, NULL);
        cvResetImageROI(frame);
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
    cvReleaseCapture( &capture );
    cvDestroyWindow( "mywindow" );
    return 0;
}

int main_detection(int argc, char* argv[])
{
    
    // Default capture size - 640x480
    
    // Open capture device. 0 is /dev/video0, 1 is /dev/video1, etc.
    CvCapture* capture = cvCaptureFromCAM( 0 );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 640 );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 480 );
    IplImage* frame = cvQueryFrame( capture );
    CvSize size = cvGetSize(frame);
    Detector detector = Detector(size);
    if( !capture )
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
        IplImage* frame = cvQueryFrame( capture );
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
    cvReleaseCapture( &capture );
    cvDestroyWindow( "mywindow" );
    return 0;
}
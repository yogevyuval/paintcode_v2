//
//  Frame.cpp
//
//  Created by Shira Asa-El on 11/27/12.
//
//


#include "Frame.h"

CvCapture* capture;
IplImage* frame;


Frame::Frame(int width, int height)
{
    capture = cvCaptureFromCAM( 0 );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, width );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, height );
    Frame::type = Frame::VIDEO;
    Frame::size = cvSize(width, height);
}

Frame::Frame(int width, int height,char* imgPath)
{
    Frame::type = Frame::STILL;
    Frame::size = cvSize(width, height);
    IplImage *original = cvLoadImage(imgPath);
    if(!original){
        cout << "Error: Bad Image Path!" << endl;
        exit(1);
    }
    still = cvCreateImage(cvSize(width, height), original->depth, original->nChannels);
    cvResize(original, still);
}

IplImage* Frame::getFrame()
{
    if(type == Frame::VIDEO)
    {
        if(!capture)
        {
            cout << "Error: Capture is NULL" << endl;
            exit(1);
        }
        frame = cvQueryFrame( capture );
        if(!frame){
            cout << "Error: Frame is NULL!" << endl;
            exit(1);
        }
        return frame;
    }
    else if(type == Frame::STILL)
    {
        return still;
    }
}

void Frame::drawAndShow(Motion* m)
{
    IplImage* show = cvCreateImage(Frame::size,IPL_DEPTH_8U, 3);
    Candidate *c1, *c2;
    for(int i = 1; i < m->length(); i++)
    {
        c1 = m->getCandidate(i - 1);
        c2 = m->getCandidate(i);
        cout<<c1->getX() << ", " << c2->getX()<<endl;
        cvLine(show, cvPoint(c1->getX(), c1->getY()), cvPoint(c2->getX(), c2->getY()), cvScalar(0,0,255), 6,8,0);
    }

    cvNamedWindow( "Motion", CV_WINDOW_AUTOSIZE );
    cvShowImage( "Motion", show );
}


void Frame::drawStartSquare(MotionHandler * mh)
{
    CvRect square = mh->getStartSquare();
    CvScalar color;
    if(mh->didStopInSquare(square)) {color = cvScalar(0, 255, 0);}
    else {color = cvScalar(255, 0, 0);}
    cvRectangle(&curFrame, cvPoint(square.x, square.y), cvPoint(square.x + square.width, square.y + square.height), color, 1, 8, 0);
}

void Frame::drawEndSquare(MotionHandler * mh)
{
    CvRect square = mh->getEndSquare();
    CvScalar color;
    if(mh->didStopInSquare(square)) {color = cvScalar(0, 255, 0);}
    else {color = cvScalar(255, 0, 0);}
    cvRectangle(&curFrame, cvPoint(square.x, square.y), cvPoint(square.x + square.width, square.y + square.height), color, 1, 8, 0);
}

//
//  Frame.cpp
//
//  Created by Shira Asa-El on 11/27/12.
//
//


#include "Frame.h"

CvCapture* capture;


Frame::Frame(int width, int height)
{
    capture = cvCaptureFromCAM( 0 );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, width );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, height );
    Frame::type = Frame::VIDEO;
    Frame::size = cvSize(width, height);
    Frame::motionTrack=cvCreateImage(size,IPL_DEPTH_8U, 3);
    cvZero(Frame::motionTrack);
}

Frame::Frame(int width, int height,char* imgPath)
{
    Frame::type = Frame::STILL;
    Frame::size = cvSize(width, height);
    IplImage *original = cvLoadImage(imgPath);
    if(!original)
    {
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
        curFrame = cvQueryFrame( capture );
        if(!curFrame)
        {
            cout << "Error: Frame is NULL!" << endl;
            exit(1);
        }
        return curFrame;
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


void Frame::drawPendingSquare(MotionHandler * mh)
{
    CvRect square;
    CvScalar color = cvScalar(255, 0, 0);
    if(mh->getState() == MotionHandler::WAITING_FOR_START)
    {
        square = mh->getStartSquare();
    }
    else if (mh->getState() == MotionHandler::RECORDING)
    {
        square = mh->getEndSquare();
    }
    else {return;}
    Candidate* last = mh->getLastCandidate();
    if(last && mh->isInSquare(square, *last))
    {
        color = cvScalar(255, 0, 0);
    }
    else
    {
        color = cvScalar(0, 255, 0);
    }
    cvRectangle(curFrame, cvPoint(square.x, square.y), cvPoint(square.x + square.width, square.y + square.height), color, 1, 8, 0);
}

void Frame::drawCand(Candidate * cand)
{
    if(cand==NULL)
        return;
    float x = cand->getX();
    float y = cand->getY();
    float r = cand->getRadius();
    cvCircle( curFrame, cvPoint(cvRound(x),cvRound(y)),
             3, CV_RGB(0,255,0), -1, 8, 0 );
    cvCircle( curFrame, cvPoint(cvRound(x),cvRound(y)),
             cvRound(r), CV_RGB(255,0,0), 3, 8, 0 );
}

// For some reason draws points instead of lines
void Frame::drawMotion(MotionHandler * mh)
{
    if (mh == NULL)
        return;
    if (mh->getState() == MotionHandler::RECORDING)
    {
        Motion motion = mh->getMotion();
        if(motion.length() < 2)
            return;
        // Here's the problem - cur and last are the same
        Candidate *last = motion.getCandidate(0),
            *cur = motion.getCandidate(1);
        float lastX = last->getX(),
            lastY = last->getY(),
            x = cur->getX(),
            y = cur->getY();
        cout << "last: " << lastX << ", " << lastY << endl;
        cout << "cur: " << x << ", " << y << endl;
        cvLine(motionTrack, cvPoint(x, y), cvPoint(lastX, lastY), cvScalar(0,0,255), 6);
        cvAdd(curFrame, motionTrack, curFrame);
    }
}

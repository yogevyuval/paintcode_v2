//
//  Frame.cpp
//
//  Created by Shira Asa-El on 11/27/12.
//
//


#include "Frame.h"

CvCapture* capture;
IplImage* frame;


Frame::Frame(int width, int height,int type)
{

    capture = cvCaptureFromCAM( 0 );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, width );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, height );
    Frame::type = type;
    // on video - initialize curFrame:
    getFrame();
}


IplImage* Frame::crop(IplImage* img, int x, int y, int width, int height)
{
    Rect cropRect = Rect(x,y,width ,height);
    cvSetImageROI(img, cropRect);
    IplImage *roiImage = cvCreateImage(cvGetSize(img), img->depth,
                                       img->nChannels);
    cvCopy(img, roiImage, NULL);
    cvResetImageROI(img);
    return roiImage;
}

IplImage* Frame::crop(IplImage* img, Rect r)
{
    cvSetImageROI(img, r);
    IplImage *roiImage = cvCreateImage(cvGetSize(img), img->depth,
                                       img->nChannels);
    cvCopy(img, roiImage, NULL);
    cvResetImageROI(img);
    return roiImage;
}

IplImage* Frame::getFrame()
{
    if(type == Frame::VIDEO)
    {
        if(!capture)
        {
            return NULL;
        }
        frame = cvQueryFrame( capture );
        cvCopy(&frame, &curFrame, NULL);
        return frame;
    }
    else if(type == Frame::STILL)
    {
        return cvLoadImage( "../Dog.jpg", CV_LOAD_IMAGE_COLOR );
    }
}

void Frame::drawAndShow(Motion* m)
{
    IplImage* show = cvCreateImage(cvSize(CAM_FRAME_WIDTH, CAM_FRAME_HEIGHT),IPL_DEPTH_8U, 3);
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


void Frame::drawSquare(MotionHandler * mh)
{

}

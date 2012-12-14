//
//  Frame.cpp
//
//  Created by Shira Asa-El on 11/27/12.
//
//


#include "Frame.h"

CvCapture* capture;
IplImage* frame;


Frame::Frame(int width, int height,int type){
    
    capture = cvCaptureFromCAM( 0 );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, width );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, height );
    Frame::type = type;
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

IplImage* Frame::crop(IplImage* img, Rect r){
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
        return frame;
    }
    else if(type == Frame::STILL)
    {
        return cvLoadImage( "../Dog.jpg", CV_LOAD_IMAGE_COLOR );
    }
}

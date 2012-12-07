//
//  Frame.cpp
//
//  Created by Shira Asa-El on 11/27/12.
//
//

#include <cvaux.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cxcore.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <iostream>
#include "../Entities/Frame.h"

using namespace std;
using namespace cv;

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

IplImage* Frame::getFrame(int type)
{
    if(type == Frame::VIDEO)
    {
        CvCapture* capture = cvCaptureFromCAM( 0 );
        cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, Frame::CAM_FRAME_WIDTH );
        cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, Frame::CAM_FRAME_HEIGHT );
        if(!capture)
        {
            return NULL;
        }
        IplImage* img = cvQueryFrame( capture );
        return img;
    }
    else if(type == Frame::STILL)
    {
        return cvLoadImage( "../Dog.jpg", CV_LOAD_IMAGE_COLOR );
    }
}

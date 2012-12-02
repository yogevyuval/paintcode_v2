//
//  Detector.cpp
//  CvTest
//
//  Created by Yuval Yogev on 11/24/12.
//
//

#include "Detector.h"

/**
 Detector constructor -
    Currently gets just the capture size.
 */
Detector::Detector(CvSize size){

    Detector::hsv_frame   = cvCreateImage(size, IPL_DEPTH_8U, 3);
    Detector::thresholded = cvCreateImage(size, IPL_DEPTH_8U, 1);
    /////ORNAGE/////
    Detector::hsv_min = cvScalar(5, 50, 50, 0);
    Detector::hsv_max = cvScalar(20, 256, 255, 0);
    ////BLUE////
//    Detector::hsv_min = cvScalar( 104, 178, 70  );
//    Detector::hsv_max = cvScalar( 130, 240, 124 );
}

IplImage * Detector::getHSVFrame(){return Detector::hsv_frame;}
IplImage * Detector::getThresholdedFrame(){return Detector::thresholded;}

Candidate * Detector::getBestCandidate(){
    return Detector::best;
}

/**
 This is the main method that the detector works with. It get's the currnt frame
 and proccess it, until we get the best candidate.
 */
void Detector::processFrame(IplImage *frame){
    Detector::frame = frame;
    applyFilters(frame);
    houghTransform(Detector::thresholded);

    chooseCandidate();
    if(candidates.size() > 0){
        cout << candidates.at(0).getScore() << endl;
    }
}

/**
 This method applys the different filters on the frame such as
 HSV conversion, smoothing and so on.
 */
void Detector::applyFilters(IplImage *frame){

    // Covert color space to HSV as it is much easier to filter colors in the HSV color-space.
    cvCvtColor(frame, hsv_frame, CV_BGR2HSV);
    // Filter out colors which are out of range.
    cvInRangeS(hsv_frame, hsv_min, hsv_max, thresholded);
    // hough detector works better with some smoothing of the image
    cvSmooth( thresholded, thresholded, CV_BLUR, 15, 15 );
    cvErode(thresholded,thresholded,NULL,2);
    //        cvMorphologyEx(thresholded, thresholded, storage, NULL, CV_MOP_CLOSE, 2);
    cvSmooth( thresholded, thresholded, CV_BLUR, 15, 15 );
}


/**
 Circle detection
 Currently the parameters are hardcoded.
 builds the candidates list.
 */
vector<Candidate> Detector::houghTransform(IplImage *thresholded){
    Detector::candidates.clear();
    // Memory for hough circles
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* circles = cvHoughCircles(thresholded, storage, CV_HOUGH_GRADIENT, 2,
                                    thresholded->height/3, 140, 50, 15, 100);

    for (int i = 0; i < circles->total; i++){

        float* p = (float*)cvGetSeqElem( circles, i );
        float x = p[0];
        float y = p[1];
        float r = p[2];
        candidates.push_back(Candidate(x, y, r));
    }

    return Detector::candidates;
}

/*
 This method is important! It chooses from the candidates list
 the best candidate by a list of preoperties.
 */
void Detector::chooseCandidate(){
    rateColor();
    sort(candidates.begin(), candidates.end(),Candidate::compareCands);
    if (candidates.size()>0) {
        Detector::best = &candidates.at(0);
    }
    else{
        Detector::best = NULL;
    }


}

/*
 This method gives score to each candidate by the color of the candidate.
 */
void Detector::rateColor(){
        for (int i = 0; i < candidates.size(); i++){
        double distanceFromOrange = 0;
        Candidate *curCand = &candidates.at(i);
        int x = curCand->getX();
        int y = curCand->getY();
        int r = curCand->getRadius();

        if(x-(r/2) < 0 || y-(r/2) < 0 || x+(r/2) + 2 > frame->width  || y+(r/2)  + 2> frame->height)
            continue;
        Rect cropRect = Rect(x-(r/2),y-(r/2),r,r);
        cvSetImageROI(Detector::frame, cropRect);
        IplImage *roiImage = cvCreateImage(cvGetSize(Detector::frame), Detector::frame->depth,
                                           Detector::frame->nChannels);

        cvCopy(Detector::frame, roiImage, NULL);
        cvResetImageROI(Detector::frame);

        IplImage *  hsv_test    = cvCreateImage(cvSize(roiImage->width, roiImage->height), IPL_DEPTH_8U, 3);
        cvCvtColor(roiImage, hsv_test, CV_BGR2HSV);
        IplImage*  thresholded   = cvCreateImage(cvSize(roiImage->width, roiImage->height), IPL_DEPTH_8U, 1);
        cvInRangeS(hsv_test, hsv_min, hsv_max, thresholded);
        cvShowImage( "Ball", thresholded );
        cvMoveWindow("Ball", 600, 50);

        for (int i = 0; i < thresholded->height; i++)
        {
            for (int j = 0; j < thresholded->width; j += 1){
                int pixel = cvGet2D( thresholded , i, j).val[0];
                distanceFromOrange += pixel == 255 ? 1 : 0;
            }
        }
        distanceFromOrange = distanceFromOrange/(thresholded->height*thresholded->width);
        curCand->increase(distanceFromOrange);
    }
}

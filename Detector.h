//
//  Detector.h
//  CvTest
//
//  Created by Yuval Yogev on 11/24/12.
//
//

#ifndef CvTest_Detector_h
#define CvTest_Detector_h
#include "Candidate.h"
#include <opencv/cvaux.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cxcore.hpp>
#include "vector.h"
#include <iostream>

using namespace std;
using namespace cv;


class Detector{
public:
    Detector(CvSize size);
    Candidate * getBestCandidate();
    void processFrame(IplImage * frame);
    IplImage * getHSVFrame();
    IplImage * getThresholdedFrame();
    IplImage * getFrame();
    
    
private:
    Candidate * best;
    vector<Candidate> candidates;
    IplImage * frame;
    IplImage * hsv_frame;
    IplImage * thresholded;
    /////ORNAGE/////
    CvScalar hsv_min;
    CvScalar hsv_max;
    void applyFilters(IplImage * frame);
    void chooseCandidate();
    vector<Candidate> houghTransform(IplImage* thresholded);
    void rateColor();
};


#endif

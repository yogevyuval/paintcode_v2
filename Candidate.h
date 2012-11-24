//
//  Candidate.h
//  CvTest
//
//  Created by Yuval Yogev on 11/24/12.
//
//

#ifndef CvTest_Candidate_h
#define CvTest_Candidate_h

class Candidate {
    
public:
    Candidate();
    Candidate(int x, int y, int r);
    int getX();
    int getY();
    int getRadius();
private:
    int x,y;
    int radius;
};

#endif

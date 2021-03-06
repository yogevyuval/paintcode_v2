//
//  Candidate.h
//  CvTest
//
//  Created by Yuval Yogev on 11/24/12.
//
//

#ifndef CvTest_Candidate_h
#define CvTest_Candidate_h
#include <string>
using namespace std;
class Candidate {
    
public:
    Candidate();
    Candidate(int x, int y, int r);
    int getX();
    int getY();
    double getScore();
    void increase(double score);
    int getRadius();
    static bool compareCands(Candidate cand1, Candidate cand2);
    void setX(int x);
    void setY(int y);
    void setRadius(int radius);
    void setScore(double score);
    string toString();
private:
    int x,y;
    int radius;
    double score;
};

#endif

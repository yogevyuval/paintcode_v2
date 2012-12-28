//
//  Motion.h
//  PaintCode_V2
//
//  Created by Michael Lantsman on 11/25/12.
//  Copyright (c) 2012 Michael Lantsman. All rights reserved.
//

#ifndef MOTION_H_
#define MOTION_H_

#include <iostream>
#include "Candidate.h"
#include <vector>

using namespace std;

class Motion{
public:
    Motion();
    void start();
    void stop();
    int compare(Motion m2);
    int save(string id);
    Motion load(string id);
    void smooth();
    void add(Candidate * c);
    int length();
    Candidate * getCandidate(int i);
    
    
private:
    int compareByLength(Motion m2);
    int compareByRadius(Motion m2);
    int compareByNumberOfCandidates(Motion m2);
    Candidate * firstCandidte;
    Candidate * lastCandidate;
    vector <Candidate *> sequence;
    
    
};

#endif //Defined
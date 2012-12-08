//
//  testSave.cpp
//  PaintCode_V2
//
//  Created by Michael Lantsman on 12/8/12.
//  Copyright (c) 2012 Michael Lantsman. All rights reserved.
//

#include "testSave.h"
#include "Entities/Motion.h"
#include "Entities/Candidate.h"
int main(){
    Candidate cand1 = Candidate(1,2,3);
    Candidate cand2 = Candidate(12,22,32);
    Candidate cand3 = Candidate(13,23,33);
    Motion motion = Motion();
    motion.add(&cand1);
    motion.add(&cand2);
    motion.add(&cand3);
    motion.save();
    return 0;
}

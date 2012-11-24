#include <iostream>
using namespace std;
//
//  Candidate.cpp
//  CvTest
//
//  Created by Yuval Yogev on 11/24/12.
//
//

#include "Candidate.h"
Candidate::Candidate(){
    //Empty
}

Candidate::Candidate(int x,int y, int r){
    Candidate::x = x;
    Candidate::y = y;
    Candidate::radius = r;
}

int Candidate::getX(){
    return Candidate::x;
}

int Candidate::getY(){
    return Candidate::y;
}

int Candidate::getRadius(){
    return Candidate::radius;
}

int main(){
    Candidate cand1 = Candidate(1, 2, 3);
    Candidate cand2 = Candidate(3,2,1);
    cout << cand1.getX() + cand2.getX();
    return 0;
}
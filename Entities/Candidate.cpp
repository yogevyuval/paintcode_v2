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
    Candidate::score = 0;
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

double Candidate::getScore(){
    return Candidate::score;
}

void Candidate::increase(double score){
    Candidate::score+= score;
}

bool Candidate::compareCands(Candidate cand1, Candidate cand2){
    return (cand1.getScore()>cand2.getScore());

}

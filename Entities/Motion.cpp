//
//  Motion.cpp
//  PaintCode_V2
//
//  Created by Michael Lantsman on 11/25/12.
//  Copyright (c) 2012 Michael Lantsman. All rights reserved.
//

#include "Motion.h"
#include "Candidate.h"
#include <iostream>
#include <fstream>


Motion::Motion(){
    
}

void Motion::add( Candidate * c1){
    Motion::sequence.push_back(c1);
   
}

int Motion::save(){
    std::ofstream myfile;
    myfile.open ("DB\DB.txt");
    if (myfile.is_open()) {
        cout<< "open";
        myfile<<"yay";
    }
    for(int i=0;i<length();i++){
        cout<<"in";
        myfile << getCandidate(i)->toString()+";";
        cout<< getCandidate(i)->toString()+";";
    }
    myfile.close();
    return 0;
}
Motion Motion::load(int id){
    int NUM_OF_FIELDS=1;
    ifstream myReadFile;
    myReadFile.open(id + ".txt");
    string line="";
    
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            getline(myReadFile,line);
            for (int i=0; i<NUM_OF_FIELDS; i++) {
                
            }
        }
    }
    myReadFile.close();
    return Motion();
}

Candidate * Motion::getCandidate(int i){
    return Motion::sequence.at(i);
}

int Motion::length(){
    return Motion::sequence.size();
}

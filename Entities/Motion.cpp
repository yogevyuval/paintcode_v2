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
#include <regex.h>


Motion::Motion(){
    
}

void Motion::add( Candidate * c1){
    Motion::sequence.push_back(c1);
}

int Motion::save(Motion m1){
    std::ofstream myfile;
    myfile.open ("DB.txt");
    
    for(int i=0;i<m1.length();i++){
        myfile << (*m1.getCandidate(i)).toString();
    }
    myfile.close();
    return 0;
}
Motion Motion::load(int id){
    ifstream myReadFile;
    myReadFile.open(to_string(id)+".txt");
    string line="";
    
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            
            getline(myReadFile,line);
            
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

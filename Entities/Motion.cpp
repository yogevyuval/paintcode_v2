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


int Motion::save(string  id){
    std::ofstream myfile;
    myfile.open ("DB/"+id+".txt",ios::app);
    Candidate c;
    if(myfile.is_open()){
        for(int i=0;i<length();i++){
            c= * getCandidate(i);
            myfile << c.getX()<<"\n";
            myfile << c.getY()<<"\n";
            myfile << c.getRadius()<<"\n";
            myfile << c.getScore()<<"\n";
        }
    }
    else{
        cout<<"failed to open file";
    }
    myfile.close();
    return 0;
}
Motion Motion::load(string id){
    int NUM_OF_FIELDS=4;//change if needed
    
    ifstream myReadFile;
    myReadFile.open("DB/"+ id + ".txt");
    string line="";
    Motion m=Motion();
    Candidate c;
    int i=0,x=0,y=0,radius=0;
    if (myReadFile.is_open()) {
        cout<<"file is open";
        getline(myReadFile,line);
        while (!myReadFile.eof()) {
            if(i%NUM_OF_FIELDS==0){
                x=atoi(line.c_str());
            }
            else if(i%NUM_OF_FIELDS==1)
                y=atoi(line.c_str());
            else if(i%NUM_OF_FIELDS==2){
                radius=atoi(line.c_str());
            }else if(i%NUM_OF_FIELDS==3){
                c=Candidate(x, y, radius);
                c.setScore(atof(line.c_str()));
                m.add(&c);
            }
            i++;
            getline(myReadFile,line);
        }
    }
    myReadFile.close();
    return m;
}

Candidate * Motion::getCandidate(int i){
    return Motion::sequence.at(i);
}

int Motion::length(){
    return Motion::sequence.size();
}

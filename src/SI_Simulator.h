//
//  SI_Simulator.h
//  Insection_Simulator
//
//  Created by Nick Chao on 3/22/17.
//
//

#ifndef SI_Simulator_h
#define SI_Simulator_h

#include "Car.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ofMain.h"

using namespace std;

class SI_Simulator: public ofBaseApp
{
private:
    vector<Car> list;
    string filename;
public:
    SI_Simulator();
    SI_Simulator(string datafile);
    void readDataFile();
    void printData();
    void alignCars();
    vector<Car> getCarList();
};


#endif /* SI_Simulator_h */

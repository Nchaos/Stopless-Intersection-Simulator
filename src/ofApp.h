#pragma once

#include "ofMain.h"
#include "Car.h"
#include <fstream>
#include <vector>
#include <algorithm>

class ofApp : public ofBaseApp{
    
    private:
        vector<Car*> list; // Master List of Cars
        string filename;
        vector<int> hori;
        vector<int> vert;
    
        vector<Car*> horizonal; // Cars in the horizontal danger zone
        vector<Car*> vertical; // Cars in the vertical danger zone
        int collisions = 0;
        float speed_limit = 13.4; // 30mph = 13.4 m/s
    
    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofApp(string filename);
    
        void readDataFile();
        void printData(vector<Car*>);
        void printTimeData(vector<Car*>);
        void alignCars();
        void checkForSouthEastCollisions();
        void collision_algorithm();
        void sortFIFOTime(vector<Car*>&);
        void sortFIFODistance(vector<Car*>&);
    

		
};

//bool compareCarStartTimes(Car* a, Car* b)
//{
//    return (a->getCarStart() < b->getCarStart());
//}

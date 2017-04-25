#pragma once

#include "ofMain.h"
#include "Car.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>

class ofApp : public ofBaseApp{
    
    private:
        vector<Car*> list; // Master List of Cars
        string filename;
    
        vector<Car*> westCars;
        vector<Car*> northCars;
    
        vector<Car*> horizonal; // Cars in the horizontal danger zone
        vector<Car*> vertical; // Cars in the vertical danger zone
        int collisions = 0;
        float speed_limit = 1.34; // 30mph = 13.4 m/s
        int number_cars = 0;
        bool pause = false;
        bool stopless_algorithm = true;
        bool pass = true;
        double begTime;
        double seconds = 10.0;
        ofImage street;
    
    
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
        void sortFIFOTime(vector<Car*>&); // V2I
        void sortFIFODistance(vector<Car*>&); // V2I
        void doNotPass();
        void sortDistance(vector<Car*>&, bool); // V2V
        
        void start();
        unsigned long elapsedTime();
        bool isTimeout(unsigned long seconds);
    

		
};

//bool compareCarStartTimes(Car* a, Car* b)
//{
//    return (a->getCarStart() < b->getCarStart());
//}

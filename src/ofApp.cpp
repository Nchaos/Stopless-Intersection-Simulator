#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofTranslate(400, 400);
    ofSetBackgroundColor(0, 0, 0);
    ofSetColor(255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Checks danger zone cars
    checkForSouthEastCollisions();
    collision_algorithm();
    
    // Updates the position of all cars
    for(int i = 0; i < list.size(); i++)
    {
        if(list.at(i)->getDir()) // north/south
        {
            list.at(i)->setYPos(list.at(i)->getYPos() + list.at(i)->getSpeed());
            if((list.at(i)->getYPos() >= -50.0) && (list.at(i)->getYPos() <= 50.0))
            {
                if(!list.at(i)->getCollision())
                {
                    if(!list.at(i)->getDanger())
                    {
                        list.at(i)->setDanger(true);
                        vert.push_back(i);          // Delete this later
                        vertical.push_back(list.at(i));
                        list.at(i)->setColor(255, 0, 0);
                    }
                }
            }
        }
        else // east/west
        {
            list.at(i)->setXPos(list.at(i)->getXPos() + list.at(i)->getSpeed());
            if((list.at(i)->getXPos() >= -50.0) && (list.at(i)->getXPos() <= 50.0))
            {
                if(!list.at(i)->getCollision())
                {
                    if(!list.at(i)->getDanger())
                    {
                        list.at(i)->setDanger(true);
                        hori.push_back(i);          // Delete this later
                        horizonal.push_back(list.at(i));
                        list.at(i)->setColor(255, 0, 0);
                    }
                }
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(400, 400);
    
    int vertSize = vertical.size();
    int horiSize = horizonal.size();
    
    
    // List Trackers
    ofSetColor(0, 255, 0);
    ofDrawBitmapString("Vertical Cars in Traffic Zone: \t\t" + ofToString(vertSize), -375, -380);
    ofDrawBitmapString("Horizontal Cars in Traffic Zone: \t" + ofToString(horiSize), -375, -370);
    ofDrawBitmapString("Cars in Collisions: \t\t\t" + ofToString(collisions), -375, -360);
    
    // Intersection lines
    ofSetColor(255, 255, 255);
    ofDrawLine(-400, -10, 400, -10);
    ofDrawLine(-400, 0, 400, 0);
    ofDrawLine(-400, 10, 400, 10);
    
    ofDrawLine(-10, -400, -10, 400);
    ofDrawLine(0, -400, 0, 400);
    ofDrawLine(10, -400, 10, 400);
    
    
    // Danger Zone
    ofNoFill();
    ofDrawRectangle(-50,-50,100,100);
    ofFill();
    
    
    for(int i = 0; i < list.size(); i++)
    {
        float locx = list.at(i)->getXPos();
        float locy = list.at(i)->getYPos();
        //cout << "Location x: " << locx << endl;
        //cout << "Location y: " << locy << endl;
        ofSetColor(list.at(i)->getRed(), list.at(i)->getGreen(), list.at(i)->getBlue());
        ofDrawCircle(locx, locy, 5.0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
ofApp::ofApp(string datafile){
    ifstream fileReader;
    fileReader.open(ofToDataPath(filename).c_str() );

    filename = datafile;
    readDataFile();
    alignCars();
    //printData(list);
}
//--------------------------------------------------------------
void ofApp::readDataFile()
{
    ifstream file;
    
    file.open(ofToDataPath(filename).c_str() );
    
    string s_id;
    string s_speed;
    string s_xpos;
    string s_ypos;
    string s_north;
    while(!file.eof())
    {
        
        /*
         Reading Data from file
         */
        file >> s_id;
        file >> s_speed;
        file >> s_xpos;
        file >> s_ypos;
        file >> s_north;
        
        //cout << "ID: " << s_id << " Speed: " << s_speed << endl;
        
        int i_id = stoi(s_id);
        float f_speed = (stof(s_speed)/100);
        float f_xpos = stof(s_xpos);
        float f_ypos = stof(s_ypos);
        bool b_north;
        if (s_north.compare("true") == 0)
            b_north = true;
        else
            b_north = false;
        
        /*
         Creating Car object
         Adding it to the list
         */
        Car *newCar = new Car(i_id, b_north, f_speed, f_xpos, f_ypos);
        list.push_back(newCar);
        
    }

}
//--------------------------------------------------------------
void ofApp::printData(vector<Car*> carList)
{
    for (int i = 0; i < carList.size(); i++)
    {
        cout << "Car: " << (i+1) << endl;
        carList.at(i)->print();
        cout << endl;
    }    
}
//--------------------------------------------------------------
void ofApp::printTimeData(vector<Car*> carList)
{
    for (int i = 0; i < carList.size(); i++)
    {
        cout << "Car: " << (i+1) << endl;
        carList.at(i)->printTime();
        cout << endl;
    }
}
//--------------------------------------------------------------
void ofApp::alignCars()
{
    for (int i = 0; i < list.size(); i++)
    {
        list.at(i)->alignCoordinates();
    }
}
//--------------------------------------------------------------
void ofApp::checkForSouthEastCollisions()
{
    for (int i = 0; i < vertical.size(); i++)   // North/South
    {
        if((vertical.at(i)->getYPos() <= -50.0) || (vertical.at(i)->getYPos() >= 50.0))
        {
            if(!vertical.at(i)->getCollision())
            {
                vertical.at(i)->setColor(0, 255, 0);
            }
            // Remove from Vertical List and from danger zone
            vertical.at(i)->setDanger(false);
            vertical.erase(vertical.begin() + i);
            
        }
        else if((vertical.at(i)->getYPos() >= 0.0) && (vertical.at(i)->getYPos() <= 10.0)) // checks for collisions
        {
            for(int j = 0; j < horizonal.size(); j++)
            {
                if((horizonal.at(j)->getXPos() >= -10.0) && horizonal.at(j)->getXPos() <= 0.0 )
                {
                    // Collision
                    if(!horizonal.at(j)->getCollision())
                    {
                        horizonal.at(j)->setCollision(true);
                        horizonal.at(j)->setColor(0, 0, 255);
                        collisions++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < horizonal.size(); i++)
    {
        if((horizonal.at(i)->getXPos() <= -50.0) || (horizonal.at(i)->getXPos() >= 50.0))
        {
            if(!horizonal.at(i)->getCollision())
            {
                horizonal.at(i)->setColor(0, 255, 0);
            }
            // Remove from Horizonal List and from danger zone
            horizonal.at(i)->setDanger(false);
            horizonal.erase(horizonal.begin() + i);
            
        }
        else if((horizonal.at(i)->getXPos() >= -10.0) && (horizonal.at(i)->getXPos() <= 0.0)) // checks for collisions
        {
            for(int j = 0; j < vertical.size(); j++)
            {
                if((vertical.at(j)->getYPos() >= 0.0) && (vertical.at(j)->getYPos() <= 10.0))
                {
                    // Collision
                    if(!vertical.at(j)->getCollision())
                    {
                        vertical.at(j)->setCollision(true);
                        vertical.at(j)->setColor(0, 0, 255);
                        collisions++;
                    }
                }
            }
        }
    }

}
//--------------------------------------------------------------
void ofApp::collision_algorithm()
{
    vector<Car*> timeSort;
    // Go through Vert/Horizonal lists and set collision times
    // Add them to a timeSort list
    for (int i = 0; i < vertical.size(); i++)
    {
        vertical.at(i)->setCarStart(fabs((vertical.at(i)->getYPos() - 0.0) / vertical.at(i)->getSpeed()));
        vertical.at(i)->setCarEnd(fabs((vertical.at(i)->getYPos() - 10.0) / vertical.at(i)->getSpeed()));
        vertical.at(i)->setCarCollisionTime(vertical.at(i)->getCarEnd() - vertical.at(i)->getCarStart());
        vertical.at(i)->setCarDistance(fabs(vertical.at(i)->getYPos() - 10.0));
        if(vertical.at(i)->getCarCollisionTime() > 0.0)
        {
            timeSort.push_back(vertical.at(i));
        }
    }
    for (int i = 0; i < horizonal.size(); i++)
    {
        horizonal.at(i)->setCarStart(fabs((horizonal.at(i)->getXPos() - 0.0) / horizonal.at(i)->getSpeed()));
        horizonal.at(i)->setCarEnd(fabs((horizonal.at(i)->getXPos() - 10.0) / horizonal.at(i)->getSpeed()));
        horizonal.at(i)->setCarCollisionTime(horizonal.at(i)->getCarEnd() - horizonal.at(i)->getCarStart());
        horizonal.at(i)->setCarDistance(fabs(horizonal.at(i)->getXPos() - 10.0));
        if(horizonal.at(i)->getCarCollisionTime() > 0.0)
        {
            timeSort.push_back(horizonal.at(i));
        }
    }
    
    // Sort Cars by FIFO
    sortFIFOTime(timeSort);
    //sortFIFODistance(timeSort);
    //printData(timeSort);
    printTimeData(timeSort);
    
    
/*
 The biggest issue is that i prioritize the first car in the list over all cars
 When there are too many cars in the "danger zone" then there is not enough time for the remaining cars to change veolicity to avoid collisions.
 
 for loop over everycar in the "danger zone". 
 set first car to speed limit
 set second car speed as fast to arrive 500ms after the second car
 
 
 fucnction for V2V to spread out cars in the same lane
 */
    // Setting first car to speed limit
    
    for (int i = 0; i < timeSort.size(); i++)
    {
        timeSort.at(0)->setSpeed(speed_limit);
        if(timeSort.at(i)->getDir())
        {
            timeSort.at(i)->setCarStart(fabs((timeSort.at(i)->getYPos() - 0.0) / timeSort.at(i)->getSpeed()));
            timeSort.at(i)->setCarEnd(fabs((timeSort.at(i)->getYPos() - 10.0) / timeSort.at(i)->getSpeed()));
            timeSort.at(i)->setCarCollisionTime(timeSort.at(i)->getCarEnd() - timeSort.at(i)->getCarStart());
            timeSort.at(i)->setCarDistance(fabs(timeSort.at(i)->getYPos() - 10.0));
        }
        else
        {
            timeSort.at(i)->setCarStart(fabs((timeSort.at(i)->getXPos() - 0.0) / timeSort.at(i)->getSpeed()));
            timeSort.at(i)->setCarEnd(fabs((timeSort.at(i)->getXPos() - 10.0) / timeSort.at(i)->getSpeed()));
            timeSort.at(i)->setCarCollisionTime(timeSort.at(i)->getCarEnd() - timeSort.at(i)->getCarStart());
            timeSort.at(i)->setCarDistance(fabs(timeSort.at(i)->getXPos() - 10.0));
        }
        if(i > 0)
        {
            float timeBuffer = timeSort.at(i-1)->getCarEnd() + 100;
            float distance = timeSort.at(i-1)->getCarDistance();
            float speed = distance/timeBuffer;
            if(speed < speed_limit)
                timeSort.at(i)->setSpeed(speed);
        }
    }
    
    

    
}
//--------------------------------------------------------------
void ofApp::sortFIFOTime(vector<Car*>& timeSort)
{
    if(!timeSort.empty()) // only sort if not empty
    {
        for (int i = 0; i < timeSort.size(); i++)
        {
            for (int j = 0; j < timeSort.size() - 1; j++)
            {
                if ( timeSort.at(j)->getCarStart() > timeSort.at(j+1)->getCarStart())
                {
                    Car *swap = timeSort.at(j);
                    (timeSort.at(j)) = (timeSort.at(j+1));
                    (timeSort.at(j+1)) = swap;
                }
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::sortFIFODistance(vector<Car*>& timeSort)
{
    if(!timeSort.empty()) // only sort if not empty
    {
        for (int i = 0; i < timeSort.size(); i++)
        {
            for (int j = 0; j < timeSort.size() - 1; j++)
            {
                if ( timeSort.at(j)->getCarDistance() > timeSort.at(j+1)->getCarDistance())
                {
                    Car *swap = timeSort.at(j);
                    (timeSort.at(j)) = (timeSort.at(j+1));
                    (timeSort.at(j+1)) = swap;
                }
            }
        }
    }
    
}

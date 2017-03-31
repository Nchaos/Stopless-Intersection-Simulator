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
        float f_speed = (stof(s_speed)/100.0);
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
        if(horizonal.at(i)->getCarCollisionTime() > 0.0)
        {
            timeSort.push_back(horizonal.at(i));
        }
    }
    
    // Sort Cars by FIFO
    sortFIFO(timeSort);
    //printData(timeSort);
    printTimeData(timeSort);
    
    // Go through timeSort vector
    // Start with first Car
    // figure out which direction the car is going/ which cars could conflict
    // go through the rest of the vector, if they are in a conflicting direction check for possible collision
    // Possible collision involves if the second car's start time is less than the first cars end time
    // if no, do nothing
    // if yes, speed up car 1, slow down car 2
    
    bool direction; // Find priority
    if(timeSort.size() != 0)
    {
        direction = timeSort.at(0)->getDir();
    }
    
    
    
    
    for (int i = 1; i < timeSort.size(); i++)
    {
        float carEnd = timeSort.at(0)->getCarEnd();
        if(direction != timeSort.at(i)->getDir())
        {
            //Conflict Cars
            float carStart = timeSort.at(i)->getCarStart();
            if(carStart < carEnd)
            {
                // Conflict!!!
                //timeSort.at(0)->setSpeed(timeSort.at(0)->getSpeed()+ 0.01); //Speed up first car
                //timeSort.at(i)->setSpeed(timeSort.at(i)->getSpeed()- 0.01); //Slow down second car
                float timeDiff = carEnd - carStart;
                timeSort.at(0)->setSpeed(timeSort.at(0)->getSpeed() + (timeDiff/200));
                timeSort.at(i)->setSpeed(timeSort.at(i)->getSpeed() - (timeDiff/200));
                
                
            }
        }
    }
    
    
    
    
    
    
}
//--------------------------------------------------------------
void ofApp::sortFIFO(vector<Car*>& timeSort)
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

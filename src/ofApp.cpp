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
    //collision_algorithm();
    
    // Updates the position of all cars
    for(int i = 0; i < list.size(); i++)
    {
        if(list.at(i).getDir()) // north/south
        {
            list.at(i).setYPos(list.at(i).getYPos() + list.at(i).getSpeed());
            if((list.at(i).getYPos() >= -50.0) && (list.at(i).getYPos() <= 50.0))
            {
                if(!list.at(i).getCollision())
                {
                    if(!list.at(i).getDanger())
                    {
                        list.at(i).setDanger(true);
                        vert.push_back(i);
                        list.at(i).setColor(255, 0, 0);
                    }
                }
            }
        }
        else // east/west
        {
            list.at(i).setXPos(list.at(i).getXPos() + list.at(i).getSpeed());
            if((list.at(i).getXPos() >= -50.0) && (list.at(i).getXPos() <= 50.0))
            {
                if(!list.at(i).getCollision())
                {
                    if(!list.at(i).getDanger())
                    {
                        list.at(i).setDanger(true);
                        hori.push_back(i);
                        list.at(i).setColor(255, 0, 0);
                    }
                }
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(400, 400);
    
    int vertSize = vert.size();
    int horiSize = hori.size();
    
    
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
        float locx = list.at(i).getXPos();
        float locy = list.at(i).getYPos();
        //cout << "Location x: " << locx << endl;
        //cout << "Location y: " << locy << endl;
        ofSetColor(list.at(i).getRed(), list.at(i).getGreen(), list.at(i).getBlue());
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
    //printData();
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
        Car newCar(i_id, b_north, f_speed, f_xpos, f_ypos);
        list.push_back(newCar);
        
    }

}
//--------------------------------------------------------------
void ofApp::printData()
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << "Car: " << (i+1) << endl;
        list.at(i).print();
        cout << endl;
    }    
}
//--------------------------------------------------------------
void ofApp::alignCars()
{
    for (int i = 0; i < list.size(); i++)
    {
        list.at(i).alignCoordinates();
    }
}
//--------------------------------------------------------------
void ofApp::checkForSouthEastCollisions()
{
    for(int i = 0; i < list.size(); i++)
    {
        if(list.at(i).getDanger())
        {
            if(list.at(i).getDir()) // north/south
            {
                if((list.at(i).getYPos() <= -50.0) || (list.at(i).getYPos() >= 50.0))
                {
                    list.at(i).setDanger(false);
                    for(int c = 0; c < vert.size(); c++)
                    {
                        if (vert.at(c) == i)
                            vert.erase(vert.begin() + c);
                    }
                    if(!list.at(i).getCollision())
                    {
                        list.at(i).setColor(0, 255, 0);
                    }
                }
                else if((list.at(i).getYPos() >= 0.0) && (list.at(i).getYPos() <= 10.0)) // checks for collisions
                {
                    for (int c = 0; c < hori.size(); c++)
                    {
                        if((list.at(hori.at(c)).getXPos() >= -10.0) && (list.at(hori.at(c)).getXPos() <= 0.0))
                        {
                            //cout << "collision" << endl;
                            if(!list.at(hori.at(c)).getCollision())
                            {
                                list.at(hori.at(c)).setCollision(true);
                                list.at(hori.at(c)).setColor(0, 0, 255);
                                collisions++;
                            }
                        }
                    }
                }
            }
            else // east/west
            {
                if((list.at(i).getXPos() <= -50.0) || (list.at(i).getXPos() >= 50.0))
                {
                    list.at(i).setDanger(false);
                    for(int c = 0; c < hori.size(); c++)
                    {
                        if (hori.at(c) == i)
                            hori.erase(hori.begin() + c);
                    }
                    if(!list.at(i).getCollision())
                    {
                        list.at(i).setColor(0, 255, 0);
                    }
                }
                else if((list.at(i).getXPos() >= -10.0) && (list.at(i).getXPos() <= 0.0)) // checks for collisions
                {
                    for (int c = 0; c < vert.size(); c++)
                    {
                        if((list.at(vert.at(c)).getYPos() >= 0.0) && (list.at(vert.at(c)).getYPos() <= 10.0))
                        {
                            //cout << "collision" << endl;
                            if(!list.at(vert.at(c)).getCollision())
                            {
                                list.at(vert.at(c)).setCollision(true);
                                list.at(vert.at(c)).setColor(0, 0, 255);
                                collisions++;
                            }
                        }
                    }
                }
            }
        }
    }

}
//--------------------------------------------------------------
void ofApp::collision_algorithm()
{
    vector<int> queue;
    vector<Car> timeSort;
    // Go through Vert/Horizonal lists and set collision times
    for (int i = 0; i < vert.size(); i++)
    {
        list.at(vert.at(i)).setCarStart(fabs((list.at(vert.at(i)).getYPos() - 0.0)/ (list.at(vert.at(i)).getSpeed())));
        list.at(vert.at(i)).setCarEnd(fabs((list.at(vert.at(i)).getYPos() - 10.0)/ (list.at(vert.at(i)).getSpeed())));
        list.at(vert.at(i)).setCarCollisionTime(list.at(vert.at(i)).getCarEnd() - list.at(vert.at(i)).getCarStart());
        timeSort.push_back(list.at(vert.at(i)));
    }
    for (int i = 0; i < hori.size(); i++)
    {
        list.at(hori.at(i)).setCarStart(fabs((list.at(hori.at(i)).getYPos() - 0.0)/ (list.at(hori.at(i)).getSpeed())));
        list.at(hori.at(i)).setCarEnd(fabs((list.at(hori.at(i)).getYPos() - 10.0)/ (list.at(hori.at(i)).getSpeed())));
        list.at(hori.at(i)).setCarCollisionTime(list.at(hori.at(i)).getCarEnd() - list.at(hori.at(i)).getCarStart());
        timeSort.push_back(list.at(hori.at(i)));
    }
    
    // Sort Cars based on FIFO
    if (!timeSort.empty()) // only sort if not empty
    {
        std::vector<Car>::iterator it;
        for (int i = 0; i < timeSort.size(); i++)
        {
            it = timeSort.begin();
            int low = i;
            
            for (int j = 1+i; j < timeSort.size(); i++)
            {
                if (timeSort.at(j).getCarStart() < timeSort.at(i).getCarStart())
                {
                    //int temp = i;
                    //timeSort.insert()
                    //timeSort.at(i).getCarStart();
                    //low = j;
                    
                }
            }
        }
    }
    
    
    //Sorted?
    for(int i = 0; i < timeSort.size(); i++)
    {
        cout << "Starting................" << endl;
        timeSort.at(i).print();
        cout << "Ending.................." << endl;
    }
    
    // find time until enter collision zone
    // find time until leave collision zone
    // Organize them in a new list based on FIFO
    // New list is called queue
    
    
    
    
}
//--------------------------------------------------------------

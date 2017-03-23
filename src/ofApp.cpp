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
                else if((list.at(i).getYPos() >= -5.0) && (list.at(i).getYPos() <= 5.0)) // checks for collisions
                {
                    for (int c = 0; c < hori.size(); c++)
                    {
                        if((list.at(hori.at(c)).getXPos() >= -5.0) && (list.at(hori.at(c)).getXPos() <= 5.0))
                        {
                            //cout << "collision" << endl;
                            list.at(hori.at(c)).setCollision(true);
                            list.at(hori.at(c)).setColor(0, 0, 255);
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
                else if((list.at(i).getXPos() >= -5.0) && (list.at(i).getXPos() <= 5.0)) // checks for collisions
                {
                    for (int c = 0; c < vert.size(); c++)
                    {
                        if((list.at(vert.at(c)).getYPos() >= -5.0) && (list.at(vert.at(c)).getYPos() <= 5.0))
                        {
                            //cout << "collision" << endl;
                            list.at(vert.at(c)).setCollision(true);
                            list.at(vert.at(c)).setColor(0, 0, 255);
                        }
                    }
                }
            }
        }
    }
    
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
                    list.at(i).setDanger(true);
                    vert.push_back(i);
                    list.at(i).setColor(255, 0, 0);
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
                    list.at(i).setDanger(true);
                    hori.push_back(i);
                    list.at(i).setColor(255, 0, 0);
                }
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(400, 400);
    
    ofSetColor(255, 255, 255);
    ofDrawLine(-400, -5, 400, -5);
    ofDrawLine(-400, 5, 400, 5);
    ofDrawLine(-5, -400, -5, 400);
    ofDrawLine(5, -400, 5, 400);
    
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
        ofDrawCircle(locx, locy, 5);
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

void ofApp::printData()
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << "Car: " << (i+1) << endl;
        list.at(i).print();
        cout << endl;
    }    
}

void ofApp::alignCars()
{
    for (int i = 0; i < list.size(); i++)
    {
        list.at(i).alignCoordinates();
    }
}

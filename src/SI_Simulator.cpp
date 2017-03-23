/*
	Nicholas Chao
	March 21, 2017
	Stopless Intersection Simulator
	SI_Simulator.cpp
*/

#include "SI_Simulator.h"


using namespace std;


SI_Simulator::SI_Simulator()
{
    
}


SI_Simulator::SI_Simulator(string datafile)
{

  	//string datafile = argv[1];
    filename = datafile;
    cout << datafile << endl;
	//vector<Car> list;
	//readDataFile();
	//alignCars();
	//printData();
	
	
}

void SI_Simulator::alignCars()
{
	for (int i = 0; i < list.size(); i++)
	{
		list.at(i).alignCoordinates();
	}
}

void SI_Simulator::printData()
{
	for (int i = 0; i < list.size(); i++)
	{
		cout << "Car: " << (i+1) << endl;
		list.at(i).print();
		cout << endl;
	}
}

void SI_Simulator::readDataFile()
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
		float f_speed = stof(s_speed);
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

vector<Car> SI_Simulator::getCarList()
{
    return list;
}

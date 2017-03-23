/*
	Nicholas Chao
	March 21, 2017
	Car Object
	Car.h
*/
#ifndef H_CAR
#define H_CAR

class Car
{

public: 
	Car(int, bool, float, float, float);
	int getID();
	void setID(int);
	float getSpeed();
	void setSpeed(float);
	float getXPos();
	void setXPos(float);
	float getYPos();
	void setYPos(float);
	bool getDir();
	void setDir(bool);
    float getRed();
    float getBlue();
    float getGreen();
    void setColor(float r, float g, float b);
    bool getDanger();
    void setDanger(bool logic);
    bool getCollision();
    void setCollision(bool logic);

	void print();
	void alignCoordinates();
    

private:

	int id = 0;
	bool dir = true;
	float speed = 0.0;
	float x_pos = 0.0;
	float y_pos = 0.0;
    float red = 255;
    float green = 255;
    float blue = 255;
    bool danger = false;
    bool collision = false;



};


#endif

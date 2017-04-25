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
    float getCarStart();
    void setCarStart(float);
    float getCarEnd();
    void setCarEnd(float);
    float getCarCollisionTime();
    void setCarCollisionTime(float);
    float getCarDistance();
    void setCarDistance(float);

	void print();
    void printTime();
	void alignCoordinates();
    
    

private:

	int id = 0;
	bool dir = true;
	float speed = 0.0;
	float x_pos = 0.0;
	float y_pos = 0.0;
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;
    bool danger = false;
    bool collision = false;
    float carStart = 0.0;
    float carEnd = 0.0;
    float carCollisionTime = 0.0;
    float carDistance;



};



#endif

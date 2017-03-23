#include "ofMain.h"
#include "ofApp.h"
#include "Car.h"

//========================================================================
int main(int argc,char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr,"%s <datafile> <Xcode stuff> <Xcode stuff\n",argv[0]);
        exit(1);
    }
    
    string datafile = argv[1];
	ofSetupOpenGL(800,800,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp(datafile));

}

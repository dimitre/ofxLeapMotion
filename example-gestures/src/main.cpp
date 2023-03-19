//#include "ofMain.h"
//#include "ofApp.h"

#include "ofApp.h"             // for ofApp
#include "ofAppRunner.h"       // for ofRunApp, ofSetupOpenGL
#include "ofWindowSettings.h"  // for OF_WINDOW

int main( ){
	ofSetupOpenGL(600,300,OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofApp());
}

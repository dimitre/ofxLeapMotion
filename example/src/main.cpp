#include "ofApp.h"             // for ofApp
#include "ofAppRunner.h"       // for ofRunApp, ofSetupOpenGL
#include "ofWindowSettings.h"  // for OF_WINDOW

int main( ){
	ofSetupOpenGL(1280, 960, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofApp());
}

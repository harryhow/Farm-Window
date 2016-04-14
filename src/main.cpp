#include "ofMain.h"
#include "ofApp.h"
//#include "ofAppGlutWindow.h"
#include "ofAppGLFWWindow.h" // multiwindow
//#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){
//	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
//
//	// this kicks off the running of my app
//	// can be OF_WINDOW or OF_FULLSCREEN
//	// pass in width and height too:
//	ofRunApp(new ofApp());
    
    //ofAppGlutWindow window;
    ofSetLogLevel(OF_LOG_VERBOSE);
  
// +++ for multiwinow
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
//    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    ofSetupOpenGL(&window, 800, 600, OF_FULLSCREEN);
// ----
    
    //ofSetFullscreen(true);
    ofRunApp(new ofApp());


}

//
//  SlideShow.cpp
//  Farm_Window_AVF
//
//  Created by Harry Chen on 12/28/15.
//
//

#include "SlideShow.h"



SlideShow::SlideShow()
{
    
}

void SlideShow::setup(string photosFolder)
{
    ofDirectory photosDirectory(photosFolder);
    photosDirectory.listDir();
    ofLogVerbose() << photosDirectory.path();
    vector<ofFile> files = photosDirectory.getFiles();
    ofLogVerbose() << "files.size() :" << files.size();
    
    int numFiles = files.size();
    int maxNumFiles = 20;
    for (int i=0; i<files.size(); i++)
    {
        if (images.size()<maxNumFiles)
        {
            ofFile filePath = files[ofRandom(files.size())].path();
            string path = filePath.getAbsolutePath();
            ofLogVerbose() << "file name: " << path;
            
            if (filePath.getExtension() == "jpg" || filePath.getExtension() == "tif")
            {
                ofxGiantImage *image = new ofxGiantImage();
                image->loadImage(path);
                images.push_back(image);
            }
        }
        
        
        
    }
    ofLogVerbose() << "images.size() " << images.size();
    counter = 0;
    currentImage = new ofxGiantImage();
    currentImage = images[counter];
    
    previousImage = new ofxGiantImage();
    previousImage = NULL;
    waitCounter = 0;
    
}

void SlideShow::update(int seq)
{
    counter = seq;
    previousImage = currentImage;
    currentImage = images[counter];
}

void SlideShow::draw()
{
    ofEnableAlphaBlending();
//    if (previousImage != NULL)
//    {
//        ofSetColor(255, 255, 255, 255-transitionColor);
//        previousImage->draw(0, 0, ofGetWidth(), ofGetHeight());
//    }
    ofSetColor(255, 255, 255);
    currentImage->draw(0, 0, ofGetWidth(), ofGetHeight());
    ofDisableAlphaBlending();
    //ofDrawBitmapStringHighlight(ofToString(waitCounter), 20, 20, ofColor::black, ofColor::yellow);
}
//
//  SlideShow.h
//  Farm_Window_AVF
//
//  Created by Harry Chen on 12/28/15.
//
//
#pragma once

#ifndef __Farm_Window_AVF__SlideShow__
#define __Farm_Window_AVF__SlideShow__

#include <stdio.h>
#include "ofMain.h"
#include "ofxGiantImage.h"

#endif /* defined(__Farm_Window_AVF__SlideShow__) */


class SlideShow
{
public:
    SlideShow();
    void setup(string photosFolder);
    void update(int seq);
    void draw();
    vector<ofxGiantImage*> images;
    ofxGiantImage *currentImage;
    ofxGiantImage *previousImage;
    int counter;
    int transitionColor;
    int waitCounter;
};

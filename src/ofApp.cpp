#include "ofApp.h"
#
#ifndef REMOTE_CONTROL
#define REMOTE_CONTROL
#endif


float x;
int y;
ofColor color;

int w = 0;
int i = 0;
int loopCounter = 0;
static const int N_VIDEO_PLAYERS = 2;
string ASSEST_VIDOE_FOLDER = "movies/A/";

int frameJump;

void ofApp::loadVideo(string filename){

    ofDirectory dir;
    dir.open(ASSEST_VIDOE_FOLDER);
    //int numFiles = dir.listDir();
    string path = dir.path() + filename;
    videoPlayers[i]->loadMovie(path);

    
//    ofDirectory dir;
//    dir.open(ASSEST_VIDOE_FOLDER);
//    int numFiles = dir.listDir();
//
//    for (int i = 0; i < numFiles; ++i)
//    {
//        cout << "Path at index [" << i << "] = " << dir.getPath(i) << endl;
//        videoPlayers.push_back(new ofxAVFVideoPlayer());
//        videoPlayers[i]->loadMovie(dir.getPath(i));
//        videoPlayers[i]->setLoopState(OF_LOOP_NORMAL);
//        videoPlayers[i]->play();
//    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    // for single delivery package
    //ofSetDataPathRoot("./");
    
    
    ofDirectory dir;
    dir.open(ASSEST_VIDOE_FOLDER);
    int numFiles = dir.listDir();
    
    for (int i = 0; i < numFiles; ++i)
    {
        cout << "Path at index [" << i << "] = " << dir.getPath(i) << endl;
        videoPlayers.push_back(new ofxAVFVideoPlayer());
        videoPlayers[i]->loadMovie(dir.getPath(i));
        videoPlayers[i]->setLoopState(OF_LOOP_NORMAL);
        videoPlayers[i]->play();
    }
    
    
    // load video
//    for(int i=0; i<N_VIDEO_PLAYERS; i++) {
//        videoPlayers.push_back(new ofxAVFVideoPlayer());
//        videoPlayers[i]->loadMovie("movies/farm_window.mov");
//        videoPlayers[i]->setLoopState(OF_LOOP_NORMAL);
//    }
    
//    // load images
//    imgBottom = new ofImage();
//    imgTop = new ofImage();
//    
//    imgBottom->loadImage("images/L2.jpg");
//    imgTop->loadImage("images/L1.jpg");
    
    
    // load image using ofxGiantImage
    //imgTopx = new ofxGiantImage();
    //imgTopx->loadImage("images/L1.jpg");
    imgTop = new ofxGiantImage();
    imgBottom = new ofxGiantImage();
    imgBottom->loadImage("images/L2.jpg"); //papaya
    imgTop->loadImage("images/L1.jpg");
    
    imgTopPosters.push_back(imgTop);
    
    // enable trace to file
    //ofLogToFile("myLogFile.txt", true);
    
    // initilization
    videoPause = false;
    imageDisplay = false;
    dbgImg = false;
    isDemoMode = false;
    isUpdateImg = false;
    isDownloadImg = false;
    imgRotateIndex = 0;


#ifdef REMOTE_CONTROL
    ////////////////////////////////////////////////////////
    // Remote UI
    
    RUI_SETUP(); //start server
    RUI_SHARE_PARAM(isDemoMode, ofColor(255,0,0,64));
    
    // SET PARAM GROUPS / COLORS //////////////////////////////////
    RUI_NEW_GROUP("Poster");	//make a new group (optional)
    
    // SHARE A STRING PARAM ////////////////////////////////
    strPoster = " ";
    RUI_SHARE_PARAM(strPoster, ofColor(255,0,0,64));	// you can also set a color on a per-param basis
    //Expose x and y vars to the server, providing a valid slider range
    RUI_SHARE_PARAM(x, 0, ofGetWidth());
    RUI_SHARE_PARAM(y, 0, ofGetHeight());
    
    strUpdateFileDate = "";
    RUI_SHARE_PARAM(strUpdateFileDate);
    
    //share the color param
    //RUI_SHARE_COLOR_PARAM(color);
    
    
    // SET PARAM GROUPS / COLORS //////////////////////////////////
    RUI_NEW_GROUP("Video");	//make a new group (optional)
    
    strFruitPrefix = "今天的苹果好好吃，总共有 ";
    strUnit = " 颗";
    currentAppleAmount = "0";
    RUI_SHARE_PARAM(currentAppleAmount, ofColor(255,0,0,64));	// you can also set a color on a per-param basis
    
    
    // SHARE AN ENUM PARAM ////////////////////////////////
    //build a string list for the UI to show
//    menu = MENU_OPTION_1;
//    string menuItems[] = {"MENU_OPTION_0", "MENU_OPTION_1", "MENU_OPTION_2", "MENU_OPTION_3"};
//    //privide the enum param, loweset enum, highest enum, and the Enum string list
//    RUI_SHARE_ENUM_PARAM(menu, MENU_OPTION_0, MENU_OPTION_3, menuItems);
    
    
    // SHARE A string PARAM to unload it later;
    //this is useful in cases where a variable used to be shared,
    //but its value is now on the xml and you still want it loaded
    //but you dont want it to show on the client interface
    //to do so, you first share the param, then load from XML, then remove the param
    unloadTest = "inited from source";
    RUI_SHARE_PARAM(unloadTest);
    
    //load values from XML, as they were last saved (if they were)
    RUI_LOAD_FROM_XML();
    
    //this efectively removes all remoteUI references to this param
    //but bc it's been loaded from xml in the previous step before,
    //the end result is that you get to load its value from XML
    //but it doesnt show in the client.
    //This is meant to be a way to reduce clutter in the client,
    //allowing you to phase out params that have settled down and dont
    //need further editing, but still allowing you to load its value from the xml.
    RUI_REMOVE_PARAM(unloadTest);
    cout << "unloadTest: '" << unloadTest << "'" << endl;
    
    RUI_WATCH_PARAM(currentMouseX); //this will print the supplied param all the time on screen,
    //useful for debugging
    RUI_GET_INSTANCE()->setBuiltInUiScale(3);
    RUI_GET_INSTANCE()->drawUiWithFontStash("SourceHanSansSC-Light.ttf");

#endif
    
    // load font
    unicodeFont.setup("SourceHanSansSC-Light.ttf", //font file, ttf only
                      1.0,					//lineheight percent
                      1024,					//texture atlas dimension
                      true,					//create mipmaps of the font, useful to scale down the font at smaller sizes
                      8,					//texture atlas element padding, shouldbe >0 if using mipmaps otherwise
                      2.0f					//dpi scaleup, render textures @2x the reso
                      );					//lower res mipmaps wil bleed into each other
    
    
    FZLfont.setup("FZLTZCHJW.ttf", //font file, ttf only
                      1.0,					//lineheight percent
                      1024,					//texture atlas dimension
                      true,					//create mipmaps of the font, useful to scale down the font at smaller sizes
                      8,					//texture atlas element padding, shouldbe >0 if using mipmaps otherwise
                      2.0f					//dpi scaleup, render textures @2x the reso
                      );					//lower res mipmaps wil bleed into each other
    
//    char serverPath[512] = "http://www.vim.org/scripts/download_script.php?src_id=7701"; //TODO: move to url list
//    char filePath[256] = "poster_01.zip";
//    
//    char cmd[1024];
//    sprintf(cmd, "curl -o %s %s", filePath, serverPath);
//    cout << "c md:" << cmd << "\n";
//    
//    //char command[] = "curl -o est.zip http://www.vim.org/scripts/download_script.php?src_id=7701";
//    //char command[] = "wget http://www.openss7.org/repos/tarballs/strx25-0.9.2.1.tar.bz2";
//    int status = system(cmd);
    
    
    initTime = ofGetElapsedTimef();
    initTimeDbg = ofGetElapsedTimef();
    ofRegisterURLNotification(this);
    
    // osc
    oscSender.setup(HOST, SENDPORT);
    oscReceiver.setup(RECVPORT);
    
    // send ready
    msgSend.setAddress("/sync/start/FW_SH_02_HBD_A");
    msgSend.addStringArg("ready");
    oscSender.sendMessage(msgSend);

}


//--------------------------------------------------------------
void ofApp::update(){
    
//    int i=0;
//    for(auto p : videoPlayers) {
//        p->update();
//        if(true || p->isLoaded()) {
//            if(ofGetElapsedTimef() > i++ * 0.5)
//                p->play();
//        }
//    }
    
    if (!videoPause) {
        int t = 0;
        for (int j = 0; j < videoPlayers.size(); j++) {
            videoPlayers[j]->update();
            videoPlayers[j]->play();
            
        
//        videoPlayers[i]->update();
//        if (true || videoPlayers[i]->isLoaded()) {
//
//            if (ofGetElapsedTimef() > t++ * 0.5)
//                videoPlayers[i]->play();
//        }
        }
    }
    fps = ofGetFrameRate();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    int frameDiff;
    
    while (oscReceiver.hasWaitingMessages()) {
        cout << "New msg is coming + ";
        ofxOscMessage m;
        oscReceiver.getNextMessage(&m);
        
        if (m.getAddress() == "/sync/play/FW_SH_02_HBD_A/frameJump") {
            frameJump = m.getArgAsInt32(0);
            cout << "Frame sync, jump(" << frameJump << ") frames\r\n";
            
            // do move forward
            videoPlayers[i]->setFrame(frameJump);
        }
        else if (m.getAddress() == "/sync/play/nowPlayingFile") {
            // can I get all the file list from the beginning?
            loadVideo(m.getArgAsString(0));
        }
        else if (m.getAddress() == "/sync/play/nowPlayingStart") {
            isCellStart = m.getArgAsInt32(0);
        }
        else if (m.getAddress() == "/sync/play/nowPlayingStop") {
            isCellStop = m.getArgAsInt32(0);
        }
        else if (m.getAddress() == "/sync/play/type") {
            mediaType = m.getArgAsString(0);
        }
        else if (m.getAddress() == "/sync/play/nowPlayingKickTime") {
            cellKickTime = m.getArgAsInt32(0);
        }
        //dumpOSC(m);
    }
    
    strFruitString =  strFruitPrefix + ofToString(currentAppleAmount) + strUnit;
    
    if (!videoPause) {
//        if (((videoPlayers[i]->getPosition() * videoPlayers[i]->getDuration()) - videoPlayers[i]->getDuration()) == 0){
//            
//            if (i < N_VIDEO_PLAYERS-1) {
//                i++;
//            }
//            else {
//                i = 0;
//                loopCounter++;
//            }
//        }
        
        //for(auto p : videoPlayers) {
        //        p->draw(ofMap(i++, 0, videoPlayers.size(), 0, ofGetWidth()), ofGetHeight()/2 - 108*2, 192*4, 108*4);
        
        //ofPushMatrix();
        //ofSetColor(ofRandom(255), 0, 0);
//        ofRect(0,0,ofGetWidth(),ofGetHeight());
//        ofEnableAlphaBlending();
//        ofSetColor(255,255,255);
//        
#if 0   // for 1080 x 3840 video
        //---------------------------------------------------------- draw video texture to fullscreen.
        ofRectangle screenRect(0, 0, ofGetWidth(), ofGetHeight());
        ofRectangle videoRect(0, 0, videoPlayers[i]->getWidth(), videoPlayers[i]->getHeight());
        ofRectangle videoFullscreenRect = videoRect;
        videoFullscreenRect.scaleTo(screenRect, OF_ASPECT_RATIO_KEEP_BY_EXPANDING);
        
        videoPlayers[i]->draw(0, 0, videoFullscreenRect.getWidth(), videoFullscreenRect.getHeight());
        
#endif
        
#if 1
        // for 2 1080 x 1920 videos
        //---------------------------------------------------------- draw video texture to fullscreen.
        
        for (int videoNum = 0; videoNum < videoPlayers.size(); videoNum++) {
            if (videoNum == 1) { //top
                ofRectangle screenRect(0, 0, ofGetWidth(), ofGetHeight()/2);
                ofRectangle videoRect(0, 0, videoPlayers[videoNum]->getWidth(), videoPlayers[videoNum]->getHeight());
                ofRectangle videoFullscreenRect = videoRect;
                videoFullscreenRect.scaleTo(screenRect, OF_ASPECT_RATIO_KEEP_BY_EXPANDING);
                videoPlayers[videoNum]->draw(0, 0, videoFullscreenRect.getWidth(), videoFullscreenRect.getHeight());
            }
            else if (videoNum == 0) { //bottom
                ofRectangle screenRect(0, 0, ofGetWidth(), ofGetHeight()/2);
                ofRectangle videoRect(0, 0, videoPlayers[videoNum]->getWidth(), videoPlayers[videoNum]->getHeight());
                ofRectangle videoFullscreenRect = videoRect;
                videoFullscreenRect.scaleTo(screenRect, OF_ASPECT_RATIO_KEEP_BY_EXPANDING);
                videoPlayers[videoNum]->draw(0, ofGetHeight()/2, videoFullscreenRect.getWidth(), videoFullscreenRect.getHeight());
            }
        }

        
        if (i < N_VIDEO_PLAYERS-1) {
            i++;
        }
        else {
            i = 0;
            //loopCounter++;
        }

        
#endif
        
        
        //videoPlayers[i]->draw(0, 0, 900, 1400);
        
        
        //p->draw(ofMap(i++, 0, videoPlayers.size(), 0, ofGetWidth()), ofGetHeight()/2 - 108*2, 192*4, 108*4);
        
        // 2304x4096 sumsung tv @1
        // 2304x8192 ofScreen
        // 2026x3840 video
        
        //        cout << "w:" << w << "\n";
        //        p->draw(0, 0);
        //ofPopMatrix();
        //}
    }
    
    if (imageDisplay) {
        
        ofRectangle screenRect(0, 0, ofGetWidth()/2, ofGetHeight()/2);
        ofRectangle videoRect(0, 0, imgTop->width, imgTop->height);
        ofRectangle videoFullscreenRect = videoRect;
        videoFullscreenRect.scaleTo(screenRect, OF_ASPECT_RATIO_KEEP_BY_EXPANDING);
        
        if (imgTopPosters.size() == 1) {
            ofSetColor(255, 255, 255);  // very important, don't delete set color
            imgTopPosters[0]->draw(0, 0, imgTopPosters[0]->width, imgTopPosters[0]->height);
        }

        
        if (dbgImg) {
            ofSetColor(0, 0, 255);
            imgTop->drawBounds(0, 0, imgTop->width, imgTop->height);
            imgBottom->drawBounds(0, 4096, imgBottom->width, imgBottom->height);
        }
        else {
            
            ofPushMatrix();
                ofEnableAlphaBlending();
                    ofSetColor(255, 255, 255);  // very important, don't delete set color
            
                    // ensure first image is showing
                    //imgTopPosters[0]->draw(0, 0, imgTopPosters[0]->width, imgTopPosters[0]->height);
            
                    if ((ofGetElapsedTimef() - initTime) > 2) {
                        //videoPause = !videoPause;
                        //imageDisplay = !imageDisplay;
                        initTime = ofGetElapsedTimef();
                        
                        if (imgTopx && !isUpdateImg) {
                            //ofColor(255, 0, 0, 100);
                            int size = imgTopPosters.size(); // size limitation is 2 by design
                            if (size > 0) {
                                imgTopPosters[imgRotateIndex]->draw(0, 0, imgTopPosters[imgRotateIndex]->width, imgTopPosters[imgRotateIndex]->height);
                                imgRotateIndex++;
                                if (imgRotateIndex >= size)
                                    imgRotateIndex = 0;
                                
                                //ofSleepMillis(3000);// well...
                            }
                            
                            //                        for (auto i = imgTopPosters.begin(); i!= imgTopPosters.end();  ++i) {
                            //                            //(*i)->draw(0, 0, imgTopx->width, imgTopx->height);
                            //                            (*i)->draw(0, 0, (*i)->width, (*i)->height);
                            //                        }
                            //imgTopx->draw(0, 0, imgTopx->width, imgTopx->height);
                        }
                        else{
                            imgTopPosters[0]->draw(0, 0, imgTopPosters[0]->width, imgTopPosters[0]->height);
                            //imgTop->draw(0, 0, imgTop->width, imgTop->height);
                        }
                    }
            
                    ofNoFill();
                    ofSetColor(100, 0, 100, 100);
                    ofCircle(imgTop->width/2, imgTop->height/3+100, 400);
                ofDisableAlphaBlending();
                
                //ofRectangle bbox;
                float fontSize = 300;
                //ofTranslate(100, 2* ofGetHeight()/3);
                //ofRotateY(50 * ofGetElapsedTimef());
                ofSetColor(100, 0, 100, 128);
                FZLfont.draw(strPoster, fontSize, imgTop->width/2-100+0.1*x, imgTop->height/3+100+0.1*y);
                //bbox = unicodeFont.getStringBoundingBox(strFruitPrefix, 100, 2* ofGetHeight()/3);
                //ofSetColor(0, 200, 0);
                //ofFill();
                //ofRotateZ(-5);
                ofEnableAlphaBlending();
            ofPopMatrix();
            
            // Bottom poster
            //ofColor(255, 255, 255);
            //ofTranslate(0, 4096); // samgung tv
            ofSetColor(255, 255, 255); // very important, don't delete set color
            ofTranslate(0, 7680/2); // pptv
            imgBottom->draw(0, 0, imgBottom->width, imgBottom->height);
        }
    }
    
    ofDrawBitmapStringHighlight("FPS: " + ofToString(fps), 20, 360);
    ofDrawBitmapStringHighlight("Frame " + ofToString(videoPlayers[i]->getCurrentFrame()) + "/" + ofToString(videoPlayers[i]->getTotalNumFrames()), 20, 380);
    ofDrawBitmapStringHighlight("Duration " + ofToString(videoPlayers[i]->getPosition() * videoPlayers[i]->getDuration(), 2) + "/" + ofToString(videoPlayers[0]->getDuration(), 2), 20, 400);
    ofDrawBitmapStringHighlight("Speed " + ofToString(videoPlayers[i]->getSpeed(), 2), 20, 420);
    ofDrawBitmapStringHighlight("Canvas W:" + ofToString(ofGetWidth()) + " H:" + ofToString(ofGetHeight()), 20, 440);

    ofDrawBitmapString("Total Loop #" + ofToString(loopCounter) + " \nClip #" + ofToString(i), 20, 460);
    
    // send out frame number information
    msgSend.setAddress("/sync/play/FW_SH_02_HBD_A/currentFrame");
    msgSend.addIntArg(videoPlayers[i]->getCurrentFrame());
    oscSender.sendMessage(msgSend);
    
    
    
#if 0
#if 0
    ofPushMatrix();
    ofRectangle bbox;
    ofSetColor(255, 0, 0, 32);
    float fontSize = 20 /*134*/;
    //TIME_SAMPLE_START("bbox");
    //ofTranslate(100, 2* ofGetHeight()/3);
    bbox = unicodeFont.getBBox(strFruitString, fontSize, 500, 500);
    //TIME_SAMPLE_STOP("bbox");
    ofRect(bbox);
    ofPopMatrix();
#endif

    ofPushMatrix();
        ofRectangle bbox;
        float fontSize = 134;
        //ofTranslate(100, 2* ofGetHeight()/3);
        //ofRotateY(50 * ofGetElapsedTimef());
        ofSetColor(0xd3, 0xd3, 0xd3, 200);
        unicodeFont.draw(strFruitString, fontSize, 100, 2* ofGetHeight()/3);
        bbox = unicodeFont.getStringBoundingBox(strFruitPrefix, 100, 2* ofGetHeight()/3);
        ofSetColor(0, 200, 0);
        //ofFill();
        ofEnableAlphaBlending();
        ofRect(bbox);
        //ofRotateZ(-5);
    ofPopMatrix();
    
    // text background
    ofSetColor(153, 153, 153, 100);
    ofRect(100, 2* ofGetHeight()/3 - 130, ofGetWidth()-100, 160);
    
    if (isDemoMode) {
        if ((ofGetElapsedTimef() - initTimeDbg) > 3.0) {
            videoPause = !videoPause;
            imageDisplay = !imageDisplay;
            initTimeDbg = ofGetElapsedTimef();
        }
    }
    
    if (isDownloadImg){
        isDownloadImg = !isDownloadImg;
       
        cout << "Downloading..." << "\n";
        ofSetColor(100, 0, 100, 128);
        
        if (isUpdateImg) {
            string str = "Poster Updating...";
            FZLfont.draw(str, 200, ofGetWidth()/2, ofGetHeight()/4*2);
        }
        
        // read file name from iOS client
        char serverPath[512] = "http://192.168.43.155:8080/";
        if (strUpdateFileDate.length() != 0) {
            sprintf(updateURL, "%s%s.jpg", serverPath, strUpdateFileDate.c_str());
            cout << "Update URL: " << updateURL << "\n";
            ofSaveURLAsync(updateURL, "images/L1.jpg");
        }
        else{
            cout << "ERROR: No update date" << "\n";
        }
    }
    
    if (isUpdateImg) {
        // reload image here
        if (imgTopx)
            delete imgTopx;
        
        imgTopx = new ofxGiantImage();
        imgTopx->loadImage("images/L1.jpg");
        imgTopPosters.push_back(imgTopx); // push into image queues
        isUpdateImg = !isUpdateImg;
    }
#endif
    
}

void ofApp::urlResponse(ofHttpResponse & response) {
    
    cout << "Got response!!" << "\n";
    isUpdateImg = true;

}

void ofApp::exit() {
    
    ofUnregisterURLNotification(this);
    delete imgTopx;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key) {
        case 'I':
            videoPause = !videoPause;
            imageDisplay = !imageDisplay;
            break;
        case 'D':
            isDemoMode = !isDemoMode;
            break;
        // reserved debug option 1-0
        case '1':
            dbgImg = !dbgImg;
            break;
        case 'p':
            isDownloadImg = !isDownloadImg;
            //isUpdateImg = !isUpdateImg;
            break;
    }
}

void ofApp::dumpOSC(ofxOscMessage m) {
    
    string msg_string;
    
    msg_string = m.getAddress();
    
    for (int i=0; i<m.getNumArgs(); i++ ) {
        msg_string += " ";
        if(m.getArgType(i) == OFXOSC_TYPE_INT32)
            msg_string += ofToString( m.getArgAsInt32(i));
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT)
            msg_string += ofToString( m.getArgAsFloat(i));
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING)
            msg_string += m.getArgAsString(i);
    }
    cout << msg_string << endl;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
//    currentFrameA = x;
//    currentFrameB = y;
//    
//    ofxOscMessage msgfromA;
//    ofxOscMessage msgfromB;
//    msgfromA.setAddress("/sync/A/currentFrame");
//    msgfromB.setAddress("/sync/B/currentFrame");
//    
//    msgfromA.addIntArg(currentFrameA);
//    msgfromB.addIntArg(currentFrameB);
//    
//    oscSender.sendMessage(msgfromA);
//    oscSender.sendMessage(msgfromB);

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


/***
 * PROJECT FARM WINDOW - MACHINE A
 *              ____                                    ,--,                 ,--.
 *            ,'  , `.   ,---,         ,----..        ,--.'|   ,---,       ,--.'|    ,---,.                         ,---,
 *         ,-+-,.' _ |  '  .' \       /   /   \    ,--,  | :,`--.' |   ,--,:  : |  ,'  .' |                        '  .' \
 *      ,-+-. ;   , || /  ;    '.    |   :     :,---.'|  : '|   :  :,`--.'`|  ' :,---.'   |                       /  ;    '.
 *     ,--.'|'   |  ;|:  :       \   .   |  ;. /|   | : _' |:   |  '|   :  :  | ||   |   .'                      :  :       \
 *    |   |  ,', |  '::  |   /\   \  .   ; /--` :   : |.'  ||   :  |:   |   \ | ::   :  |-,                      :  |   /\   \
 *    |   | /  | |  |||  :  ' ;.   : ;   | ;    |   ' '  ; :'   '  ;|   : '  '; |:   |  ;/|                      |  :  ' ;.   :
 *    '   | :  | :  |,|  |  ;/  \   \|   : |    '   |  .'. ||   |  |'   ' ;.    ;|   :   .'                      |  |  ;/  \   \
 *    ;   . |  ; |--' '  :  | \  \ ,'.   | '___ |   | :  | ''   :  ;|   | | \   ||   |  |-,                      '  :  | \  \ ,'
 *    |   : |  | ,    |  |  '  '--'  '   ; : .'|'   : |  : ;|   |  ''   : |  ; .''   :  ;/|                      |  |  '  '--'
 *    |   : '  |/     |  :  :        '   | '/  :|   | '  ,/ '   :  ||   | '`--'  |   |    \                      |  :  :
 *    ;   | |`-'      |  | ,'        |   :    / ;   : ;--'  ;   |.' '   : |      |   :   .'                      |  | ,'
 *    |   ;/          `--''           \   \ .'  |   ,/      '---'   ;   |.'      |   | ,'                        `--''
 *    '---'                            `---`    '---'               '---'        `----'
 *
 */



#include "ofApp.h"
//#include <memory>
#ifndef USE_REMOTE_CONTROL
#define USE_REMOTE_CONTROL
#endif

#ifndef USE_VIDEO_SYNC
#define USE_VIDEO_SYNC
#endif

float x;
int y;
ofColor color;

int w = 0;
int i = 0;
int loopCounter = 0;
static const int N_VIDEO_PLAYERS = 9;
string ASSET_VIDEO_FOLDER = "movies/"; // not used
string ASSET_IMAGE_FOLDER = "images/modelA";
string ASSET_HYBRID_IMAGE_FOLDER = "images/modelC/";

int frameJump;

#define ALL_DAY (-99)


void ofApp::InitRemoteControlUI() {

#ifdef USE_REMOTE_CONTROL
    ////////////////////////////////////////////////////////
    // Remote UI
    
    RUI_SETUP(); //start server
    
    // SETUP A CALLBACK ///////////////////////////////////////////
    //ofAddListener(RUI_GET_OF_EVENT(), this, &testApp::clientDidSomething);
    
    RUI_GET_INSTANCE()->setVerbose(true);
//    RUI_SHARE_PARAM(isDemoMode, ofColor(255,0,0,64));
    
//    // SET PARAM GROUPS / COLORS //////////////////////////////////
//    RUI_NEW_GROUP("Poster");	//make a new group (optional)
//    
//    // SHARE A STRING PARAM ////////////////////////////////
//    strPoster = " ";
//    RUI_SHARE_PARAM(strPoster, ofColor(255,0,0,64));	// you can also set a color on a per-param basis
    //Expose x and y vars to the server, providing a valid slider range
    //RUI_SHARE_PARAM(logoX, 0, ofGetWidth());

//
//    strUpdateFileDate = "";
//    RUI_SHARE_PARAM(strUpdateFileDate);
    
    //share the color param
    //RUI_SHARE_COLOR_PARAM(color);
    
    
    // SET PARAM GROUPS / COLORS //////////////////////////////////
    RUI_NEW_GROUP("Vegetable Percentage");	//make a new group (optional)
    
    strFruitPrefix = "";
    strUnit = "%";
    currentAppleAmount = 65;
    RUI_SHARE_PARAM(currentAppleAmount, 0, 100);	// you can also set a color on a per-param basis
    RUI_SHARE_PARAM(percentageX, 0, ofGetWidth());	// you can also set a color on a per-param basis
    
    
    // SHARE A BOOL PARAM ////////////////////////////////////////
    RUI_SHARE_PARAM(isShowPercentage);
    
    
    RUI_NEW_GROUP("Maintenance Option");	//make a new group (optional)
    RUI_SHARE_PARAM(logoY, 0, ofGetHeight());
    //RUI_SHARE_PARAM(oscIP);
    
    
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

}

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    // turn off ESC quit
    ofSetEscapeQuitsApp(false);

    ofSetVerticalSync(true);
    //ofEnableAntiAliasing();
    //ofSetFrameRate(60);
    
    // for single delivery package
    //ofSetDataPathRoot("./");
    
    
    slideshow.setup(ofToDataPath("images/modelB/slideshow/morning", true));
    slideshowAfternoon.setup(ofToDataPath("images/modelB/slideshow/afternoon", true));
    slideshowNight.setup(ofToDataPath("images/modelB/slideshow/night", true));

    PreloadAsset();
    
    // percentage value x coordination, x=1080px so doesn't matter if cross screen or not
    percentageX = imgTopPosters[0]->width/2 - 100;
    
    // enable trace to file
    ofLogToFile("FW_SH_02_HBD_A_LOG.txt", true);
    
    // initilization
    videoPause = false;
    imageDisplay = false;
    dbgImg = false;
    isDemoMode = false;
    isDebugMode = false;
    isUpdateImg = false;
    isDownloadImg = false;
    isShowCursor = false;
    isSlideShow = false;
    isHybridVideoLoaded = false;
    imgRotateIndex = 0;
    previousCellKickTime = -1;
    previousPeriod = -1;
    countOne, countTwo, countThree = 0;
    hybridPosterCount = 0;
    prevHybridSeq = -1;
    isShowPercentage = true;
    oscIP = "";
    
    // remote controller
    InitRemoteControlUI();

    // load font
    unicodeFont.setup("SourceHanSansSC-Light.ttf", //font file, ttf only
                      1.0,					//lineheight percent
                      1024,					//texture atlas dimension
                      true,					//create mipmaps of the font, useful to scale down the font at smaller sizes
                      8,					//texture atlas element padding, shouldbe >0 if using mipmaps otherwise
                      2.0f					//dpi scaleup, render textures @2x the reso
                      );					//lower res mipmaps wil bleed into each other
    
    
    FZLfont.setup("FZLTZCHJW.TTF", //font file, ttf only
                      1.0,					//lineheight percent
                      1024,					//texture atlas dimension
                      true,					//create mipmaps of the font, useful to scale down the font at smaller sizes
                      8,					//texture atlas element padding, shouldbe >0 if using mipmaps otherwise
                      2.0f					//dpi scaleup, render textures @2x the reso
                      );					//lower res mipmaps wil bleed into each other
    
    
    posterfont.setup("BrandonGrotesque-Regular.ttf", //font file, ttf only
                  1.0,					//lineheight percent
                  1024,					//texture atlas dimension
                  true,					//create mipmaps of the font, useful to scale down the font at smaller sizes
                  8,					//texture atlas element padding, shouldbe >0 if using mipmaps otherwise
                  2.0f					//dpi scaleup, render textures @2x the reso
                  );					//lower res mipmaps wil bleed into each other
    
    percentagefont.setup("BrandonGrotesque-Bold.ttf", //font file, ttf only
                     1.0,					//lineheight percent
                     1024,					//texture atlas dimension
                     true,					//create mipmaps of the font, useful to scale down the font at smaller sizes
                     8,					//texture atlas element padding, shouldbe >0 if using mipmaps otherwise
                     2.0f					//dpi scaleup, render textures @2x the reso
                     );					//lower res mipmaps wil bleed into each other
    
    
    
    strPosterLeft = (string)"SHANDONG, YANTAI";
    strPosterLeftCh = (string)"        山东烟台";
    
    strPosterRight = (string)"A HUNTER GATHERER FARM";
    strPosterRightCh = (string)"             悦衡食集农场";
    percentageBk.loadImage("poster_veg_bk.png");
    logoBk.loadImage("logo_small.png");

    
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
    
 
    // OSC
    // TODO: need more tests on this
//    oscIP = "\"" + oscIP + "\"";
//    if (oscIP.length() > 7) {
//        oscSender.setup(oscIP, SENDPORT);
//        cout << "oscIP:" << oscIP << "\r\n";
//    }
//    else
//        oscSender.setup(HOST, SENDPORT);

    oscSender.setup(HOST, SENDPORT);
    oscReceiver.setup(RECVPORT);
    
    // send ready
    ofxOscMessage m;
    m.setAddress("/sync/start/FW_SH_02_HBD_A");
    m.addStringArg("ready");
    cout << "+++ A: OSC SEND: " << ofGetTimestampString() << "\r\n";
    oscSender.sendMessage(m);
    cout << "--- A: OSC SEND: " << ofGetTimestampString() << "\r\n";
}


void ofApp::PreloadAsset() {
    
    ofDirectory dir;
    dir.open(ASSET_IMAGE_FOLDER);
    int numFiles = dir.listDir();
    
    for (int i = 0; i < numFiles; ++i) {
        cout << "Preload image:(" << i << "/" << numFiles << ") " << dir.getPath(i) << "\r\n";
        imgTop = new ofxGiantImage();
        imgTop->loadImage(dir.getPath(i));
        imgTopPosters.push_back(imgTop);
    }
    
    // 1080 x 1920 px posters
    dir.open(ASSET_HYBRID_IMAGE_FOLDER);
    numFiles = dir.listDir();
    
    for (int i = 0; i < numFiles; ++i) {
        cout << "load hybrid image:(" << i << "/" << numFiles << ") " << dir.getPath(i) << "\r\n";
        imgHybrid = new ofImage();
        imgHybrid->loadImage(dir.getPath(i));
        imgTopHybridPosters.push_back(imgHybrid);
    }
    
    if (timePeriod == 0 || timePeriod == 1 || timePeriod == 2) {
        videoPlayers.push_back(new ofxAVFVideoPlayer);
        videoPlayers[0]->loadMovie("movies/modelA/1.mov");
        videoPlayers[0]->setLoopState(OF_LOOP_NORMAL);
        
        videoPlayers.push_back(new ofxAVFVideoPlayer());
        videoPlayers[1]->loadMovie("movies/modelA/2.mov");
        videoPlayers[1]->setLoopState(OF_LOOP_NORMAL);
        
        videoPlayers.push_back(new ofxAVFVideoPlayer());
        videoPlayers[2]->loadMovie("movies/modelA/3.mov");
        videoPlayers[2]->setLoopState(OF_LOOP_NORMAL);
    }
}


void ofApp::LoadCurrentVideo(int timePeriod) {
    
    if ((timePeriod == previousPeriod) && (lastMode == currentMode))
        return;
    
// TOFIX: delete videoPlayers?
//    for (int i=0; i<videoPlayers.size(); i++) {
//        delete videoPlayers[i];
//    }

    //clearVideoPlayer();
    
    // TODO: should i keep timePeriod 1, 2 still?
    if (timePeriod == 0 || timePeriod == 1 || timePeriod == 2) {
        videoPlayers.push_back(new ofxAVFVideoPlayer());
        videoPlayers[0]->loadMovie("movies/modelA/morning/1.mov");
        videoPlayers[0]->setLoopState(OF_LOOP_NORMAL);
        
        videoPlayers.push_back(new ofxAVFVideoPlayer());
        videoPlayers[1]->loadMovie("movies/modelA/morning/2.mov");
        videoPlayers[1]->setLoopState(OF_LOOP_NORMAL);
        
        videoPlayers.push_back(new ofxAVFVideoPlayer());
        videoPlayers[2]->loadMovie("movies/modelA/morning/3.mov");
        videoPlayers[2]->setLoopState(OF_LOOP_NORMAL);
            
    }
    else if (timePeriod == ALL_DAY) {
        
        if (!isHybridVideoLoaded) {
            videoPlayers.push_back(new ofxAVFVideoPlayer());
            videoPlayers[0]->loadMovie("movies/modelC/1.mov");
            videoPlayers[0]->setLoopState(OF_LOOP_NORMAL);
            
            videoPlayers.push_back(new ofxAVFVideoPlayer());
            videoPlayers[1]->loadMovie("movies/modelC/2.mov");
            videoPlayers[1]->setLoopState(OF_LOOP_NORMAL);
            
            videoPlayers.push_back(new ofxAVFVideoPlayer());
            videoPlayers[2]->loadMovie("movies/modelC/3.mov");
            videoPlayers[2]->setLoopState(OF_LOOP_NORMAL);

            videoPlayers.push_back(new ofxAVFVideoPlayer());
            videoPlayers[3]->loadMovie("movies/modelC/4.mov");
            videoPlayers[3]->setLoopState(OF_LOOP_NORMAL);
            
            videoPlayers.push_back(new ofxAVFVideoPlayer());
            videoPlayers[4]->loadMovie("movies/modelC/5.mov");
            videoPlayers[4]->setLoopState(OF_LOOP_NORMAL);
            
            isHybridVideoLoaded = true;
        }
    }
}


float t = 0;

//--------------------------------------------------------------
void ofApp::update(){
    
    if (!videoPause) {
        int j = 0;
        
        if (true || videoPlayers[j]->isLoaded()) {

            for (j; j < videoPlayers.size(); j++) {
                videoPlayers[j]->update();
                videoPlayers[j]->play();
            }
        }
        initTime = ofGetElapsedTimef();
    }
    
    if (isSlideShow) {
        if (timePeriod == 0) {
            slideshow.update(slideshowSeq);
        }
        else if (timePeriod == 1) {
            slideshowAfternoon.update(slideshowSeq);
        }
        else if (timePeriod == 2) {
            slideshowNight.update(slideshowSeq);
        }

    }
    
    if (isHybrid) {
        
        for (auto p: videoPlayers) {
            if(true || p->isLoaded()) {
                p->update();
                p->setVolume(0.0);
            }
        }

        videoPlayers[hybridVideoNum]->play();

    }
        
    initTime = ofGetElapsedTimef();
    fps = ofGetFrameRate();
}

void ofApp::clearVideoPlayer() {
   
    for (vector<ofxAVFVideoPlayer*>::iterator it = videoPlayers.begin(); it != videoPlayers.end(); ++it) {
        delete *it;
    }
    
    videoPlayers.clear();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    int frameDiff;
    
    while (oscReceiver.hasWaitingMessages()) {
        //cout << "New msg is coming... \r\n";
        ofxOscMessage m;
        oscReceiver.getNextMessage(&m);
        
        // TOFIX: not use
        if (m.getAddress() == "/sync/play/FW_SH_02_HBD_A/frameJump") {
            frameJump = m.getArgAsInt32(0);
            cout << "Frame sync, jump(" << frameJump << ") frames\r\n";
            
            // do move forward
            //videoPlayers[i]->setFrame(frameJump);
        }
        else if (m.getAddress() == "/sync/start/nowPlayingInfo/poster") {
            imageDisplay = true;
            videoPause = true;
            isSlideShow = false;
            isHybridVideoLoaded = false;
            isHybrid = false;
            
            timePeriod = m.getArgAsInt32(0);
            posterSeq = m.getArgAsInt32(1);
            
            cout << "[POSTER SYNC INFO] " << ofGetTimestampString() << "time:" << timePeriod << ", seq#" << posterSeq << "\r\n";
            canIStart = true;
            isHybridVideoLoaded = false;
            //currentMode = ONE_SINGLE;
            
        }
        else if (m.getAddress() == "/sync/start/nowPlayingInfo/video") {
            imageDisplay = false;
            videoPause = false;
            isSlideShow = false;
            isHybridVideoLoaded = false;
            isHybrid = false;

            timePeriod = m.getArgAsInt32(0);
            videoSeq = m.getArgAsInt32(1);
            cellKickTime = m.getArgAsInt32(2);
            
           
            if (cellKickTime > previousCellKickTime)
                isCellStart = true;

            i = videoSeq + 0;
            
            // add canIstart here
            canIStart = true;
            currentMode = ONE_SINGLE;
            //preload video
            LoadCurrentVideo(timePeriod);
            previousPeriod = timePeriod;
            
            cout << "[VIDEO SYNC INFO]" << ofGetTimestampString() << " time:" << timePeriod << ", seq#" << videoSeq << ", kick:" << cellKickTime << "\r\n";
        }
        else if (m.getAddress() == "/sync/start/FW_SH_02_HBD_A/RUTHERE") {
            // send ready
            cout << "Yes, I'm here..." << "\r\n";
            ofxOscMessage m;
            m.setAddress("/sync/start/FW_SH_02_HBD_A");
            m.addStringArg("ready");
            //cout << "+++ A: OSC SEND: " << ofGetTimestampString() << "\r\n";
            oscSender.sendMessage(m);
            //cout << "--- A: OSC SEND: " << ofGetTimestampString() << "\r\n";
           
        }
        else if (m.getAddress() == "/sync/start/nowPlayingInfo/slideshow") {
            imageDisplay = false;
            videoPause = true;
            isSlideShow = true;
            isHybridVideoLoaded = false;
            isHybrid = false;
            
            timePeriod = m.getArgAsInt32(0);
            slideshowSeq = m.getArgAsInt32(1);
            
            cout << "[SLIDESHOW SYNC INFO] " << ofGetTimestampString() << "time:" << timePeriod << ", seq#" << slideshowSeq << "\r\n";
            
            //LoadCurrentSlideshows(timePeriod);
            previousPeriod = timePeriod;
            currentMode = TWO_SLIDESHOW;
            
        }
        else if (m.getAddress() == "/sync/start/nowPlayingInfo/hybrid") {
            imageDisplay = false;
            videoPause = true;
            isSlideShow = false;
            isHybrid = true;
            
            timePeriod = m.getArgAsInt32(0);
            hybridshowSeq = m.getArgAsInt32(1);
            cellKickTime = m.getArgAsInt32(2);
            
            if (cellKickTime > previousCellKickTime)
                isCellStart = true;
            
            cout << "[HYBRID SYNC INFO] " << ofGetTimestampString() << "time:" << timePeriod << ", seq#" << hybridshowSeq << "\r\n";
            hybridVideoNum = hybridshowSeq;
            
            if (hybridshowSeq == prevHybridSeq && hybridPosterCount <4) // 5 posters in total
                hybridPosterCount++;
            else {
                hybridPosterCount = 0;
                videoPlayers[hybridVideoNum]->setPosition(0.0);
            }
            
            canIStart = true;
            currentMode = THREE_HYBRID;
           
            LoadCurrentVideo(ALL_DAY);
            previousPeriod = timePeriod; //TODO: this is potential issue
        }
        //dumpOSC(m);
    }
 
    strFruitString =  ofToString(currentAppleAmount) + strUnit;
    
    if (!canIStart)
        return;
    
    if (!videoPause) {
        // update kicktime
        // 0 -> 60 -> 90 -> 0 ->
        if (isCellStart) {
            
            // start time: 0
            if (cellKickTime == 0) {
                videoPlayers[i]->setPaused(true);
                cout << "set position: " << cellKickTime/videoPlayers[i]->getDuration() << "\r\n";
                videoPlayers[i]->setPosition(cellKickTime/videoPlayers[i]->getDuration());
                videoPlayers[i]->setPaused(false);
                previousCellKickTime = -1;
                cellKickTime = -1;
            }
            else if (cellKickTime > previousCellKickTime) {
                //move forward video
                // int duration = videoPlayers[i]->getDuration();
                videoPlayers[i]->setPaused(true);
                cout << "set position: " << cellKickTime/videoPlayers[i]->getDuration() << "\r\n";
                videoPlayers[i]->setPosition(cellKickTime/videoPlayers[i]->getDuration());
                videoPlayers[i]->setPaused(false);
                previousCellKickTime = cellKickTime;
                // when to set previousCellKickTime to -1?
            }
        }
        
#if 1   // for 1080 x 3840 video
            //---------------------------------------------------------- draw video texture to fullscreen.
            ofRectangle screenRect(0, 0, ofGetWidth(), ofGetHeight());
            ofRectangle videoRect(0, 0, videoPlayers[i]->getWidth(), videoPlayers[i]->getHeight());
            ofRectangle videoFullscreenRect = videoRect;
            videoFullscreenRect.scaleTo(screenRect, OF_ASPECT_RATIO_KEEP_BY_EXPANDING);
            videoPlayers[i]->draw(0, 0, videoFullscreenRect.getWidth(), videoFullscreenRect.getHeight());
#endif
        
        // Static data for vegetable percentage
        ofPushMatrix();
        ofEnableAlphaBlending();
        ofEnableAntiAliasing();
        ofEnableSmoothing();
        
        ofTranslate(0, -200);
        ofPoint locationBK;
        locationBK.set(imgTopPosters[0]->width/2 -140, imgTopPosters[0]->height/2-220);
        if (isShowPercentage)
            percentageBk.draw(locationBK, percentageBk.width*0.7, percentageBk.height*0.7);
        
        ofPoint locationLogo;
        locationLogo.set(0,logoY);
        logoBk.draw(locationLogo, 1080, 437); // change to 1080
        ofRectangle bbox;
        ofSetColor(255, 255, 255, 255);
        int fontSize = 200;
        //percentageX = imgTopPosters[0]->width/2 - 100;
        if (isShowPercentage)
            percentagefont.draw(strFruitString, fontSize, percentageX, imgTopPosters[0]->height/2-50);
        
        percentagefont.draw(strPosterLeft, 30, 100, imgTopPosters[0]->height/2-50);
        FZLfont.drawMultiLine(strPosterLeftCh, 28, 100, imgTopPosters[0]->height/2-18);
        
        percentagefont.drawMultiLine(strPosterRight, 30, imgTopPosters[0]->width/2 + 220, imgTopPosters[0]->height/2 -50);
        FZLfont.drawMultiLine(strPosterRightCh, 24, imgTopPosters[0]->width/2 + 220+15, imgTopPosters[0]->height/2 -18);
        
        ofDisableSmoothing();
        ofDisableAlphaBlending();
        ofDisableAntiAliasing();
        ofPopMatrix();
        lastMode = ONE_SINGLE;
    }
    else if (imageDisplay) {
       
        ofRectangle screenRect(0, 0, ofGetWidth(), ofGetHeight());
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
            
                    imgTopPosters[posterSeq]->draw(0, 0, imgTopPosters[posterSeq]->width, imgTopPosters[posterSeq]->height);

                float fontSize = 300;
                FZLfont.draw(strPoster, fontSize, imgTop->width/2-100+0.1*x, imgTop->height/3+100+0.1*y);
                ofEnableAlphaBlending();
            ofPopMatrix();
            
        }
        lastMode = ONE_SINGLE;
    }
    else if (isSlideShow) {
        if (timePeriod == 0)
            slideshow.draw();
        else if (timePeriod == 1)
            slideshowAfternoon.draw();
        else if (timePeriod == 2)
            slideshowNight.draw();
        
        // Static data for vegetable percentage
        ofPushMatrix();
        ofEnableAlphaBlending();
        ofEnableAntiAliasing();
        ofEnableSmoothing();
        
        ofTranslate(0, -200);
        ofPoint locationBK;
        locationBK.set(imgTopPosters[0]->width/2 -140, imgTopPosters[0]->height/2-220);
        if (isShowPercentage)
            percentageBk.draw(locationBK, percentageBk.width*0.7, percentageBk.height*0.7);
        ofPoint locationLogo;
        locationLogo.set(0,logoY);
        logoBk.draw(locationLogo, 1080, 437);
        ofRectangle bbox;
        ofSetColor(255, 255, 255, 255);
        
        int fontSize = 200;
        //percentageX = imgTopHybridPosters[0]->width/2 - 100;
        if (isShowPercentage)
            percentagefont.draw(strFruitString, fontSize, percentageX, imgTopPosters[0]->height/2-50);
        
        percentagefont.draw(strPosterLeft, 30, 100, imgTopPosters[0]->height/2-50);
        FZLfont.drawMultiLine(strPosterLeftCh, 28, 100, imgTopPosters[0]->height/2-18);
        
        percentagefont.drawMultiLine(strPosterRight, 30, imgTopPosters[0]->width/2 + 220, imgTopPosters[0]->height/2 -50);
        FZLfont.drawMultiLine(strPosterRightCh, 24, imgTopPosters[0]->width/2 + 220+15, imgTopPosters[0]->height/2 -18);
        
        ofDisableSmoothing();
        ofDisableAlphaBlending();
        ofDisableAntiAliasing();
        ofPopMatrix();
        lastMode = TWO_SLIDESHOW;
    }
    else if (isHybrid) {
        // draw video
        ofRectangle screenRect(0, 0, ofGetWidth(), ofGetHeight()/2);
        ofRectangle videoRect(0, 0, videoPlayers[hybridVideoNum]->getWidth(), videoPlayers[hybridVideoNum]->getHeight());
        ofRectangle videoFullscreenRect = videoRect;
        videoFullscreenRect.scaleTo(screenRect, OF_ASPECT_RATIO_KEEP_BY_EXPANDING);
        videoPlayers[hybridVideoNum]->draw(0, 0, videoFullscreenRect.getWidth(), videoFullscreenRect.getHeight());
        //cout << "hybrid: video num: " << hybridVideoNum;
    
        
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
            
            imgTopHybridPosters[hybridPosterCount]->draw(0,  imgTopHybridPosters[0]->height, imgTopHybridPosters[hybridPosterCount]->width, imgTopHybridPosters[hybridPosterCount]->height);
            
            float fontSize = 300;
            FZLfont.draw(strPoster, fontSize, imgHybrid->width/2-100+0.1*x, imgHybrid->height-100+0.1*y);
            ofEnableAlphaBlending();
            ofPopMatrix();
            
        }
        
        prevHybridSeq = hybridshowSeq;
        
        //////////////////////////////////////////////////////////////////////////
        // Static data for vegetable percentage
        ofPushMatrix();
        ofEnableAlphaBlending();
        ofEnableAntiAliasing();
        ofEnableSmoothing();
        
        ofTranslate(0, -200);
        ofPoint locationBK;
        locationBK.set(imgTopHybridPosters[0]->width/2 -140, imgTopHybridPosters[0]->height-220);
        if (isShowPercentage)
            percentageBk.draw(locationBK, percentageBk.width*0.7, percentageBk.height*0.7);
        ofPoint locationLogo;
        locationLogo.set(0,logoY);
        logoBk.draw(locationLogo, 1080, 437);
        ofRectangle bbox;
        ofSetColor(255, 255, 255, 255);
        int fontSize = 200;
        //percentageX = imgTopHybridPosters[0]->width/2 - 100;
        if (isShowPercentage)
            percentagefont.draw(strFruitString, fontSize, percentageX, imgTopHybridPosters[0]->height-50);
        
        percentagefont.draw(strPosterLeft, 30, 100, imgTopHybridPosters[0]->height-50);
        FZLfont.drawMultiLine(strPosterLeftCh, 28, 100, imgTopHybridPosters[0]->height-18);
        
        percentagefont.drawMultiLine(strPosterRight, 30, imgTopHybridPosters[0]->width/2 + 220, imgTopHybridPosters[0]->height -50);
        FZLfont.drawMultiLine(strPosterRightCh, 24, imgTopHybridPosters[0]->width/2 + 220+15, imgTopHybridPosters[0]->height -18);

        
        ofDisableSmoothing();
        ofDisableAlphaBlending();
        ofDisableAntiAliasing();
        ofPopMatrix();
        
        lastMode = THREE_HYBRID;
    }

    if (isDebugMode) {
        
        if (isHybrid)
            i = hybridVideoNum;
        ofDrawBitmapStringHighlight("FPS: " + ofToString(fps), 20, 360);
        ofDrawBitmapStringHighlight("Frame " + ofToString(videoPlayers[i]->getCurrentFrame()) + "/" + ofToString(videoPlayers[i]->getTotalNumFrames()), 20, 400);
        ofDrawBitmapStringHighlight("Duration " + ofToString(videoPlayers[i]->getPosition() * videoPlayers[i]->getDuration(), 2) + "/" + ofToString(videoPlayers[0]->getDuration(), 2), 20, 440);
        ofDrawBitmapStringHighlight("Speed " + ofToString(videoPlayers[i]->getSpeed(), 2), 20, 480);
        ofDrawBitmapStringHighlight("Canvas W:" + ofToString(ofGetWidth()) + " H:" + ofToString(ofGetHeight()), 20, 520);
        ofDrawBitmapStringHighlight("Clip #" + ofToString(i), 20, 560);
    }
    
    

#if 0
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
    
    if (isShowCursor)
        ofShowCursor();
    else
        ofHideCursor();
    
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
    
    int moveFrame = 0;
    
    switch(key) {
        case 'z':
            isShowCursor = !isShowCursor;
            break;
        case 'd': // debug mode
            isDebugMode = !isDebugMode;
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


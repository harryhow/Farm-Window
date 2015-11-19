#pragma once

#include "ofMain.h"
#include "ofxAVFVideoPlayer.h"
#include "ofxRemoteUIServer.h"
#include "ofxFontStash.h"
#include "ofxGiantImage.h"
#include "ofURLFileLoader.h"
#include "ofxOsc.h"

#define     HOST "192.168.0.255" // broadcast ip
#define     SENDPORT 6002
#define     RECVPORT 6002


class ofApp : public ofBaseApp{
    
    enum MenuItems{
        MENU_OPTION_0, MENU_OPTION_1, MENU_OPTION_2, MENU_OPTION_3
    };
    
    
   	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void loadVideo(string filename);
    
        std::vector<ofxAVFVideoPlayer *> videoPlayers;
    
        int fps;
        // remote UI
        string currentAppleAmount;
        string unloadTest;
        MenuItems menu;
        ofxGiantImage *imgTopx;
    
        // remote command
        string strUpdateFileDate;
        char updateFileDate[64];
        //char serverPath;
        char updateURL[1024];
    
        // font
        ofxFontStash unicodeFont;
        ofxFontStash FZLfont;
    
        // text display
        string strFruitPrefix;
        string strUnit;
        string strFruitString;
        string strPoster;
    
//        ofImage *imgTop;
//        ofImage *imgBottom;
    
        ofxGiantImage *imgTop;
        ofxGiantImage *imgBottom;
        vector<ofxGiantImage*> imgTopPosters;
        int imgRotateIndex;
    
        // debug optipn
        bool dbgImg;
        bool videoPause;
        bool imageDisplay;
        bool isDemoMode;
        bool isUpdateImg;
        bool isDownloadImg;
        float initTime;
        float initTimeDbg;
    
        // osc values
        int    isCellStart;
        int    isCellStop;
        string mediaType;
        int    cellKickTime;
    
        // member function
        void urlResponse(ofHttpResponse & response);
        void exit();
    
        void dumpOSC(ofxOscMessage m);
        
        ofxOscSender oscSender;
        ofxOscReceiver oscReceiver;
        
        ofxOscMessage msgSend;
        ofxOscMessage msgRecv;
};

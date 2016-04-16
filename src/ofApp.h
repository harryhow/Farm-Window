#pragma once

#include "ofMain.h"
#include "ofxAVFVideoPlayer.h"
#include "ofxRemoteUIServer.h"
#include "ofxFontStash.h"
#include "ofxGiantImage.h"
#include "ofURLFileLoader.h"
#include "ofxOsc.h"
#include "SlideShow.h"

//#define     HOST "10.1.3.255" // HG HBD's ip
//#define       HOST "10.150.2.255" // HG HBD's LAN IP
//#define     HOST "192.168.78.255" // BXB's broadcast ip
#define     HOST "10.29.3.255" // BXB's broadcast ip
//#define     HOST "192.168.0.255"  // NY 251
//#define     HOST "172.16.0.255"     // Houson Valley
//#define     HOST "192.168.1.255" // queesn studio
#define     SENDPORT 6002
#define     RECVPORT 6002


class ofApp : public ofBaseApp{
    
    enum MenuItems{
        MENU_OPTION_0, MENU_OPTION_1, MENU_OPTION_2, MENU_OPTION_3
    };
    
    enum Mode {
        ONE_SINGLE=0,   // cross screen single video + poster
        TWO_SLIDESHOW,   // slideshow + poster
        THREE_HYBRID  // single video + poster
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
        void loadPoster(string filename);
        void InitRemoteControlUI();
        void PreloadAsset();
        void LoadCurrentVideo(int timePeriod);
        void LoadCurrentSlideshows(int timePeriod);
        void clearVideoPlayer();
    
        std::vector<ofxAVFVideoPlayer *> videoPlayers;
        //std::vector<std::unique_ptr<ofxAVFVideoPlayer>> videoPlayers;
    
    
        int prevTimePeriod; 
    
        int fps;
        // remote UI
        int currentAppleAmount;
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
        ofxFontStash posterfont;
        ofxFontStash percentagefont;
    
        // text display
        string strFruitPrefix;
        string strUnit;
        string strFruitString;
        string strPoster;
        string strPosterLeft;
        string strPosterLeftCh;
        string strPosterRight;
        string strPosterRightCh;
        ofImage percentageBk;
        ofImage logoBk;
    
//        ofImage *imgTop;
//        ofImage *imgBottom;
    
        ofxGiantImage *imgTop;
        ofxGiantImage *imgBottom;
        vector<ofxGiantImage*> imgTopPosters;
        vector<ofImage*> imgTopHybridPosters;
        ofImage* imgHybrid;
        int imgRotateIndex;
    
        // debug optipn
        bool dbgImg;
        bool videoPause;
        bool imageDisplay;
        bool isDemoMode;
        bool isDebugMode;
        bool isUpdateImg;
        bool isDownloadImg;
        float initTime;
        float initTimeDbg;
        bool isShowCursor;
        bool canIStart;
    
    
        // osc values
        int    isCellStart;     // start signal
        int    isCellStop;      // stop signal
        string mediaType;       // photo or video
        //int    mediaType;
        string nowPlayingFile;  // now playing file name
        int    cellKickTime;
        int previousCellKickTime;
        string startFlag;
        int timePeriod;
        int previousPeriod;
        int videoSeq;
        int posterSeq;
        int slideshowSeq;
        int hybridshowSeq;
        int countOne, countTwo, countThree;
        int logoX, logoY, percentageX;
        bool isShowPercentage;
        string oscIP;
    
    
        // member function
        void urlResponse(ofHttpResponse & response);
        void exit();
    
        void dumpOSC(ofxOscMessage m);
        
        ofxOscSender oscSender;
        ofxOscReceiver oscReceiver;
        
        ofxOscMessage msgSend;
        ofxOscMessage msgRecv;
    
        SlideShow slideshow;
        SlideShow slideshowAfternoon;
        SlideShow slideshowNight;
    
        bool isSlideShow;
        bool isHybrid;
        bool isHybridVideoLoaded;
        int  hybridPosterCount;
        int  prevHybridSeq;
        int  hybridVideoNum;
        Mode lastMode;
        Mode currentMode;
};

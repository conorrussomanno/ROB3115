#include "EEG.h"
#include "Story.h"
#include "Minigame.h"
#include "LoadThread.h"
#include "ofxThinkGear1.h"
#include "ofxBlur.h"
#include <fstream>


const bool EXITROB = false;

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofTrueTypeFont font1;
    EEG eeg; //EEG device communicator
    int mode; //-1 = opening sequence; 0 = Intro Screen (sequence); 1 = Connecting to Device; 2 = minigame; 3 = Story; 4 = Close Sequence
    
    //-10 = start, -9 = x start screen, -8 = x go
    
    char * fileName;
    
    ofxThinkGear1 thinkgearX;
    bool hasLoadedBigStuff;
    
    bool connectText;
    bool storySetUp;
    int deviceNumber;
    
    float timeOfLastMouseRelease;
    bool cursorHidden;
    
    ofImage intro;
    ofImage neuroSkyDevices;
    ofImage description;
    ofImage tutorial;
    
    ofImage appPicker;
    
    ofstream myFile;
    
    float timeOfNegativeOne;
    
    float timeOfZero;
    Story story;
    
    
//    LoadThread loadScreen;
    
    Minigame minigame;
    float timeOfFadeIn;
    
    float chapterAttValue;
    float currentAttValue;
    float currentSignalQuality;
    
    int number; //test
    int blink;
    
    //-------X items---------//
    ofVideoPlayer welcomescreen;
    ofVideoPlayer gameplay;
    ofVideoPlayer gameover;
    
    vector<ofFbo*> fbos;
    
    ofxBlur blur;
    ofImage transparency;
    
    ofxThinkGear thinkGear;
    void attentionListener(float &param);
    
    float atChangeTime;
    float meChangeTime;
    float distAw;
    float prevAw;
    float currAw;
    float distMw;
    float prevMw;
    float currMw;
    
    ofTrueTypeFont font;
    
    float attention;
    
    float currBlur;
    
    bool welcome;
    bool incident;
    bool over;
    bool danger;
    bool extreme;
    bool firstPlaySeq;
    bool lastPlaySeq;
    
    int counter;
    int threshold;
    int openThreshold;
    
    float startTime;
    float currentTime;
    float totalTime;
    bool flip;
    
    ofImage introX;
    
    bool xLoaded; //boolean for loaded videos in X's setup
    
    
    
    //------------------------//
    
    
};

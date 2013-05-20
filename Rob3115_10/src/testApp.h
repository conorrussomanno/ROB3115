#include "EEG.h"
#include "Story.h"
#include "Minigame.h"
#include "LoadThread.h"

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
    
    bool connectText;
    bool storySetUp;
    int deviceNumber;
    
    ofImage intro;
    ofImage neuroSkyDevices;
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
    
    
};
#include "EEG.h"
#include "Story.h"
#include "Minigame.h"

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
    int mode; //0 = Intro Screen (sequence); 1 = Connecting to Device; 2 = minigame; 3 = Story; 4 = Close Sequence
    
    bool connectText;
    int deviceNumber;
    
    ofImage intro;
    Story story;
    
    Minigame minigame;
    
    float chapterAttValue;
    
    int number; //test
    int blink;
    
    
};


#include "ofMain.h"
#include "ofxTextBlock.h"

class Minigame : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    vector<ofxTextBlock> quotes;
    ofImage bg;
    
    bool isMeterFull; // false until minigame is won
    
    float meterCount;
    float meterCapacity;
    float meterFlux;
    
    int randomQuote;
    
    ofTrueTypeFont font;
    
    
    
};

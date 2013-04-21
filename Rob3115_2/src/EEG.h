//
//  EEG.h
//  neuroStory
//
//  Created by Conor Russomanno on 3/12/13.
//
//

#include "ofMain.h"
#include "ofxThinkGear.h"
#include "ofxTweenLite.h"

class EEG : public ofBaseApp{
    
public:
    bool setup(int deviceType);
    void update();
    void draw();
    
    ofxThinkGear thinkGear;
    float getChapterAttention();
    void attentionListener(float &param);
    void drawAttentionGraph();
    
    
    float signalQuality;
    
    float atChangeTime; //
    float attention;  //
    float distAw;    //
    float currAw; //
    float prevAw;
    vector <int> attValues; //whole story
    vector <int> chapValues; //resets when chapter switches
    
    ofTrueTypeFont font;
    
    float distFromLeftEdge;
    float distFromTopEdge;
    
    bool graphOn;
    int mode;
    
    bool newAttentionValueReady;
    
};
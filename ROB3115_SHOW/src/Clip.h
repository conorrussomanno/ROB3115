//
//  Clip.h
//  Rob3115
//
//  Created by Conor Russomanno on 5/7/13.
//
//

#include "ofMain.h"
#include "ofxTextBlock.h"

class Clip : public ofBaseApp{
    
public:
    void setup(string _text, bool _requiresClick, float _waitTime, int _speaker);
    void setup(string _text, bool _requiresClick, float _waitTime, int _speaker, int _animationClip);
    void update();
    void draw();
    
    void alphaBlink();
    
    bool requiresClick;
    float waitTime;
    float tripTime;
    bool textFinished;
    
    //for animation clips
    bool isDebugClip;
    bool isAlertClip;
    bool isBugFoundClip;
    bool isAlphaMoveClip;
    
    
    string text;
    ofxTextBlock textBlock;
    
    float timeOfLastWord;
    float timeTilNextWord;
    int wordNumber;
    
    ofImage eyes;
    
    ofColor textColor;
    
    int speaker;  //0=CENTRAL; 1=ALPHA; 2=ROB
    
    
};
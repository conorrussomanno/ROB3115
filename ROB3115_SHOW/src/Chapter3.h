//
//  Chapter.h
//  neuroStory
//
//  Created by Conor Russomanno on 3/20/13.
//
/*
    -**- Chapter3 Class & Clip Class -**-
 
    - This is an automated text animation system
    - each clip has a predetermined wait time that indicates how long to wait after the preceeding clip finishes.
    - The chapter starts at clip 0 and chonologically progresses through the sequence
    - it is similar in nature to the page class but includes time-based features
    - certain clips require a mouseRelease to be activated
    - clips are also assigned (or not) animation booleans to trigger animations in chapter 3 class
 */

#include "ofMain.h"
#include "Clip.h"
#include "HUD.h"


class Chapter3: public ofBaseApp{
    
public:
    void setup(int _tier);
    void update(float _currentAttValue, float _currentSignalQuality);
    void draw();
    
    void populateClips(int _tier);
    void mouseReleased();
    void debugAnimation();
    void alertAnimation();
    void alphaWalkingAnimation(float _startTime);
    void deathAnimation();
    void backToWorkAnimation();
    
    //-----Variables------//
    
    int tier; //H/M/L
    
    float alphaAnimateFactor;
    float alphaAnimateStartTime;
    
    
    vector<Clip> clips;
    int currentClip;
    
    ofImage chapter3_bg;
    ofImage alpha;
    ofImage grayFlash;
    ofImage redFlash;
    ofImage blueFlash;
    ofImage overlay;
    
    bool exitRob;
    
    float endTime;
    bool isFinished;
    
    bool wasMouseReleased;
    
    
    
    
    
    
};
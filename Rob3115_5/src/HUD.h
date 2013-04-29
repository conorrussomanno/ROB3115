#include "ofMain.h"
#include "HUDSpinner.h"

class HUD : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw(int _blink);
    
    void activateSingle();
    void activateDouble();
    
    HUDSpinner spinner1;
    HUDSpinner spinner2;
    HUDSpinner spinner3;
    HUDSpinner spinner4;
    HUDSpinner spinner5;
    
    HUDSpinner spinner6;
    ofImage HUDimg;
    
    bool singleBlink;
    bool doubleBlink;
    
    float singleTriggerTime;
    float doubleTriggerTime;
    
};
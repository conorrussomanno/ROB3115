#include "ofMain.h"
#include "HUDSpinner.h"
#include "HUDStepGraph.h"

class HUD : public ofBaseApp{
    
public:
    void setup();
    void update(float _currentAttValue, float _currentSignalQuality);
    void draw(int _blink);
    
    void activateSingle();
    void activateDouble();
    
    HUDSpinner spinner1;
    HUDSpinner spinner2;
    HUDSpinner spinner3;
    HUDSpinner spinner4;
    HUDSpinner spinner5;
    
    //Upper Left Spinner
    HUDSpinner spinner6;
    
    //Lower Right Spinner
    vector <HUDUnit> unit1_1;
    vector <HUDUnit> unit1_2;
    
    //Middle Left Spinner (w/ lens)
    vector <HUDUnit> unit2_1;
    vector <HUDUnit> unit2_2;
    
    HUDStepGraph stepGraph1;
    
    ofImage HUDimg;
    
    bool singleBlink;
    bool doubleBlink;
    
    float singleTriggerTime;
    float doubleTriggerTime;
    
};
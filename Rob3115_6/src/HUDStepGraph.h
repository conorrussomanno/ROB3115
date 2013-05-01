
#include "ofMain.h"

class HUDStepGraph : public ofBaseApp{
public:
    
    void setup(float _maxBlocks, float _graphWidth, float _graphHeight, float _distBetweenBlocks, ofColor _blockColor, float _xLocation, float _yLocation);
    void update(float _currentAttValue, float _currentSignalQuality);
    void draw();
    
    //variables passed in setup
    float maxBlocks;
    float graphWidth;
    float graphHeight;
    float distBetweenBlocks;
    ofColor blockColor;
    
    //calculated from passed variables
    float xLocation, yLocation;
    float blockHeight;
    float blockWidth;
    float currentBlockCount;
    
};
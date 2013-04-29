//
//  Page.h
//  neuroStory
//
//  Created by Conor Russomanno on 3/20/13.
//
//

#include "ofMain.h"
#include "ofxTextBlock.h"

class Page : public ofBaseApp{
    
public:
    void setup(string _text, ofImage _img, int textboxValuesPlaceholder);
    void update();
    void draw();
    
    string text;
    ofxTextBlock textBlock;
    ofImage img;
    
    float timeOfLastWord;
    float timeTilNextWord;
    int wordNumber;
    
    bool textDone;
    
};
//
//  Page.cpp
//  neuroStory
//
//  Created by Conor Russomanno on 3/20/13.
//
//

#include "Page.h"

void Page::setup(string _text, ofImage _img, int textboxValuesPlaceholder){
    //setup textbox with values passed through setup
    text = _text;
    img = _img;
    
    textBlock.init("font/wwDigital.ttf", 20);
    textBlock.setText(text);
    textBlock.wrapTextX((0.8)*ofGetWindowWidth());
    
    wordNumber = 0;
    timeOfLastWord = ofGetElapsedTimeMillis();
    timeTilNextWord = 40 + ofRandom(-30,30);
    
    textDone = false;
    
}

//--------------------------------------------------------------
void Page::update(){
    
    if(ofGetElapsedTimeMillis()-timeTilNextWord >= timeOfLastWord){
        wordNumber++;
        timeOfLastWord = ofGetElapsedTimeMillis();
        timeTilNextWord = 40; + ofRandom(-30,30);
    }
    
    if (wordNumber == textBlock.words.size()){
        textDone = true;
    }
    
}

//--------------------------------------------------------------
void Page::draw(){
    
    img.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    textBlock.drawLeftAndType((0.140)*ofGetWindowWidth(), (0.840) * ofGetWindowHeight(), wordNumber);
    
    //draw textbox
    
}
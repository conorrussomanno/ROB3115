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
}

//--------------------------------------------------------------
void Page::update(){
    
}

//--------------------------------------------------------------
void Page::draw(){
    img.draw(0,0,ofGetScreenWidth(), ofGetScreenHeight());
    
    //draw textbox
    
}
//
//  EEG.cpp
//  neuroStory
//
//  Created by Conor Russomanno on 3/12/13.
//
//

#include "EEG.h"


bool EEG::setup(int deviceType){
    bool connection;
    if(deviceType == 1){
        connection = thinkGear.setup("/dev/tty.MindWaveMobile-DevA-1");
    }
    if(deviceType == 2){
        connection = thinkGear.setup("/dev/tty.MindSet-DevB");
    }
    if(deviceType == 3){
        connection = thinkGear.setup("/dev/tty.BrainBand-DevB");
    }
    
    ofAddListener(thinkGear.attentionChangeEvent, this, &EEG::attentionListener);
    
    font.loadFont("font/venus_rising.ttf", 12);
    distAw = 0.0;
    prevAw = 0.0;
    currAw = 0.0;
    
    distFromLeftEdge = (50.0/1680.0)*ofGetWidth();
    distFromTopEdge = (50.0/1680.0)*ofGetWidth();
    graphOn = false;
    
    return connection;
    
}

//--------------------------------------------------------------
int EEG::updateNew(){
    
    returnBlinkInt = thinkGear.update();
    
    signalQuality = ofMap(thinkGear.getSignalQuality(),200,0,0,100);
    //Update for AttGraph (using Tween)
    float cur = ofGetElapsedTimef();
    float progress = cur - atChangeTime;
//    cout << "prevAw2" << prevAw << endl;
    currAw = ofxTweenLite::tween(prevAw, distAw, progress, OF_EASE_SINE_INOUT);
    
    if(returnBlinkInt != 0){
        cout << "Return Int 2: " << returnBlinkInt << endl;
    }
    
    return returnBlinkInt;
    
}

//--------------------------------------------------------------
void EEG::draw(){
//    cout << "Attention: " << attention << endl;
//    cout << "Signal Quality: " << signalQuality << endl;
    
    if(graphOn){
        drawAttentionGraph();
    }
}

void EEG::attentionListener(float &param)
{
    prevAw = distAw;
    attention = param;
    attValues.push_back(attention);
    chapValues.push_back(attention);
    distAw = ofMap(attention, 0.0, 100.0, 0, ofGetWidth() - (2*distFromLeftEdge));
    atChangeTime = ofGetElapsedTimef();
}

float EEG::getChapterAttention(){
    float chapAttTotal = 0;
    for(int i = 0; i < chapValues.size(); i++){
        chapAttTotal += chapValues[i];
    }
    
    if(chapValues.size()>0){
        return (float)chapAttTotal/chapValues.size();
    }
    else{
        return 0.0;
    }
}

void EEG::drawAttentionGraph()
{
    
    ofPushMatrix();
    ofTranslate(0, distFromTopEdge);
    
    //Draw bar-graph
    ofPushStyle();
    ofSetColor(104, 208, 190, ofMap(currAw, 0.0, ofGetWidth() - (2*distFromLeftEdge), distFromLeftEdge, 255)); //color of bar-graph bar
    ofFill();
    ofRect(distFromLeftEdge, ofGetHeight()/4+1, currAw, ((distFromLeftEdge-1)/1680.0)*ofGetWidth());
    
    ofSetColor(ofColor::white);
    font.drawString("Attention", distFromLeftEdge, ofGetHeight()/4 - (10.0/1680.0)*ofGetWidth());
    font.drawString("0", distFromLeftEdge, ofGetHeight()/4 + (70.0/1680.0)*ofGetWidth());
    font.drawString("100", ofGetWidth() - distFromLeftEdge - (20.0/1680.0)*ofGetWidth(), ofGetHeight()/4 + (70.0/1680.0)*ofGetWidth());
    ofNoFill(); //empty to make outline for bar-graph
    ofRect(distFromLeftEdge, ofGetHeight()/4, ofGetWidth() - (100.0/1680.0)*ofGetWidth(), (distFromLeftEdge/1680.0)*ofGetWidth()); //outline of bar-graph
    
    if (attention > 0.0)
    {
        ofSetColor(ofColor::white, ofMap(currAw, 0.0, ofGetWidth(), 50, 255));
        font.drawString(ofToString(attention), distFromLeftEdge + (10.0/1680.0)*ofGetWidth(), ofGetHeight()/4 + (40.0/1680.0)*ofGetWidth()); //attention # in bar-graph
    }
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(ofColor::white);
    string qStr = "";
    
    if (thinkGear.getSignalQuality() == 0.0)
    {
        qStr = "good";
        ofPushStyle();
        ofSetColor(0, 255, 0);
        //        ofEllipse(25, ofGetScreenHeight()-25, 10, 10);
        ofPopStyle();
    }
    else
    {
        qStr = "poor (" + ofToString(thinkGear.getSignalQuality()) + ")";
        ofPushStyle();
        ofSetColor(255, 0, 0);
        //        ofEllipse(25, ofGetScreenHeight()-25, 10, 10);
        ofPopStyle();
    }
    
    float total = 0;
    float firstHalf = 0;
    float secondHalf = 0;
    
    //------------- CALCULATE total/first-half/second-half attention averages
    
    for(int i = 0; i < (int)attValues.size(); i++){
        total+=attValues[i];
    }
    total=total/(attValues.size());
    cout << "total: " << total << endl;
    
    for(int i = 0; i < (int)attValues.size()/2; i++){
        firstHalf+=attValues[i];
    }
    firstHalf=firstHalf/(attValues.size()/2);
    cout << "firstHalf: " << firstHalf << endl;
    
    
    for(int i = (int)attValues.size()/2; i < attValues.size(); i++){
        secondHalf+=attValues[i];
    }
    secondHalf=secondHalf/(attValues.size()/2);
    cout << "secondHalf: " << secondHalf << endl;
    
    
    //------------ Line Graph ---//
    
    font.drawString("Signal Quality: " + ofToString(signalQuality) + "%", distFromLeftEdge, 40);
    ofPushStyle();
    if(getChapterAttention()<=45) ofSetColor(194, 79, 79);
    else if(getChapterAttention()>=55) ofSetColor(110, 197, 106);
    else ofSetColor(202, 197, 114);
    font.drawString("Avg. Attention (Chapter): " + ofToString(total), distFromLeftEdge, 80);
    ofPopStyle();
    //    font.drawString("Avg. Attention (Chapter): " + ofToString(total), distFromLeftEdge, 80);
    font.drawString("Avg. Attention (1st Half): " + ofToString(firstHalf), distFromLeftEdge, 120);
    font.drawString("Avg. Attention (2nd Half): " + ofToString(secondHalf), distFromLeftEdge, 160);
    ofPopStyle();
    
    //draw line-graph BG
    ofPushStyle();
    ofSetColor(50, 50, 50, 50); // opaque gray
    ofRect(distFromLeftEdge, (ofGetHeight()/2)-(100.0/1680.0)*ofGetWidth(), ofGetWidth()-((2*distFromLeftEdge)/1680.0)*ofGetWidth(), (200.0/1680.0)*ofGetWidth());
    ofPopStyle();
    
    //draw mid-line for line-graph
    ofPushStyle();
    ofSetColor(123, 123, 123);
    ofLine(distFromLeftEdge, ofGetHeight()/2, ofGetWidth()-(50.0/1680.0)*ofGetWidth(), ofGetHeight()/2);
    ofPopStyle();
    
    if(attValues.size()>0){
        for (int i = 0; i < attValues.size()-1; i++) {
            ofPushStyle();
            ofSetColor(0, 0, 255);
            ofEllipse(ofMap(i, 0, attValues.size(), (50.0/1680.0)*ofGetWidth(), ofGetWidth()-(50.0/1680.0)*ofGetWidth()), ofGetHeight()/2+(100.0/1680.0)*ofGetWidth()-attValues[i]*2, (5.0/1680.0)*ofGetWidth(), (5.0/1680.0)*ofGetWidth());
            ofSetLineWidth((5.0/1680.0)*ofGetWidth());
            ofLine(ofMap(i, 0, attValues.size(), (50.0/1680.0)*ofGetWidth(), ofGetWidth()-(50.0/1680.0)*ofGetWidth()), ofGetHeight()/2+(100.0/1680.0)*ofGetWidth()-attValues[i]*2, ofMap(i+1, 0, attValues.size(), (50.0/1680.0)*ofGetWidth(), ofGetWidth()-(50.0/1680.0)*ofGetWidth()), ofGetHeight()/2+(100.0/1680.0)*ofGetWidth()-attValues[i+1]*2);
            ofEllipse(ofMap(i+1, 0, attValues.size(), (50.0/1680.0)*ofGetWidth(), ofGetWidth()-(50.0/1680.0)*ofGetWidth()),ofGetHeight()/2+(100.0/1680.0)*ofGetWidth()-attValues[i+1]*2, (5.0/1680.0)*ofGetWidth(), (5.0/1680.0)*ofGetWidth());
            ofPopStyle();
        }
    }
    
    ofPopMatrix();
}

//void EEG::disconnect(){
//    thinkGear.disconnect();
//}
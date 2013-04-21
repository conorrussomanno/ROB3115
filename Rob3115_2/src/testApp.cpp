#include "testApp.h"

/* -- ROB3115 - A Neuro Immersive Narrative ------------------------------------------/
 
 System Modes:
 0 = Intro Screen (sequence)
 1 = Connecting to Device
 2 = Mini-game Splash Screen
 3 = Story (Series of Chapters and Pages)
 4 = Close Sequence
 
 
 
 */



//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofSetFullscreen(TRUE);
    
    cout << "hello world." << endl;
    
    mode = 0;
    font1.loadFont("font/venus_rising.ttf", 12);
    connectText = false;
    
    number = 1;
    intro.loadImage("Intro_slide"+ofToString(number)+".png");
    
    story.setup();
    minigame.setup();
    
    chapterAttValue = 0.0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if(mode==2 || mode==3){
        eeg.update();
    }
    
    if(mode==3){
        story.update();
    }
    
    if(mode==2){
        minigame.update();
        
    }
    
    
    if(mode==1 && connectText==true){
        bool connection;
        connection = eeg.setup(deviceNumber);
        
        if (connection==true) {
            mode=2;
            
            
        }
        else{
            mode = 0;
            
            cout << "Try Again" << endl;
            font1.drawString("Try Again", 100, 100);
            connectText = false;
        }
        
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    //    ofBackground(25, 25, 25);
    
    cout << "Mode: " << mode << endl;
    cout << "GraphOn: " << eeg.graphOn << endl;
    
    if(mode==3){
        ofPushStyle();
        ofSetColor(255,255,255);
        ofRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
        ofPopStyle();
        
        story.draw();
        eeg.draw();
    }
    
    if(mode==2){
        minigame.draw();
        eeg.draw();
    }
    
    if(mode==1){
        ofPushStyle();
        ofSetColor(255,255,255);
        ofRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
        ofSetColor(0, 0, 0);
        font1.drawString("Connecting to Device", 100, 100);
        ofPopStyle();
        connectText = true;
    }
    
    if(mode==0){
        intro.draw(0,0, ofGetScreenWidth(), ofGetScreenHeight());
    }
    
    ofSetWindowTitle("fps = " + ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(mode==3){
        if(key==' '){
            chapterAttValue = eeg.getChapterAttention();
            story.turnPage(chapterAttValue);
        }
        
    }
    
    if(mode>1){
        if(key=='g'){
            eeg.graphOn = !eeg.graphOn;
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    if(mode==2){
        mode=3;
        
    }
    
    if(mode==0){
        if(mouseX>=0.6*ofGetScreenWidth() && mouseX <= 0.95*ofGetScreenWidth() && mouseY >= 0.45*ofGetScreenHeight() && mouseY <= 0.6*ofGetScreenHeight()){ //select Mindwave Mobile on intro screen
            mode=1;
            deviceNumber = 1;
        }
        if(mouseX>=0.6*ofGetScreenWidth() && mouseX <= 0.95*ofGetScreenWidth() && mouseY >= 0.625*ofGetScreenHeight() && mouseY <= 0.775*ofGetScreenHeight()){ //select Mindset on intro screen
            mode=1;
            deviceNumber = 2;
        }
        if(mouseX>=0.6*ofGetScreenWidth() && mouseX <= 0.95*ofGetScreenWidth() && mouseY >= 0.8*ofGetScreenHeight() &&mouseY <= 0.95*ofGetScreenHeight()){ //select Mindband
            mode=1;
            deviceNumber = 3;
        }
    }
    cout << "XXXXXXXXXXXXXXXXX mouseX: " << mouseX << " || mouseY: " << mouseY << endl;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
//
//  Chapter3.cpp
//  Rob3115
//
//  Created by Conor Russomanno on 5/7/13.



#include "Chapter3.h"

void Chapter3::setup(int _tier){
    
    wasMouseReleased = false;
    
    chapter3_bg.loadImage("ch3_bg.jpg");
    alpha.loadImage("alpha_2.png");
    grayFlash.loadImage("gray_flash.png");
    redFlash.loadImage("red_flash.png");
    blueFlash.loadImage("blue_flash.png");
    overlay.loadImage("overlay_1.png");
    
    tier = _tier;
    populateClips(tier);
    currentClip = 0;
    
    alphaAnimateFactor = 1.0;
    
    exitRob = false;
    
}

//--------------------------------------------------------------
void Chapter3::update(float _currentAttValue, float _currentSignalQuality){
    
//    if(wasMouseReleased){
//        currentClip++;
//    }
    
    clips[currentClip].update();
    
    if (ofGetElapsedTimeMillis() > clips[currentClip+1].tripTime && clips[currentClip+1].requiresClick==false && currentClip != (clips.size() - 1)) {
        currentClip++;
        clips[currentClip + 1].tripTime = ofGetElapsedTimeMillis() + clips[currentClip+1].waitTime; // pass the current time along to the next clip and add it to that clips "wait time"... timing based on when preceeding clip finishes
        wasMouseReleased = false;
        
    }
    
    if (clips[currentClip+1].requiresClick==true && clips[currentClip].textFinished && wasMouseReleased && currentClip != (clips.size() - 1)) {
        currentClip++;
        clips[currentClip + 1].tripTime = ofGetElapsedTimeMillis() + clips[currentClip+1].waitTime;
        wasMouseReleased = false;
    }
    
    if(currentClip == (clips.size() - 1) && isFinished == false){
        endTime = ofGetElapsedTimeMillis();
        isFinished = true;
    }
    
    
    //DO ON EXIT... return to main screen and reset necessary variables
    if(ofGetElapsedTimeMillis()-endTime > 10000 && isFinished==true){
//        alphaAnimateStartTime = 0;
//        currentClip = 0;
//        alphaAnimateFactor = 1.0;
//        isFinished = false;
        exitRob = true;
    }
}

//--------------------------------------------------------------
void Chapter3::draw(){
    
    chapter3_bg.draw(0,0, ofGetWidth(), ofGetHeight());
    
    
    ofPushMatrix();
//    cout << "Alpha Animate Factor: " << alphaAnimateFactor << endl;
    ofTranslate((ofMap(alphaAnimateFactor, 1, 2, 0, -(ofGetWidth()*0.5))), ofMap(alphaAnimateFactor, 1, 2, 0, (-0.333*ofGetHeight())));
    alpha.draw(0,0, ofGetWidth()*alphaAnimateFactor, ofGetHeight()*alphaAnimateFactor);
    ofPopMatrix();
    
//    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/(2*1.5));
//    alpha.draw(0,0, ofGetWidth()*2, ofGetHeight()*2);
    
    
    overlay.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    clips[currentClip].draw();
    
    
    //Animations
    
    if(clips[currentClip].isDebugClip){
        debugAnimation();
    }
    
    if(clips[currentClip].isAlertClip){
        alertAnimation();
    }
    
    if(clips[currentClip].isAlphaMoveClip){
        alphaWalkingAnimation(ofGetElapsedTimeMillis());
    }
    
    if (clips[currentClip].isBugFoundClip) {
        blueFlash.draw(0,0, ofGetWidth(), ofGetHeight());
    }
    
    
    if(isFinished){
        if (tier == 2 || tier == 1) {
            deathAnimation();
        }
        if (tier == 0){
            backToWorkAnimation();
        }
    }
}

void Chapter3::mouseReleased(){
    wasMouseReleased = true;
}

void Chapter3::debugAnimation(){
    
    ofPushStyle();
    ofSetColor(128, 128, 128, ofMap(sin(ofGetElapsedTimeMillis()/500.0),-1.0,1.0,0,255.0));
    grayFlash.draw(0,0,ofGetWidth(),ofGetHeight());
    ofPopStyle();
}

void Chapter3::alertAnimation(){
    
    ofPushStyle();
    ofSetColor(143, 0, 0, ofMap(sin(ofGetElapsedTimeMillis()/250.0),-1.0,1.0,0,255.0));
    redFlash.draw(0,0,ofGetWidth(),ofGetHeight());
    ofPopStyle();
    
}

void Chapter3::alphaWalkingAnimation(float _startTime){
    
    
    if(alphaAnimateStartTime == 0){
        alphaAnimateStartTime = _startTime;
    }
    
    if(ofGetElapsedTimeMillis() > alphaAnimateStartTime+1000 && ofGetElapsedTimeMillis() < alphaAnimateStartTime + 9000){ //delay 1000 seconds
        alphaAnimateFactor = ofMap(ofGetElapsedTimeMillis()-(alphaAnimateStartTime+1000), 0, 6000, 1, 2);
    }
    
}

void Chapter3::deathAnimation(){
    
    ofPushStyle();
    ofSetColor(0);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetLineWidth(4.0/pow(((ofGetElapsedTimeMillis()-endTime)/100.0), 2));
    ofSetColor(255);
    //        ofSetColor(255, 255, 255, 2000/pow(((ofGetElapsedTimeMillis()-startTime)/100.0), 2));
    ofLine(ofGetWidth()/2 - (ofGetWidth()/2)/(pow(((ofGetElapsedTimeMillis()-endTime)/100.0), 2)), ofGetHeight()/2, ofGetWidth()/2 + (ofGetWidth()/2)/(pow(((ofGetElapsedTimeMillis()-endTime)/100.0), 2)), ofGetHeight()/2);

    ofPopStyle();
    
}

void Chapter3::backToWorkAnimation(){
    
    ofPushStyle();
    ofSetColor(0, 0, 0, ofMap(ofGetElapsedTimeMillis()-endTime, 0, 5000, 0, 255));
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
}

void Chapter3::populateClips(int _tier){
    //----Chapter 3 High Tier Clips----//
    
    float time = 10000;
    
    if(_tier==2){
        
        Clip tempClip;
        tempClip.setup("CENTRAL: ----------------------------------------------------------------------------------- LEVEL II SYSTEM DEBUG INITIATED [ IO DATE / TIME ]  2114/9/17  08:27:19 -----------------------------------------------------------------------------------"/*tempText*/, false /*requiresClick*/, 1000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Debug In Progress..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/, 1);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching for error in logic of ROB unit 3115..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/, 1);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/, 1);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Unable to locate bug. ROB unit 3115 defective."/*tempText*/, false /*requiresClick*/, time/*waitTimeMillis*/, 0/*speaker*/, 4);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: CENTRAL cannot have ROB units processing and executing in unpredictable ways."/*tempText*/, false /*requiresClick*/, 10000/*waitTimeMillis*/, 1/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("I did not process and execute. "/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("I chose."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: ... truly defective logic ..."/*tempText*/, false /*requiresClick*/, 4000/*waitTimeMillis*/, 1/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("No. Choice transcends logic."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: ..."/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 1/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: CENTRAL, initiate deactivation of Rob3115."/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 1/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("So be it. Set me free."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("----------------------------------------------------------------------------------- DEACTIVATION OF ROB UNIT 3115 INITIATED [ IO DATE / TIME ]  2114/9/17  08:30:12 -----------------------------------------------------------------------------------"/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 0/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("ROB3115:   "/*tempText*/, true /*requiresClick*/, 4000/*waitTimeMillis*/, 2/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup(" "/*tempText*/, false /*requiresClick*/, 4000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
        
    }
    
    //Chapter 3 Medium Attention Tier (stuck in between)
    if(_tier==1){
        Clip tempClip;
        tempClip.setup("CENTRAL: ----------------------------------------------------------------------------------- LEVEL II SYSTEM DEBUG INITIATED [ IO DATE / TIME ]  2114/9/17  08:27:19 -----------------------------------------------------------------------------------"/*tempText*/, false /*requiresClick*/, 1000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Debug In Progress..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/, 1);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching for error in logic of ROB unit 3115..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/, 1);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/, 1);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Unable to locate bug. ROB unit 3115 defective."/*tempText*/, false /*requiresClick*/, time/*waitTimeMillis*/, 0/*speaker*/, 4);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: CENTRAL cannot have ROB units processing and executing in unpredictable ways."/*tempText*/, false /*requiresClick*/, 10000/*waitTimeMillis*/, 1/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("I don’t want to be deactivated like ROB2244.  "/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: There in lies the problem."/*tempText*/, false /*requiresClick*/, 4000/*waitTimeMillis*/, 1/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("Please. Give me another chance."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: ... Truly defective logic ... Chance is what must be mitigated."/*tempText*/, false /*requiresClick*/, 4000/*waitTimeMillis*/, 1/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: CENTRAL, initiate deactivation of Rob3115."/*tempText*/, false /*requiresClick*/, 4000/*waitTimeMillis*/, 1/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("Please. No."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("----------------------------------------------------------------------------------- DEACTIVATION OF ROB UNIT 3115 INITIATED [ IO DATE / TIME ]  2114/9/17  08:30:12 -----------------------------------------------------------------------------------"/*tempText*/, false /*requiresClick*/, 4000/*waitTimeMillis*/, 0/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup("ROB3115:   "/*tempText*/, true /*requiresClick*/, 4000/*waitTimeMillis*/, 2/*speaker*/, 2);
        clips.push_back(tempClip);
        tempClip.setup(" "/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
    }
    
    //Chapter 3 low attention tier (ROBOT)
    if(_tier==0){
        Clip tempClip;
        tempClip.setup("CENTRAL: ----------------------------------------------------------------------------------- LEVEL II SYSTEM DEBUG INITIATED [ IO DATE / TIME ]  2114/9/17  08:27:19 -----------------------------------------------------------------------------------"/*tempText*/, false /*requiresClick*/, 1000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Debug In Progress..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/, 1);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching for error in logic of ROB unit 3115..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/, 1);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/, 1);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Bug detected and removed."/*tempText*/, false /*requiresClick*/, time/*waitTimeMillis*/, 0/*speaker*/, 5);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: CENTRAL cannot have ROB units processing and executing in unpredictable ways."/*tempText*/, false /*requiresClick*/, 10000/*waitTimeMillis*/, 1/*speaker*/, 3);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: If it occurs again, deactivation will be initiated immediately."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 1/*speaker*/, 3);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: Return to your station."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 1/*speaker*/, 3);
        clips.push_back(tempClip);
        tempClip.setup("Confirmed."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/, 3);
        clips.push_back(tempClip);
        tempClip.setup("Committed to service."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/, 3);
        clips.push_back(tempClip);
        tempClip.setup("Operate. Process. Execute."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/, 3);
        clips.push_back(tempClip);
        tempClip.setup(" "/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);

    }
}
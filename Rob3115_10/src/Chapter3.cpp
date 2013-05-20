//
//  Chapter3.cpp
//  Rob3115
//
//  Created by Conor Russomanno on 5/7/13.


#include "Chapter3.h"

void Chapter3::setup(int _tier){
    
    wasMouseReleased = false;
    
    populateClips(_tier);
    currentClip = 0;
    
}

//--------------------------------------------------------------
void Chapter3::update(float _currentAttValue, float _currentSignalQuality){
    
    clips[currentClip].update();
    
    if (ofGetElapsedTimeMillis() > clips[currentClip+1].tripTime && clips[currentClip+1].requiresClick==false) {
        currentClip++;
        clips[currentClip + 1].tripTime = ofGetElapsedTimeMillis() + clips[currentClip+1].waitTime; // pass the current time along to the next clip and add it to that clips "wait time"... timing based on when preceeding clip finishes
        
    }
    
    if (clips[currentClip+1].requiresClick==true && clips[currentClip].textFinished && wasMouseReleased) {
        currentClip++;
        clips[currentClip + 1].tripTime = ofGetElapsedTimeMillis() + clips[currentClip+1].waitTime;
        wasMouseReleased = false;
        
    }
}

//--------------------------------------------------------------
void Chapter3::draw(){
    
    clips[currentClip].draw();
    
}

void Chapter3::mouseReleased(){
    
    wasMouseReleased = true;
    
}

void Chapter3::alertAnimation(){
    
}

void Chapter3::alphaWalkingAnimation(){
    
}

void Chapter3::deathAnimation(){
    
}

void Chapter3::backToWorkAnimation(){
    
}

void Chapter3::populateClips(int _tier){
    //----Chapter 3 High Tier Clips----//
    if(_tier==2){
        
        Clip tempClip;
        tempClip.setup("CENTRAL: -------------------------------------------------- LEVEL II SYSTEM DEBUG INITIATED [IO DATE/TIME]  2114/9/17  08:27:19 --------------------------------------------------"/*tempText*/, false /*requiresClick*/, 1000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Debug In Progress..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching for error in logic of ROB unit 3115..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Unable to locate bug in logic..."/*tempText*/, false /*requiresClick*/, 15000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: CENTRAL cannot have ROB units processing and executing in unpredictable ways."/*tempText*/, false /*requiresClick*/, 9000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("I did not process and execute. "/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("I chose."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: ... truly defective logic ..."/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("No. Choice transcends logic."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: ..."/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: CENTRAL, initiate deactivation of Rob3115."/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("So be it. Set me free."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("-------------------------------------------------- DEACTIVATION OF ROB UNIT 3115 INITIATED [IO DATE/TIME]  2114/9/17  08:30:12 --------------------------------------------------"/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ROB3115:   "/*tempText*/, true /*requiresClick*/, 4000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
        
    }
    
    //Chapter 3 Medium Attention Tier (stuck in between)
    if(_tier==1){
        Clip tempClip;
        tempClip.setup("CENTRAL: -------------------------------------------------- LEVEL II SYSTEM DEBUG INITIATED [IO DATE/TIME]  2114/9/17  08:27:19 --------------------------------------------------"/*tempText*/, false /*requiresClick*/, 1000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Debug In Progress..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching for error in logic of ROB unit 3115..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Unable to locate bug in logic..."/*tempText*/, false /*requiresClick*/, 15000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: CENTRAL cannot have ROB units processing and executing in unpredictable ways."/*tempText*/, false /*requiresClick*/, 9000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("I don’t want to be deactivated like ROB2244.  "/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: There in lies the problem."/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("Please. Give me another chance."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: ... Truly defective logic ... Chance is what must be mitigated."/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: CENTRAL, initiate deactivation of Rob3115."/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("Please. No."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("-------------------------------------------------- DEACTIVATION OF ROB UNIT 3115 INITIATED [IO DATE/TIME]  2114/9/17  08:30:12 --------------------------------------------------"/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ROB3115:   "/*tempText*/, true /*requiresClick*/, 4000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
    }
    
    //Chapter 3 low attention tier (ROBOT)
    if(_tier==0){
        Clip tempClip;
        tempClip.setup("CENTRAL: -------------------------------------------------- LEVEL II SYSTEM DEBUG INITIATED [IO DATE/TIME]  2114/9/17  08:27:19 --------------------------------------------------"/*tempText*/, false /*requiresClick*/, 1000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Debug In Progress..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching for error in logic of ROB unit 3115..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Searching..."/*tempText*/, false /*requiresClick*/, 5000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("CENTRAL: Bug detected and removed."/*tempText*/, false /*requiresClick*/, 15000/*waitTimeMillis*/, 0/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: CENTRAL cannot have ROB units processing and executing in unpredictable ways."/*tempText*/, false /*requiresClick*/, 9000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: If it occurs again, deactivation will be initiated immediately."/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("ALPHA214: Return to your station."/*tempText*/, false /*requiresClick*/, 3000/*waitTimeMillis*/, 1/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("Confirmed."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);
        tempClip.setup("Committed to service."/*tempText*/, true /*requiresClick*/, 1000/*waitTimeMillis*/, 2/*speaker*/);
        clips.push_back(tempClip);

    }
}
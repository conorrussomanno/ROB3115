//
//  LoadThread.h
//  Rob3115
//
//  Created by Conor Russomanno on 5/5/13.
//
//

#pragma once
#include "ofMain.h"
#include "HUDSpinner.h"

class LoadThread : public ofThread {
    
public:
    
    HUDSpinner loadSpinner;
    ofColor c;
    bool finishedSetup;
    
    void threadedFunction(){
        
        while(isThreadRunning()) {
            
//            lock();
//            cout << finishedSetup << endl;
//            if(finishedSetup == false){
//                c.set(255);
//                loadSpinner.setup(20, 0, 5, c, 100, (100.0/1680.0)*ofGetWidth(), (300.0/1680.0)*ofGetWidth(), (10.0/1680.0)*ofGetWidth(), (200.0/1680.0)*ofGetWidth(), false);
//                finishedSetup = true;
//            }
////
//            loadSpinner.update(100, 100);
//            loadSpinner.draw(ofGetWidth()/2, ofGetHeight()/2);
//
            cout << "THREAD BITCHES" << endl;
//
//            unlock();
        }
    }

};
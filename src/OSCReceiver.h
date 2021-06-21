//
//  Coin.h
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

// Listen on port 8000;
#define PORT 8000
#define NUM_MSG_STRINGS 20

class OSCReceiver{

    public:
    OSCReceiver();
    
            // Functions
            void setup();
            void update();
            void draw();

            // OSC Vars;
            ofxOscReceiver receiver;
            int maxBufferSize = 20;
            deque<string> messageBuffer;
            glm::vec2 leftWristPos;
            glm::vec2 rightWristPos;
            
            // Width and Height vars;
            int width, height;
    
};

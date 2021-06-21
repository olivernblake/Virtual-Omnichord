//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "OSCReceiver.h"

//-------------------------------------------------------
OSCReceiver::OSCReceiver()
{
    
}

//--------------------------------------------------------
void OSCReceiver::setup()   {
    // Setup Receiver;
    cout << "OSC set on Port: " << PORT << endl;
    receiver.setup(PORT);
    
    // Width and height vars;
    width = ofGetWidth();
    height = ofGetHeight();
}
//--------------------------------------------------------------
void OSCReceiver::update() {
    // Listen for OSC Messages;
    if (messageBuffer.size()>maxBufferSize) messageBuffer.pop_back();

    // Check for waiting messages;
    while(receiver.hasWaitingMessages()){
        // Get new message;
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/poseNet/leftWrist"){
            // Unpack message;
            int poseNum = m.getArgAsInt(0);
            // Only detect one skeleton;
            if (poseNum == 0) {
                float leftWristX = m.getArgAsFloat(1);
                float leftWristY = m.getArgAsFloat(2);
                float mapLWX = ofMap(leftWristX, 0, 1024, width, 0, true);
                float mapLWY = ofMap(leftWristY, 0, 768, 0, height, true);
                leftWristPos = glm::vec2(mapLWX, mapLWY);
            }
        }
        
        if(m.getAddress() == "/poseNet/rightWrist"){
            // Unpack message;
            int poseNum = m.getArgAsInt(0);
            // Only detect one skeleton;
            if (poseNum == 0) {
                float rightWristX = m.getArgAsFloat(1);
                float rightWristY = m.getArgAsFloat(2);
                float mapRWX = ofMap(rightWristX, 0, 1024, width, 0, true);
                float mapRWY = ofMap(rightWristY, 0, 768, 0, height, true);
                rightWristPos = glm::vec2(mapRWX, mapRWY);
            }
        }
    }
}
//--------------------------------------------------------------
void OSCReceiver::draw(){
   
}
//--------------------------------------------------------------

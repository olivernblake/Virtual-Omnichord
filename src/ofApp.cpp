#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetCircleResolution(60);
    
    // Webcam setup;
    ofSetFrameRate(60);
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640,480);
    
    // Setup Boxes;
    drawBoxes.setup();
    drawHarp.setup();
    
    // Setup OSC;
    oscRec.setup();
    
    // Default Wood and Sin modes;
    woodMode = true;
    spaceMode = false;
    sin = true;
    saw = false;
    modeNum = 1;
    
    // Draw Instructions;
    drawInst = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update Modes;
    updateModes();
    
    // Update Vid Grabber;
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()){
        // Update Current Frame ofImage;
        currentFrame = vidGrabber.getPixels();
        currentFrame.mirror(false, true);
    }
    
    // Update Harp and Boxes with OSC;
    oscRec.update();
    drawBoxes.leftFingerPos = oscRec.leftWristPos;
    drawHarp.rightFingerPos = oscRec.rightWristPos;
    
    // Update DrawBoxes (for Chords);
    drawBoxes.update();
    
    // Update Harp with which Chords;
    updateTrigNum();
    
    // Update DrawHarp;
    drawHarp.update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    // Draw Webcam;
    ofPushStyle();
    if (woodMode) {
        ofSetColor(255);
    } else if (spaceMode) {
        ofSetColor(255, 100);
    }
    currentFrame.draw(0, 0);
    ofPopStyle();
    
    // Draw Boxes;
    drawBoxes.draw();
    drawHarp.draw();
    
    // Draw Mode (& Instructions);
    drawInstructions();
}

//--------------------------------------------------------------
void ofApp::exit() {
    drawBoxes.exit();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        // Activate Wood and Sin modes;
        woodMode = true;
        spaceMode = false;
        sin = true;
        saw = false;
        modeNum = 1;
    }
    if (key == '2') {
        // Activate Space and Sin modes;
        woodMode = false;
        spaceMode = true;
        sin = true;
        saw = false;
        modeNum = 2;
    }
    if (key == '3') {
        // Activate Wood and Saw modes;
        woodMode = true;
        spaceMode = false;
        sin = false;
        saw = true;
        modeNum = 3;
    }
    if (key == '4') {
        // Activate Space and Saw modes;
        woodMode = false;
        spaceMode = true;
        sin = false;
        saw = true;
        modeNum = 4;
    }
    
    if (key == 'i' || key == 'I') {
        drawInst = !drawInst;
    }
}

//--------------------------------------------------------------
void ofApp::drawInstructions() {
    ofPushStyle();
    if (woodMode) ofSetColor(0);
    if (spaceMode) ofSetColor(255);
    
    // Draw Mode Num;
    string modeString = "Mode: " + ofToString(modeNum);
    ofDrawBitmapString(modeString, 10, 20);
    
    // Draw Instructions;
    if (drawInst) {
        string instructions = "Cycle through the modes with buttons 1, 2, 3 and 4";
        ofDrawBitmapString(instructions, 109, 20);
        string boxString1 = "Hold you left hand over these";
        string boxString2 = "Boxes to play Chords";
        string harpString1 = "Use your Right hand to";
        string harpString2 = "strum these Harp strings";
        int instLine1 = 380;
        int instLine2 = instLine1 + 20;
        ofDrawBitmapString(boxString1, 45, instLine1);
        ofDrawBitmapString(boxString2, 82, instLine2);
        ofDrawBitmapString(harpString1, 393, instLine1);
        ofDrawBitmapString(harpString2, 385, instLine2);
    }
    
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::updateModes() {
    if (woodMode) {
        // Draw Boxes;
        drawBoxes.woodMode = true;
        drawBoxes.spaceMode = false;
        
        // Draw Harp;
        drawHarp.woodMode = true;
        drawHarp.spaceMode = false;
        
        // Bubble System;
        drawHarp.bubbleSys.woodMode = true;
        drawHarp.bubbleSys.spaceMode = false;
        
    } else if (spaceMode) {
        // Draw Boxes;
        drawBoxes.woodMode = false;
        drawBoxes.spaceMode = true;
        
        // Draw Harp;
        drawHarp.woodMode = false;
        drawHarp.spaceMode = true;
        
        // Bubble System;
        drawHarp.bubbleSys.woodMode = false;
        drawHarp.bubbleSys.spaceMode = true;
        
    }
    
    if (sin) {
        // Draw Boxes;
        drawBoxes.sin = true;
        drawBoxes.saw = false;
        
        // Draw Harp;
        drawHarp.sin = true;
        drawHarp.saw = false;
        
        // Bubble System;
        drawHarp.bubbleSys.sin = true;
        drawHarp.bubbleSys.saw = false;
    
    } else if (saw) {
        // Draw Boxes;
        drawBoxes.sin = false;
        drawBoxes.saw = true;
        
        // Draw Harp;
        drawHarp.sin = false;
        drawHarp.saw = true;
        
        // Bubble System;
        drawHarp.bubbleSys.sin = false;
        drawHarp.bubbleSys.saw = true;
    
    }
}
//--------------------------------------------------------------
void ofApp::updateTrigNum() {
    if (drawBoxes.trig1) {
        drawHarp.trigNum = 1;
    } else if (drawBoxes.trig2) {
        drawHarp.trigNum = 2;
    } else if (drawBoxes.trig3) {
        drawHarp.trigNum = 3;
    } else if (drawBoxes.trig4) {
        drawHarp.trigNum = 4;
    } else {
        drawHarp.trigNum = 0;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

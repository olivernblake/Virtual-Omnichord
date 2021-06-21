//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "DrawBoxes.h"

//-------------------------------------------------------
DrawBoxes::DrawBoxes()
{
    
}

//--------------------------------------------------------
void DrawBoxes::setup()  {
    // Default to Wood Mode;
    woodMode = true;
    spaceMode = false;
    sin = true;
    saw = false;
    outlineCol = ofColor::black;
    
    boxSize = 100;
    cursorSize = 5;
    leftFingerPos = glm::vec2(0, 0);
    
    // Box Positions;
    box1pos = glm::vec2(60, ofGetHeight()/2 - boxSize);
    box2pos = glm::vec2(box1pos.x + boxSize, box1pos.y);
    box3pos = glm::vec2(box1pos.x, ofGetHeight()/2);
    box4pos = glm::vec2(box2pos.x, box3pos.y);
    
    // Box Colours;
    box1col = 100;
    box2col = 100;
    box3col = 100;
    box4col = 100;
    
    // Setup Maxim;
    sampleRate = 44100;
    bufferSize = 512;
    
    // settings for ofxMaxim.
    maxiSettings::setup(sampleRate, 2, bufferSize);
    
    //sets up the soundStream object with default devices
    auto devices = soundStream.getMatchingDevices("default");
    //you can also list input/output devices with soundStream.printDeviceList()
    soundSettings.setOutListener(this);
    soundSettings.sampleRate = sampleRate;
    soundSettings.numOutputChannels = 2;
    soundSettings.numInputChannels = 0; // change to "2" if the programme crashes
    soundSettings.bufferSize = bufferSize;
    soundStream.setup(soundSettings);
    
    // Init Trigger value as off;
    trig1 = 0;
    trig2 = 0;
    trig3 = 0;
    trig4 = 0;
    
    // Setup ADSR;
    setADSR();
    
    // Init Osc deque;
    for (int i = 0; i < 20; i++) {
        maxiOsc tempOsc;
        osc.push_back(tempOsc);
    }
    
    // Volumes;
    bassVol = 0.25;
    noteVol = 0.1;
    chordVol = 0.1; // because default Wood Mode;
    
}
//--------------------------------------------------------------
void DrawBoxes::update(){
    // Update Mode Stuff;
    if (woodMode) {
        outlineCol = ofColor::black;
    } else if (spaceMode) {
        outlineCol = ofColor::white;
    }
    
    if (sin) {
        chordVol = 0.1;
    } else if (saw) {
        chordVol = 0.05;
    }
    
    // Check Cursor Inside Boxes;
    checkCursorPos();
    
    // Light up selected box;
    highlightBox();
}
//--------------------------------------------------------------
void DrawBoxes::draw(){
    // Draw Boxes;
    drawBoxes();
    
    // Draw Cursor;
    drawCursor();
}
//--------------------------------------------------------------
void DrawBoxes::checkCursorPos() {
    if (leftFingerPos.x > box1pos.x && leftFingerPos.x < box2pos.x) {
        // Inside Boxes 1 or 3;
        if (leftFingerPos.y > box1pos.y && leftFingerPos.y < box3pos.y) {
            // Inside Box 1;
            trig1 = 1;
            trig2 = 0;
            trig3 = 0;
            trig4 = 0;
        } else if (leftFingerPos.y > box3pos.y && leftFingerPos.y < box3pos.y + boxSize) {
            // Inside Box 3;
            trig1 = 0;
            trig2 = 0;
            trig3 = 1;
            trig4 = 0;
        } else {
            trig1 = 0;
            trig2 = 0;
            trig3 = 0;
            trig4 = 0;
        }
    } else if (leftFingerPos.x > box2pos.x && leftFingerPos.x < box2pos.x + boxSize) {
        // Inside Boxes 2 or 4;
        if (leftFingerPos.y > box2pos.y && leftFingerPos.y < box4pos.y) {
            // Inside Box 2;
            trig1 = 0;
            trig2 = 1;
            trig3 = 0;
            trig4 = 0;
        } else if (leftFingerPos.y > box4pos.y && leftFingerPos.y < box4pos.y + boxSize) {
            // Inside Box 4;
            trig1 = 0;
            trig2 = 0;
            trig3 = 0;
            trig4 = 1;
        } else {
            trig1 = 0;
            trig2 = 0;
            trig3 = 0;
            trig4 = 0;
        }
    } else {
        trig1 = 0;
        trig2 = 0;
        trig3 = 0;
        trig4 = 0;
    }
}
//--------------------------------------------------------------
void DrawBoxes::highlightBox() {
    if (trig1) {
        box1col = 255;
    } else {
        box1col = 100;
    }
    
    if (trig2) {
        box2col = 255;
    } else {
        box2col = 100;
    }
    
    if (trig3) {
        box3col = 255;
    } else {
        box3col = 100;
    }
    
    if (trig4) {
        box4col = 255;
    } else {
        box4col = 100;
    }
}
//--------------------------------------------------------------
void DrawBoxes::makeSawChord(int chordNum) {
    if (chordNum == 1) {
        double lowC = osc[0].saw(65.41) * bassVol;
        double d3 = osc[1].saw(146.83 * 2) * noteVol;
        double e3 = osc[2].saw(164.81) * noteVol;
        double g3 = osc[3].saw(196 * 2) * noteVol;
        double b3 = osc[4].saw(246.94) * noteVol/2;
        chord1 = (lowC + d3 + e3 + g3 + b3) * chordVol;
    }
    
    if (chordNum == 2) {
        double lowF = osc[5].saw(87.31) * bassVol;
        double d3 = osc[6].saw(146.83 * 2) * noteVol;
        double e3 = osc[7].saw(164.81) * noteVol;
        double a3 = osc[8].saw(220 * 2) * noteVol;
        double c4 = osc[9].saw(261.63) * noteVol/2;
        chord2 = (lowF + d3 + e3 + a3 + c4) * chordVol;
    }
    
    if (chordNum == 3) {
        double lowG = osc[15].saw(98) * bassVol;
        double d3 = osc[16].saw(146.83 * 2) * noteVol;
        double f3 = osc[17].saw(174.61) * noteVol;
        double a3 = osc[18].saw(220 * 2) * noteVol;
        double b3 = osc[19].saw(246.94) * noteVol/2;
        chord3 = (lowG + d3 + f3 + a3 + b3) * chordVol;
    }
    
    if (chordNum == 4) {
        double lowA = osc[10].saw(110) * bassVol;
        double e3 = osc[11].saw(164.81 * 2) * noteVol;
        double g3 = osc[12].saw(196) * noteVol;
        double b3 = osc[13].saw(246.94 * 2) * noteVol;
        double c4 = osc[14].saw(261.63) * noteVol/2;
        chord4 = (lowA + e3 + g3 + b3 + c4) * chordVol;
    }
}
//--------------------------------------------------------------
void DrawBoxes::makeTriChord(int chordNum) {
    if (chordNum == 1) {
        double lowC = osc[0].triangle(65.41) * bassVol;
        double d3 = osc[1].triangle(146.83 * 2) * noteVol;
        double e3 = osc[2].triangle(164.81) * noteVol;
        double g3 = osc[3].triangle(196 * 2) * noteVol;
        double b3 = osc[4].triangle(246.94) * noteVol/2;
        chord1 = (lowC + d3 + e3 + g3 + b3) * chordVol;
    }
    
    if (chordNum == 2) {
        double lowF = osc[5].triangle(87.31) * bassVol;
        double d3 = osc[6].triangle(146.83 * 2) * noteVol;
        double e3 = osc[7].triangle(164.81) * noteVol;
        double a3 = osc[8].triangle(220 * 2) * noteVol;
        double c4 = osc[9].triangle(261.63) * noteVol/2;
        chord2 = (lowF + d3 + e3 + a3 + c4) * chordVol;
    }
    
    if (chordNum == 3) {
        double lowG = osc[15].triangle(98) * bassVol;
        double d3 = osc[16].triangle(146.83 * 2) * noteVol;
        double f3 = osc[17].triangle(174.61) * noteVol;
        double a3 = osc[18].triangle(220 * 2) * noteVol;
        double b3 = osc[19].triangle(246.94) * noteVol/2;
        chord3 = (lowG + d3 + f3 + a3 + b3) * chordVol;
    }
    
    if (chordNum == 4) {
        double lowA = osc[10].triangle(110) * bassVol;
        double e3 = osc[11].triangle(164.81 * 2) * noteVol;
        double g3 = osc[12].triangle(196) * noteVol;
        double b3 = osc[13].triangle(246.94 * 2) * noteVol;
        double c4 = osc[14].triangle(261.63) * noteVol/2;
        chord4 = (lowA + e3 + g3 + b3 + c4) * chordVol;
    }
}
//--------------------------------------------------------------
void DrawBoxes::exit() {
    ofSoundStreamClose();
}
//--------------------------------------------------------------
void DrawBoxes::audioOut(ofSoundBuffer & buffer)    {
    for (unsigned int i = 0; i < buffer.getNumFrames(); i++) {
        
        // Make the 4 chords;
        for (int i = 1; i < 5; i++) {
            if (sin) {
                makeTriChord(i);
            } else if (saw) {
                makeSawChord(i);
            }
        }
        
        // Trigger each chord when necessary;
        float osc1Output = env1.adsr(chord1, trig1);
        float osc2Output = env2.adsr(chord2, trig2);
        float osc3Output = env3.adsr(chord3, trig3);
        float osc4Output = env4.adsr(chord4, trig4);

        // Add all the outputs;
        float oscSum = osc1Output + osc2Output + osc3Output + osc4Output;
        
        buffer[i * buffer.getNumChannels()    ] = oscSum;
        buffer[i * buffer.getNumChannels() + 1] = oscSum;
    }
}
//--------------------------------------------------------------
void DrawBoxes::setADSR() {
    attack = 4000;
    decay = 500;
    sustain = 1;
    release = 1000;
    
    env1.setAttack(attack);
    env1.setDecay(decay);
    env1.setSustain(sustain);
    env1.setRelease(release);
    
    env2.setAttack(attack);
    env2.setDecay(decay);
    env2.setSustain(sustain);
    env2.setRelease(release);
    
    env3.setAttack(attack);
    env3.setDecay(decay);
    env3.setSustain(sustain);
    env3.setRelease(release);
    
    env4.setAttack(attack);
    env4.setDecay(decay);
    env4.setSustain(sustain);
    env4.setRelease(release);
}
//--------------------------------------------------------------
void DrawBoxes::drawCursor() {
    // Draw Cursor;
    ofPushStyle();
    ofFill();
    ofSetColor(ofColor::white);
    ofDrawCircle(leftFingerPos, cursorSize);
    ofPopStyle();
}
//--------------------------------------------------------------
void DrawBoxes::drawBoxes() {
    // Draw Boxes;
    ofNoFill();
    ofSetColor(outlineCol);
    ofDrawRectangle(box1pos, boxSize, boxSize);
    ofDrawRectangle(box2pos, boxSize, boxSize);
    ofDrawRectangle(box3pos, boxSize, boxSize);
    ofDrawRectangle(box4pos, boxSize, boxSize);

    // Draw Shading;
    ofFill();
    ofSetColor(box1col, 100);
    ofDrawRectangle(box1pos, boxSize, boxSize);
    ofSetColor(box2col, 100);
    ofDrawRectangle(box2pos, boxSize, boxSize);
    ofSetColor(box3col, 100);
    ofDrawRectangle(box3pos, boxSize, boxSize);
    ofSetColor(box4col, 100);
    ofDrawRectangle(box4pos, boxSize, boxSize);
}
//--------------------------------------------------------------

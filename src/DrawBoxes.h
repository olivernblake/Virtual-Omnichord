//
//  Coin.h
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#pragma once
#include "ofMain.h"
#include "ofxMaxim.h"

class DrawBoxes{

    public:
    DrawBoxes();
    
            // Functions
            void setup();
            void draw();
            void update();
            void drawCursor();
            void drawBoxes();
            void makeTriChord(int chordNum);
            void makeSawChord(int chordNum);
            void setADSR();
            void highlightBox();
            void checkCursorPos();
    
    // Box Vars;
    int boxSize;
    glm::vec2 box1pos, box2pos, box3pos, box4pos;
    int box1col, box2col, box3col, box4col;

    // Cursor Vars;
    glm::vec2 leftFingerPos;
    int cursorSize;
    
    // Maxim Vars;
    void exit();
    void audioOut(ofSoundBuffer & buffer);
    ofSoundStreamSettings soundSettings;
    ofSoundStream soundStream;
    int sampleRate;
    int bufferSize;
    deque<maxiOsc> osc;
    maxiEnv env1, env2, env3, env4;
    int trig1, trig2, trig3, trig4;
    double chord1, chord2, chord3, chord4;
    double wave;
    int attack, decay, sustain, release;
    float bassVol, noteVol, chordVol;
    
    // Wood/Space Modes;
    bool woodMode, spaceMode;
    ofColor outlineCol;
    bool sin, saw;
    
};

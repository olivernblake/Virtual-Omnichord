//
//  Coin.h
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#pragma once
#include "ofMain.h"
#include "Bubble.h"
#include "Beam.h"
#include "BubbleSystem.h"

class DrawHarp{

    public:
    DrawHarp();
    
            // Functions
            void setup();
            void draw();
            void update();
            void drawLines();
            void drawCircles();
            void drawArrows();
            void drawCursor();
            void checkPlucked();
            void setColours();
    
    // Line Vars;
    int lineSize, lineSpacing;
    deque<int> yPos;
    int lineLeft, lineRight;
    deque<float> lineWidths;
    float lineSpeedReturn, lineMax, lineRest;
    
    // Circle Vars;
    deque<ofColor> colours;
    deque<float> opacs;
    int circleSize;
    deque<float> offsets;
    deque<float> scales;
    float angle;
    
    // Cursor Vars;
    glm::vec2 rightFingerPos;
    int cursorSize;
    
    // Current Trig Mode;
    int trigNum;
    
    // Plucked Vars;
    int trigMargin, newPosMargin;
    glm::vec2 previousPos;
    bool yPosNew;
    bool xInLine;
    bool trigOk;
    
    // Bubbles;
    BubbleSystem bubbleSys;
    
    // Space/Wood
    bool spaceMode, woodMode;
    ofColor lineCol;
    bool sin, saw;
};

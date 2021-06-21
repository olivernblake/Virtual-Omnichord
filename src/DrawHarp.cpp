//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "DrawHarp.h"

//-------------------------------------------------------
DrawHarp::DrawHarp()
{
    
}

//--------------------------------------------------------
void DrawHarp::setup()  {
    lineSize = 150;
    lineSpacing = 50;
    circleSize = 10; // Default Wood Mode;
    cursorSize = 5;
    angle = 0;
    
    // Default Wood Mode and Sin;
    woodMode = true;
    spaceMode = false;
    sin = true;
    saw = false;
    
    // Margin for Error in triggering;
    newPosMargin = 15;
    trigMargin = 15;

    previousPos = glm::vec2(0, 0);
    
    // Set Widths;
    lineLeft = ofGetWidth()/2 + 85;
    lineRight = lineLeft + lineSize;
    
    // Set Heights;
    for (int i = -2; i < 3; i++) {
        int tempY;
        tempY = (ofGetHeight()/2) + (lineSpacing * i);
        yPos.push_back(tempY);
    }
    
    // Set LineWidths;
    for (int i = 0; i < yPos.size(); i++) {
        float initLineWidth;
        initLineWidth = 1;
        lineWidths.push_back(initLineWidth);
    }
    lineSpeedReturn = 0.1;
    lineMax = 3;
    lineRest = 1;
    
    // Set Angle Offsets;
    for (int i = 0; i < yPos.size(); i++) {
        float phase = 360 / (yPos.size() + 1);
        float angleOffset;
        angleOffset = phase * i;
        offsets.push_back(angleOffset);
    }
    
    // Set Scales;
    for (int i = 0; i < yPos.size(); i ++) {
        float initScale;
        initScale = 1;
        scales.push_back(initScale);
    }
    
    // Set Opacs;
    for (int i = 0; i < yPos.size(); i++) {
        float initOpac;
        initOpac = 50;
        opacs.push_back(initOpac);
    }
    
    // Init Colours;
    colours.push_back(ofColor::orangeRed);
    colours.push_back(ofColor::lightPink);
    colours.push_back(ofColor::yellow);
    colours.push_back(ofColor::lightBlue);
    colours.push_back(ofColor::cadetBlue);
    
    // Set Trigger Number to Blank
    trigNum = 0;
    
    // Setup Bubble System;
    bubbleSys.setup();
}
//--------------------------------------------------------------
void DrawHarp::setColours() {
    if (woodMode) {
        colours[0] = ofColor::orangeRed;
        colours[1] = ofColor::lightPink;
        colours[2] = ofColor::yellow;
        colours[3] = ofColor::lightBlue;
        colours[4] = ofColor::cadetBlue;
        
        lineCol = ofColor::black;
        circleSize = 10;
        lineSpeedReturn = 0.1;
    }
    
    if (spaceMode) {
        colours[0] = ofColor::teal;
        colours[1] = ofColor::blueSteel;
        colours[2] = ofColor::deepPink;
        colours[3] = ofColor::purple;
        colours[4] = ofColor::mediumPurple;
        
        lineCol = ofColor::white;
        circleSize = 16;
        lineSpeedReturn = 0.03;
    }
}
//--------------------------------------------------------------
void DrawHarp::update(){
    // Update Visual mode;
    setColours();
    
//    // DEBUG Margins;
//    newPosMargin = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 30, true);
//    trigMargin = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 30, true);
//    cout << "NPM: " << newPosMargin << " TM: " << trigMargin << endl;
    
    // Check if any strings are plucked;
    checkPlucked();
    
    // Update Bubble System;
    bubbleSys.update();
    
    // Slowly Return Linewidths and Opacs (if necessary);
    for (int i = 0; i < lineWidths.size(); i++) {
        if (lineWidths[i] > 1) {
            lineWidths[i] -= lineSpeedReturn;
            opacs[i] = ofMap(lineWidths[i], lineMax, lineRest, 200, 50, true);
            scales[i] = ofMap(lineWidths[i], lineMax, lineRest, 2.2, 1, true);
        }
    }
    
    // Increment Angle;
    angle++;
}
//--------------------------------------------------------------
void DrawHarp::draw(){
    // Draw Cursor;
    drawCursor();
    
    // Draw Strings;
    drawLines();
    
    // Wood Mode = Circles;
    if (woodMode) {
        drawCircles();
    }

    // Space Mode = Arrows;
    if (spaceMode) {
        drawArrows();
    }
    
    // Draw Bubble System;
    bubbleSys.draw();
}
//--------------------------------------------------------------
void DrawHarp::checkPlucked() {
    // Prove me wrong, bools!
    trigOk = false;
    yPosNew = false;
    xInLine = false;
    
    if (trigNum != 0) {
        trigOk = true;
    }
    
    // If we're moving within margin amount, we can continue;
    if (trigOk) {
        if (rightFingerPos.y > previousPos.y + newPosMargin || rightFingerPos.y < previousPos.y - newPosMargin) {
            yPosNew = true;
        }
    }
    
    // If it's a new Y position, is X between the lines?
    if (yPosNew) {
        if (rightFingerPos.x > lineLeft && rightFingerPos.x < lineRight) {
            xInLine = true;
        }
    }
    
    if (xInLine) {
        for (int i = 0; i < yPos.size(); i++) {
            if (rightFingerPos.y < yPos[i] + trigMargin && rightFingerPos.y > yPos[i] - trigMargin) {
                // Make a note and bubble;
                if (woodMode) {
                    if (sin) {
                        bubbleSys.addBubble(glm::vec2(rightFingerPos.x, yPos[i]), i, trigNum, colours[i], "sin");
                    } else if (saw) {
                        bubbleSys.addBubble(glm::vec2(rightFingerPos.x, yPos[i]), i, trigNum, colours[i], "saw");
                    }
                }
                
                // Make a note and beam;
                if (spaceMode) {
                    if (sin) {
                        bubbleSys.addBeam(glm::vec2(rightFingerPos.x, yPos[i]), i, trigNum, colours[i], "sin");
                    } else if (saw) {
                        bubbleSys.addBeam(glm::vec2(rightFingerPos.x, yPos[i]), i, trigNum, colours[i], "saw");
                    }
                }
                
                // "Pluck" the string
                lineWidths[i] = lineMax;
            }
        }
    }
    
    // Update Previous Pos for comparison;
    previousPos = rightFingerPos;
}
//--------------------------------------------------------------
void DrawHarp::drawLines() {
    ofPushStyle();
    ofFill();
    ofSetColor(lineCol);
    for (int i = 0; i < yPos.size(); i++) {
        ofSetLineWidth(lineWidths[i]);
        ofDrawLine(lineLeft, yPos[i], lineRight, yPos[i]);
    }
    ofPopStyle();
}
//--------------------------------------------------------------
void DrawHarp::drawArrows() {
    // Draw Outlines;
    ofPushStyle();
    ofNoFill();
    for (int i = 0; i < yPos.size(); i++) {
        ofSetColor(colours[i]);
        ofPushMatrix();
        ofTranslate(lineLeft, yPos[i]);
        ofRotateDeg(angle + offsets[i]);
        ofScale(scales[i]);
        ofBeginShape();
        ofVertex(0, -circleSize);
        ofVertex(circleSize/2, circleSize/2);
        ofVertex(0, circleSize * 0.1);
        ofVertex(-circleSize/2, circleSize/2);
        ofVertex(0, -circleSize);
        ofEndShape();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(lineRight, yPos[i]);
        ofRotateDeg(angle + offsets[i]);
        ofScale(scales[i]);
        ofBeginShape();
        ofVertex(0, -circleSize);
        ofVertex(circleSize/2, circleSize/2);
        ofVertex(0, circleSize * 0.1);
        ofVertex(-circleSize/2, circleSize/2);
        ofVertex(0, -circleSize);
        ofEndShape();
        ofPopMatrix();
    }
    ofPopStyle();
    
    // Draw Shapes;
    ofPushStyle();
    ofFill();
    for (int i = 0; i < yPos.size(); i++) {
        ofSetColor(colours[i], opacs[i]);
        ofPushMatrix();
        ofTranslate(lineLeft, yPos[i]);
        ofRotateDeg(angle + offsets[i]);
        ofScale(scales[i]);
        ofBeginShape();
        ofVertex(0, -circleSize);
        ofVertex(circleSize/2, circleSize/2);
        ofVertex(0, circleSize * 0.1);
        ofVertex(-circleSize/2, circleSize/2);
        ofVertex(0, -circleSize);
        ofEndShape();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(lineRight, yPos[i]);
        ofRotateDeg(angle + offsets[i]);
        ofScale(scales[i]);
        ofBeginShape();
        ofVertex(0, -circleSize);
        ofVertex(circleSize/2, circleSize/2);
        ofVertex(0, circleSize * 0.1);
        ofVertex(-circleSize/2, circleSize/2);
        ofVertex(0, -circleSize);
        ofEndShape();
        ofPopMatrix();
    }
    ofPopStyle();
}
//--------------------------------------------------------------
void DrawHarp::drawCircles() {
    // Draw Outlines;
    ofPushStyle();
    ofNoFill();
    for (int i = 0; i < yPos.size(); i++) {
        ofSetLineWidth(lineWidths[i]);
        ofSetColor(colours[i]);
        ofDrawCircle(lineLeft, yPos[i], circleSize);
        ofDrawCircle(lineRight, yPos[i], circleSize);
    }
    ofPopStyle();
    
    // Draw Circles;
    ofPushStyle();
    ofFill();
    for (int i = 0; i < yPos.size(); i++) {
        ofSetColor(colours[i], opacs[i]);
        ofDrawCircle(lineLeft, yPos[i], circleSize);
        ofDrawCircle(lineRight, yPos[i], circleSize);
    }
    ofPopStyle();
}
//--------------------------------------------------------------
void DrawHarp::drawCursor() {
    ofPushStyle();
    ofFill();
    ofSetColor(ofColor::white);
    ofDrawCircle(rightFingerPos, cursorSize);
    ofPopStyle();
}
//--------------------------------------------------------------

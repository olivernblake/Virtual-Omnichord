//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "BubbleSystem.h"

//-------------------------------------------------------
BubbleSystem::BubbleSystem()
{
    
}

//--------------------------------------------------------
void BubbleSystem::setup()  {
    // Default Wood and Sin;
    woodMode = true;
    spaceMode = false;
    sin = true;
    saw = false;
}
//--------------------------------------------------------------
void BubbleSystem::update(){
    // Update BOTH Bubbles and Beams;
    for (int i = 0; i < bubbles.size(); i++) {
            bubbles[i].update();
            if (bubbles[i].position.y + bubbles[i].size < 0) {
                bubbles.erase(bubbles.begin() + i);
            }
        }
    
    for (int i = 0; i < beams.size(); i++) {
        beams[i].update();
        if (beams[i].position.y + beams[i].size < 0) {
            beams.erase(beams.begin() + i);
        }
    }
}
//--------------------------------------------------------------
void BubbleSystem::draw(){
    // Draw BOTH Bubbles and Beams;
    for (int i = 0; i < bubbles.size(); i++) {
        bubbles[i].draw();
    }
    
    for (int i = 0; i < beams.size(); i++) {
        beams[i].draw();
    }
}
//--------------------------------------------------------------
void BubbleSystem::addBubble(glm::vec2 _pos, int _stringNum, int _trigNum, ofColor _stringCol, string _sinsaw) {
    Bubble tempBubble;
    tempBubble.setup(_pos, _stringNum, _trigNum, _stringCol, _sinsaw);
    bubbles.push_back(tempBubble);
}
//--------------------------------------------------------------
void BubbleSystem::addBeam(glm::vec2 _pos, int _stringNum, int _trigNum, ofColor _stringCol, string _sinsaw) {
    Beam tempBeam;
    tempBeam.setup(_pos, _stringNum, _trigNum, _stringCol, _sinsaw);
    beams.push_back(tempBeam);
}
//--------------------------------------------------------------

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

class BubbleSystem{

    public:
    BubbleSystem();
    
            // Functions
            void setup();
            void draw();
            void update();
            void addBubble(glm::vec2 _pos, int _stringNum, int _trigNum, ofColor _stringCol, string _sinsaw);
            void addBeam(glm::vec2 _pos, int _stringNum, int _trigNum, ofColor _stringCol, string _sinsaw);

    deque<Bubble> bubbles;
    deque<Beam> beams;
    
    // Wood/Space Modes;
    bool woodMode, spaceMode;
    bool sin, saw;
};

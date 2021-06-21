//
//  Coin.h
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#pragma once
#include "ofMain.h"

class Beam{

    public:
    Beam();
    
            // Functions
            void setup(glm::vec2 _position, int _stringNum, int _trigNum, ofColor _stringCol, string _sinsaw);
            void draw();
            void update();
            void applyForce(glm::vec2 _force);
            void loadSinSound(int stringNum, int trigNum);
            void loadSawSound(int stringNum, int trigNum);

    // Setup stuff;
    glm::vec2 position, velocity, accel;
    glm::vec2 floating;
    float beamWidth;
    float size;
    float maxLength;
    int stringNum;
    int trigNum;
    string sinsaw;
    
    // Lifespan stuff;
    int life, lifespan;
    ofColor bubbleCol;
    float opac;
    float length;
    
    // Play Sound Vars;
    ofSoundPlayer harpNote;
    float noteVol;
    
    // Sin/Saw
    bool sin, saw;
};

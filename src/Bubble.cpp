//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "Bubble.h"

//-------------------------------------------------------
Bubble::Bubble()
{
    
}

//--------------------------------------------------------
void Bubble::setup(glm::vec2 _position, int _stringNum, int _trigNum, ofColor _stringCol, string _sinsaw)  {
    // How it floats;
    floating = glm::vec2(0, -0.1);
    
    // Zero Values for Vel and Accel;
    velocity = glm::vec2(0, 0);
    accel = glm::vec2(0, 0);
    
    // Take Position from Bubble System;
    position = _position;
    stringNum = _stringNum;
    trigNum = _trigNum;
    bubbleCol = _stringCol;
    
    // Size of Beam;
    size = 10;
    lineWidth = 3;
    
    lifespan = 120;
    life = 0;
    
    // Load In Sounds;
    if (_sinsaw == "sin") {
        sin = true;
        saw = false;
        loadSinSound(stringNum, trigNum);
        noteVol = 0.15;
    }
    
    if (_sinsaw == "saw") {
        sin = false;
        saw = true;
        loadSawSound(stringNum, trigNum);
        noteVol = 0.03;
    }

}
//--------------------------------------------------------------
void Bubble::loadSinSound(int stringNum, int trigNum) {
    // Chord 1;
    if (trigNum == 1) {
        if (stringNum == 4) {
            harpNote.load("sineC3.mp3");
        } else if (stringNum == 3) {
            harpNote.load("sineD3.mp3");
        } else if (stringNum == 2) {
            harpNote.load("sineE3.mp3");
        } else if (stringNum == 1) {
            harpNote.load("sineG3.mp3");
        } else if (stringNum == 0) {
            harpNote.load("sineB3.mp3");
        }
    }
    
    // Chord 2;
    if (trigNum == 2) {
        if (stringNum == 4) {
            harpNote.load("sineD3.mp3");
        } else if (stringNum == 3) {
            harpNote.load("sineE3.mp3");
        } else if (stringNum == 2) {
            harpNote.load("sineF3.mp3");
        } else if (stringNum == 1) {
            harpNote.load("sineA3.mp3");
        } else if (stringNum == 0) {
            harpNote.load("sineC4.mp3");
        }
    }
    
    // BOX 3;
    if (trigNum == 3) {
        if (stringNum == 4) {
            harpNote.load("sineD3.mp3");
        } else if (stringNum == 3) {
            harpNote.load("sineF3.mp3");
        } else if (stringNum == 2) {
            harpNote.load("sineG3.mp3");
        } else if (stringNum == 1) {
            harpNote.load("sineA3.mp3");
        } else if (stringNum == 0) {
            harpNote.load("sineB3.mp3");
        }
    }
    
    // BOX 4;
    if (trigNum == 4) {
        if (stringNum == 4) {
            harpNote.load("sineE3.mp3");
        } else if (stringNum == 3) {
            harpNote.load("sineG3.mp3");
        } else if (stringNum == 2) {
            harpNote.load("sineA3.mp3");
        } else if (stringNum == 1) {
            harpNote.load("sineB3.mp3");
        } else if (stringNum == 0) {
            harpNote.load("sineC4.mp3");
        }
    }
}
//--------------------------------------------------------------
void Bubble::loadSawSound(int stringNum, int trigNum) {
    // Chord 1;
    if (trigNum == 1) {
        if (stringNum == 4) {
            harpNote.load("sawC3.mp3");
        } else if (stringNum == 3) {
            harpNote.load("sawD3.mp3");
        } else if (stringNum == 2) {
            harpNote.load("sawE3.mp3");
        } else if (stringNum == 1) {
            harpNote.load("sawG3.mp3");
        } else if (stringNum == 0) {
            harpNote.load("sawB3.mp3");
        }
    }
    
    // Chord 2;
    if (trigNum == 2) {
        if (stringNum == 4) {
            harpNote.load("sawD3.mp3");
        } else if (stringNum == 3) {
            harpNote.load("sawE3.mp3");
        } else if (stringNum == 2) {
            harpNote.load("sawF3.mp3");
        } else if (stringNum == 1) {
            harpNote.load("sawA3.mp3");
        } else if (stringNum == 0) {
            harpNote.load("sawC4.mp3");
        }
    }
    
    // BOX 3;
    if (trigNum == 3) {
        if (stringNum == 4) {
            harpNote.load("sawD3.mp3");
        } else if (stringNum == 3) {
            harpNote.load("sawF3.mp3");
        } else if (stringNum == 2) {
            harpNote.load("sawG3.mp3");
        } else if (stringNum == 1) {
            harpNote.load("sawA3.mp3");
        } else if (stringNum == 0) {
            harpNote.load("sawB3.mp3");
        }
    }
    
    // BOX 4;
    if (trigNum == 4) {
        if (stringNum == 4) {
            harpNote.load("sawE3.mp3");
        } else if (stringNum == 3) {
            harpNote.load("sawG3.mp3");
        } else if (stringNum == 2) {
            harpNote.load("sawA3.mp3");
        } else if (stringNum == 1) {
            harpNote.load("sawB3.mp3");
        } else if (stringNum == 0) {
            harpNote.load("sawC4.mp3");
        }
    }
}
//--------------------------------------------------------------
void Bubble::update(){
    // Apply Forces;
    applyForce(floating);
    
    // Physics Engine;
    velocity += accel;
    position += velocity;
    
    // Reset Acceleration;
    accel = glm::vec2(0, 0);
    
    // Update Opac;
    opac = ofMap(life, 0, lifespan, 180, 0, true);
    lineWidth = ofMap(life, 0, lifespan/4, 2.5, 0, true);
    size = ofMap(life, 0, lifespan, 10, 30, true);
    
    // Increment lifespan and size;
    life++;
}
//--------------------------------------------------------------
void Bubble::draw(){
    if (life == 1) {
        harpNote.setVolume(noteVol);
        harpNote.play();
    }
    
    // Draw Bubble;
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(lineWidth);
    ofSetColor(ofColor::white, opac);
    ofDrawCircle(position, size);
    ofPopStyle();
    
    // Draw Bubble;
    ofPushStyle();
    ofFill();
    ofSetColor(bubbleCol, opac);
    ofDrawCircle(position, size);
    ofPopStyle();
}
//--------------------------------------------------------------
void Bubble::applyForce(glm::vec2 _force)   {
    accel += _force;
}
//--------------------------------------------------------------

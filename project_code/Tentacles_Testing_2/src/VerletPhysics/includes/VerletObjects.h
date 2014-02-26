//
//  VerletPointMass.h
//  Tentacles_Testing_2
//
//  Created by Anthony Scavarelli on 2/26/2014.
//
//

#ifndef Tentacles_Testing_2_VerletObjects_h
#define Tentacles_Testing_2_VerletObjects_h

#include "cinder/app/AppNative.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class VerletPointMass;

class VerletLink
{
    public:
    float mRestingDistance;
    float mStiffness;
    float mTearSensitivity;
    
    VerletPointMass *p1;
    VerletPointMass *p2;
    
    // if you want this link to be invisible, set this to false
    BOOL mDrawThis;
    
    VerletLink(VerletPointMass *which1, VerletPointMass *which2, float restingDist, float stiff, float tearSensitivity, BOOL drawMe);
    ~VerletLink();
    void solve();
    void draw();
};


class VerletPointMass
{
    public:
    float lastX, lastY; // for calculating position change (velocity)
    float x,y;
    float accX, accY;
    
    float mass;
    float damping;
    
    // An ArrayList for links, so we can have as many links as we want to this PointMass
    vector<VerletLink> links;
    
    BOOL pinned;
    float pinX, pinY;
    
    VerletPointMass(float xPos, float yPos);
    ~VerletPointMass();
    
    void updatePhysics(float timeStep, float gravity);
    void updateInteractions();
    void draw();
    void solveConstraints();
    
    void attachTo(VerletPointMass *P, float restingDist, float stiff);
    void attachTo(VerletPointMass *P, float restingDist, float stiff, BOOL drawLink);
    void attachTo(VerletPointMass *P, float restingDist, float stiff, float tearSensitivity);
    void attachTo(VerletPointMass *P, float restingDist, float stiff, float tearSensitivity, BOOL drawLink);
    
    void applyForce(float fX, float fY);
    void pinTo (float pX, float pY);
};

#endif

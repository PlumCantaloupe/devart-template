//
//  VerletWorld.h
//  Tentacles_Testing_2
//
//  Created by Anthony Scavarelli on 2/26/2014.
//  Converted from Processing code found here:
//  http://gamedevelopment.tutsplus.com/tutorials/simulate-tearable-cloth-and-ragdolls-with-simple-verlet-integration--gamedev-519
//

#ifndef Tentacles_Testing_2_VerletWorld_h
#define Tentacles_Testing_2_VerletWorld_h

#include "cinder/app/AppNative.h"

//#include "VerletCircle.h"
#include "VerletObjects.h"
#include "VerletCurtain.h"

static const float mouseInfluenceScalar = 5;

using namespace ci;
using namespace ci::app;
using namespace std;

class VerletWorld
{
    public:
    // list of circle constraints
    //vector<VerletCircle> circles;
    vector<VerletPointMass *> pointMasses;
    
    VerletWorld();
    ~VerletWorld();
    
    double previousTime;
    double currentTime;
    int fixedDeltaTime;
    float fixedDeltaTimeSeconds;
    int leftOverDeltaTime;
    int constraintAccuracy;
    
    void update();
    void draw();
    void addPointMass(VerletPointMass *pointMass);
    void addCurtain(VerletCurtain *curtain);
    float distPointToSegmentSquared(float lineX1, float lineY1, float lineX2, float lineY2, float pointX, float pointY);
    
};


#endif

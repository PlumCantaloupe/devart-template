//
//  VerletCurtain.h
//  Tentacles_Testing_2
//
//  Created by Anthony Scavarelli on 2/26/2014.
//
//

#ifndef Tentacles_Testing_2_VerletCurtain_h
#define Tentacles_Testing_2_VerletCurtain_h

#include "cinder/app/AppNative.h"
#include "VerletObjects.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class VerletCurtain
{
    public:
    vector<VerletPointMass *> pointmasses;
    
    VerletCurtain();
    ~VerletCurtain();
    
    void setup( const int curtainHeight,
                const int curtainWidth,
                const int yStart,
                const float restingDistances,
                const float stiffnesses,
                const float curtainTearSensitivity );
};

#endif

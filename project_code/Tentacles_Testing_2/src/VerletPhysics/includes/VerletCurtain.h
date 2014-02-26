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
    int mCurtainHeight = 40;
    int mCurtainWidth = 60;
    int mYStart = 25; // where will the curtain start on the y axis?
    float mRestingDistances = 6;
    float mStiffnesses = 1;
    float mCurtainTearSensitivity = 0; // distance the PointMasss have to go before ripping
    
    vector<VerletPointMass> pointmasses;
    
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

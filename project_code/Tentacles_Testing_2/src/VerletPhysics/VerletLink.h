//
//  VerletLink.h
//  Tentacles_Testing_2
//
//  Created by Anthony Scavarelli on 2/26/2014.
//
//

#ifndef Tentacles_Testing_2_VerletLink_h
#define Tentacles_Testing_2_VerletLink_h

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "VerletPointMass.h"

using namespace ci;
using namespace ci::app;
using namespace std;

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
    
    VerletLink(){}
    VerletLink(VerletPointMass *which1, VerletPointMass *which2, float restingDist, float stiff, float tearSensitivity, BOOL drawMe)
    {
        p1 = which1; // when you set one object to another, it's pretty much a reference.
        p2 = which2; // Anything that'll happen to p1 or p2 in here will happen to the paticles in our ArrayList
        
        mRestingDistance = restingDist;
        mStiffness = stiff;
        mDrawThis = drawMe;
        mTearSensitivity = tearSensitivity;
    }
    
    ~VerletLink(){}
    
    // Solve the link constraint
    void solve()
    {
        // calculate the distance between the two PointMasss
        float diffX = p1->x - p2->x;
        float diffY = p1->y - p2->y;
        float d = sqrt(diffX * diffX + diffY * diffY);
        
        // find the difference, or the ratio of how far along the restingDistance the actual distance is.
        float difference = (mRestingDistance - d) / d;
        
        // if the distance is more than curtainTearSensitivity, the cloth tears
        if (d > mTearSensitivity) {
            p1->removeLink(this);
        }
        
        // Inverse the mass quantities
        float im1 = 1 / p1->mass;
        float im2 = 1 / p2->mass;
        float scalarP1 = (im1 / (im1 + im2)) * mStiffness;
        float scalarP2 = mStiffness - scalarP1;
        
        // Push/pull based on mass
        // heavier objects will be pushed/pulled less than attached light objects
        p1->x += diffX * scalarP1 * difference;
        p1->y += diffY * scalarP1 * difference;
        
        p2->x -= diffX * scalarP2 * difference;
        p2->y -= diffY * scalarP2 * difference;
    }
    
    // Draw if it's visible
    void draw()
    {
        if (mDrawThis)
        {
            gl::drawLine(p1->x, p1->y, p2->x, p2->y);
        }
    }
};

#endif

//
//  VerletPointMass.h
//  Tentacles_Testing_2
//
//  Created by Anthony Scavarelli on 2/26/2014.
//
//

#ifndef Tentacles_Testing_2_VerletPointMass_h
#define Tentacles_Testing_2_VerletPointMass_h

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
    
    float mass = 1;
    float damping = 20;
    
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

// PointMass constructor
VerletPointMass::VerletPointMass(float xPos, float yPos)
{
    pinned = false;
    
    x = xPos;
    y = yPos;
    
    lastX = x;
    lastY = y;
    
    accX = 0;
    accY = 0;
}

VerletPointMass::~VerletPointMass()
{}

// The update function is used to update the physics of the PointMass.
// motion is applied, and links are drawn here
void VerletPointMass::updatePhysics(float timeStep, float gravity) // timeStep should be in elapsed seconds (deltaTime)
{
    applyForce(0, mass * gravity);
    
    float velX = x - lastX;
    float velY = y - lastY;
    
    // dampen velocity
    velX *= 0.99;
    velY *= 0.99;
    
    float timeStepSq = timeStep * timeStep;
    
    // calculate the next position using Verlet Integration
    float nextX = x + velX + 0.5 * accX * timeStepSq;
    float nextY = y + velY + 0.5 * accY * timeStepSq;
    
    // reset variables
    lastX = x;
    lastY = y;
    
    x = nextX;
    y = nextY;
    
    accX = 0;
    accY = 0;
}

void VerletPointMass::updateInteractions()
{
//        // this is where our interaction comes in.
//        if (mousePressed) {
//            float distanceSquared = distPointToSegmentSquared(pmouseX,pmouseY,mouseX,mouseY,x,y);
//            if (mouseButton == LEFT) {
//                if (distanceSquared < mouseInfluenceSize) { // remember mouseInfluenceSize was squared in setup()
//                    // To change the velocity of our PointMass, we subtract that change from the lastPosition.
//                    // When the physics gets integrated (see updatePhysics()), the change is calculated
//                    // Here, the velocity is set equal to the cursor's velocity
//                    lastX = x - (mouseX-pmouseX)*mouseInfluenceScalar;
//                    lastY = y - (mouseY-pmouseY)*mouseInfluenceScalar;
//                }
//            }
//            else { // if the right mouse button is clicking, we tear the cloth by removing links
//                if (distanceSquared < mouseTearSize)
//                    links.clear();
//            }
//        }
}

void VerletPointMass::draw()
{
    // draw the links and points
    glLineWidth(1.0f);
    if (links.size() > 0) {
        for (int i = 0; i < links.size(); i++) {
            links.at(i).draw();
        }
    }
    else {
        gl::drawSolidCircle(Vec2f(x,y), 3.0f);
    }
}

/* Constraints */
void VerletPointMass::solveConstraints()
{
    /* Link Constraints */
    // Links make sure PointMass connected to this one is at a set distance away
    for (int i = 0; i < links.size(); i++) {
        links.at(i).solve();
    }
    
    /* Boundary Constraints */
    // These if statements keep the PointMass within the screen
//        if (y < 1)
//            y = 2 * (1) - y;
//        if (y > height-1)
//            y = 2 * (height - 1) - y;
//        
//        if (x > width-1)
//            x = 2 * (width - 1) - x;
//        if (x < 1)
//            x = 2 * (1) - x;
    
    /* Other Constraints */
    // make sure the PointMass stays in its place if it's pinned
    if (pinned) {
        x = pinX;
        y = pinY;
    }
}

// attachTo can be used to create links between this PointMass and other PointMasss
void VerletPointMass::attachTo(VerletPointMass *P, float restingDist, float stiff)
{
    attachTo(P, restingDist, stiff, 30, true);
}

void VerletPointMass::attachTo(VerletPointMass *P, float restingDist, float stiff, BOOL drawLink)
{
    attachTo(P, restingDist, stiff, 30, drawLink);
}

void VerletPointMass::attachTo(VerletPointMass *P, float restingDist, float stiff, float tearSensitivity)
{
    attachTo(P, restingDist, stiff, tearSensitivity, true);
}

void VerletPointMass::attachTo(VerletPointMass *P, float restingDist, float stiff, float tearSensitivity, BOOL drawLink)
{
    VerletLink link(this, P, restingDist, stiff, tearSensitivity, drawLink);
    links.push_back(link);
}

//    void removeLink (VerletLink lnk)
//    {
//        links.remove(lnk);
//    }  

void VerletPointMass::applyForce(float fX, float fY)
{
    // acceleration = (1/mass) * force
    // or
    // acceleration = force / mass
    accX += fX/mass;
    accY += fY/mass;
}

void VerletPointMass::pinTo (float pX, float pY)
{
    pinned = true;
    pinX = pX;
    pinY = pY;
}


VerletLink::VerletLink(VerletPointMass *which1, VerletPointMass *which2, float restingDist, float stiff, float tearSensitivity, BOOL drawMe)
{
    p1 = which1; // when you set one object to another, it's pretty much a reference.
    p2 = which2; // Anything that'll happen to p1 or p2 in here will happen to the paticles in our ArrayList
    
    mRestingDistance = restingDist;
    mStiffness = stiff;
    mDrawThis = drawMe;
    mTearSensitivity = tearSensitivity;
}

VerletLink::~VerletLink(){}

// Solve the link constraint
void VerletLink::solve()
{
    // calculate the distance between the two PointMasss
    float diffX = p1->x - p2->x;
    float diffY = p1->y - p2->y;
    float d = sqrt(diffX * diffX + diffY * diffY);
    
    // find the difference, or the ratio of how far along the restingDistance the actual distance is.
    float difference = (mRestingDistance - d) / d;
    
    // if the distance is more than curtainTearSensitivity, the cloth tears
    //        if (d > mTearSensitivity) {
    //            p1->removeLink(this);
    //        }
    
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
void VerletLink::draw()
{
    if (mDrawThis)
    {
        gl::drawLine(Vec2f(p1->x, p1->y), Vec2f(p2->x, p2->y));
    }
}

#endif

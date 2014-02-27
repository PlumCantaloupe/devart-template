#include "VerletWorld.h"

VerletWorld::VerletWorld()
{
    fixedDeltaTime = 16;
    fixedDeltaTimeSeconds = (float)fixedDeltaTime / 1000.0;
    leftOverDeltaTime = 0;
    constraintAccuracy = 3;
}

VerletWorld::~VerletWorld()
{}

// Update physics
void VerletWorld::update(double timeStep, BOOL hasMouseInteraction, Vec2i mousePos, Vec2i prevMousePos)
{
//    // calculate elapsed time
//    currentTime = getElapsedSeconds() * 100;
//    long deltaTimeMS = currentTime - previousTime;
//    previousTime = currentTime; // reset previous time
    
    long deltaTimeMS = (int)(timeStep * 1000.0f);
    
    // break up the elapsed time into manageable chunks
    int timeStepAmt = (int)((float)(deltaTimeMS + leftOverDeltaTime) / (float)fixedDeltaTime);
    
    // limit the timeStepAmt to prevent potential freezing
    timeStepAmt = min(timeStepAmt, 5);
    
    // store however much time is leftover for the next frame
    leftOverDeltaTime = (int)deltaTimeMS - (timeStepAmt * fixedDeltaTime);
    //leftOverDeltaTime = max(leftOverDeltaTime, 0);
    
    // How much to push PointMasses when the user is interacting
    //        mouseInfluenceScalar = 1.0 / timeStepAmt;
    
    //console() << deltaTimeMS << " " << leftOverDeltaTime << " " << fixedDeltaTime << " " << deltaTimeMS << " " << timeStepAmt << "\n";
    
    // update physics
    for (int iteration = 1; iteration <= timeStepAmt; iteration++) {
        //console() << "???\n";
        
        // solve the constraints multiple times for greater accuracy
        for (int x = 0; x < constraintAccuracy; x++) {
            for ( vector<VerletPointMass*>::iterator pmIter = pointMasses.begin(); pmIter != pointMasses.end(); pmIter++ ) {
                (*pmIter)->solveConstraints();
            }
        }
        
        // update each PointMass's position
        for (int i = 0; i < pointMasses.size(); i++) {
            if ( hasMouseInteraction ) {
                pointMasses.at(i)->updateInteractions(mousePos, prevMousePos);
            }
            pointMasses.at(i)->updatePhysics(fixedDeltaTimeSeconds, 980.0f);
        }
    }
 
    for ( vector<VerletPointMass*>::iterator pmIter = pointMasses.begin(); pmIter != pointMasses.end(); pmIter++ ) {
        (*pmIter)->updatePhysics(fixedDeltaTimeSeconds, 980.0f);
    }
}

void VerletWorld::draw()
{
    for (vector<VerletPointMass *>::iterator pmIter = pointMasses.begin(); pmIter != pointMasses.end(); pmIter++) {
        (*pmIter)->draw();
    }
}

void VerletWorld::addPointMass(VerletPointMass *pointMass)
{
    pointMasses.push_back(pointMass);
}

void VerletWorld::addCurtain(VerletCurtain *curtain)
{
    for (vector<VerletPointMass*>::iterator pmIter = curtain->pointmasses.begin(); pmIter != curtain->pointmasses.end(); pmIter++) {
        pointMasses.push_back( *pmIter );
    }
}

//    void addCircle (VerletCircle c) {
//        circles.push_back(c);
//    }
//
//    void removeCircle (VerletCircle c) {
//        circles.push_back(c);
//    }
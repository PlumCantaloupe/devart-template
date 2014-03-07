#include "VerletWorld.h"

VerletWorld::VerletWorld()
{
    fixedDeltaTime = 16;
    fixedDeltaTimeSeconds = (float)fixedDeltaTime / 1000.0;
    leftOverDeltaTime = 0;
    constraintAccuracy = 3;
}

VerletWorld::~VerletWorld()
{
    for ( vector<VerletPointMass*>::iterator pmIter = pointMasses.begin(); pmIter != pointMasses.end(); pmIter++ ) {
        delete (*pmIter);
    }
}

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

//void VerletWorld::addCurtain(VerletCurtain *curtain)
//{
//    for (vector<VerletPointMass*>::iterator pmIter = curtain->pointmasses.begin(); pmIter != curtain->pointmasses.end(); pmIter++) {
//        pointMasses.push_back( *pmIter );
//    }
//}

void VerletWorld::addCurtain(   const int curtainHeight,
                                const int curtainWidth,
                                const int yStart,
                                const float restingDistances,
                                const float stiffnesses,
                                const float curtainTearSensitivity )
{
    // midWidth: amount to translate the curtain along x-axis for it to be centered
    // (curtainWidth * restingDistances) = curtain's pixel width
    int midWidth = (int) (getWindowWidth()/2 - (curtainWidth * (int)restingDistances)/2);
    //console() << midWidth << "\n";
    // Since this our fabric is basically a grid of points, we have two loops
    for (int y = 0; y <= curtainHeight; y++) { // due to the way PointMasss are attached, we need the y loop on the outside
        for (int x = 0; x <= curtainWidth; x++) {
            //pointmassData.push_back( new VerletPointMass(midWidth + x * restingDistances, y * restingDistances + yStart) );
            VerletPointMass *pointmass = new VerletPointMass(midWidth + x * restingDistances, y * restingDistances + yStart); //pointmassData.at(pointmassData.size()-1);
            
            // attach to
            // x - 1  and
            // y - 1
            //  *<---*<---*<-..
            //  ^    ^    ^
            //  |    |    |
            //  *<---*<---*<-..
            //
            // PointMass attachTo parameters: PointMass PointMass, float restingDistance, float stiffness
            // try disabling the next 2 lines (the if statement and attachTo part) to create a hairy effect
            if (x != 0) {
                pointmass->attachTo(pointMasses.at(pointMasses.size()-1), restingDistances, stiffnesses);
            }
            
            // the index for the PointMasss are one dimensions,
            // so we convert x,y coordinates to 1 dimension using the formula y*width+x
            if (y != 0) {
                pointmass->attachTo(pointMasses.at((y - 1) * (curtainWidth+1) + x), restingDistances, stiffnesses);
            }
            
            // we pin the very top PointMasss to where they are
            if (y == 0) {
                pointmass->pinTo(pointmass->x, pointmass->y);
            }
            
            pointMasses.push_back(pointmass);
        }
    }
}

//    void addCircle (VerletCircle c) {
//        circles.push_back(c);
//    }
//
//    void removeCircle (VerletCircle c) {
//        circles.push_back(c);
//    }
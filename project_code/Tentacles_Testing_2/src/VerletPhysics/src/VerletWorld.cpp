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
void VerletWorld::update()
{
    // calculate elapsed time
    currentTime = getElapsedSeconds();
    double deltaTimeMS = currentTime - previousTime;
    previousTime = currentTime; // reset previous time
    
    // break up the elapsed time into manageable chunks
    int timeStepAmt = (int)((float)(deltaTimeMS + leftOverDeltaTime) / (float)fixedDeltaTime);
    
    // limit the timeStepAmt to prevent potential freezing
    timeStepAmt = min(timeStepAmt, 5);
    
    // store however much time is leftover for the next frame
    leftOverDeltaTime = (int)deltaTimeMS - (timeStepAmt * fixedDeltaTime);
    
    // How much to push PointMasses when the user is interacting
    //        mouseInfluenceScalar = 1.0 / timeStepAmt;
    
    // update physics
    for (int iteration = 1; iteration <= timeStepAmt; iteration++) {
        // solve the constraints multiple times
        // the more it's solved, the more accurate.
        for (int x = 0; x < constraintAccuracy; x++) {
            for (int i = 0; i < pointMasses.size(); i++) {
                pointMasses.at(i)->solveConstraints();
            }
            //                for (int i = 0; i < circles.size(); i++) {
            //                    Circle c = (Circle) circles.get(i);
            //                    c.solveConstraints();
            //                }
        }
        
        // update each PointMass's position
        for (int i = 0; i < pointMasses.size(); i++) {
            pointMasses.at(i)->updateInteractions();
            pointMasses.at(i)->updatePhysics(fixedDeltaTimeSeconds, 980.0f);
        }
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
    for (vector<VerletPointMass>::iterator pmIter = curtain->pointmasses.begin(); pmIter != curtain->pointmasses.end(); pmIter++) {
        pointMasses.push_back( &(*pmIter) );
    }
}

//    void addCircle (VerletCircle c) {
//        circles.push_back(c);
//    }
//
//    void removeCircle (VerletCircle c) {
//        circles.push_back(c);
//    }

// Using http://www.codeguru.com/forum/showpost.php?p=1913101&postcount=16
// We use this to have consistent interaction
// so if the cursor is moving fast, it won't interact only in spots where the applet registers it at
float VerletWorld::distPointToSegmentSquared(float lineX1, float lineY1, float lineX2, float lineY2, float pointX, float pointY)
{
    float vx = lineX1 - pointX;
    float vy = lineY1 - pointY;
    float ux = lineX2 - lineX1;
    float uy = lineY2 - lineY1;
    
    float len = ux*ux + uy*uy;
    float det = (-vx * ux) + (-vy * uy);
    if ((det < 0) || (det > len)) {
        ux = lineX2 - pointX;
        uy = lineY2 - pointY;
        return min(vx*vx+vy*vy, ux*ux+uy*uy);
    }
    
    det = ux*vy - uy*vx;
    return (det*det) / len;
}
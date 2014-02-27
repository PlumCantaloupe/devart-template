//
//  VerletPointMass.h
//  Tentacles_Testing_2
//
//  Created by Anthony Scavarelli on 2/26/2014.
//
//

#include "VerletObjects.h"

VerletPointMass::VerletPointMass()
{}

VerletPointMass::VerletPointMass(float xPos, float yPos)
{
    x = xPos;
    y = yPos;
    
    lastX = x;
    lastY = y;
    
    accX = 0;
    accY = 0;
    
    mass= 1;
    damping = 20;
    
    // we square the mouseInfluenceSize and mouseTearSize so we don't have to use squareRoot when comparing distances with this.
    mouseInfluenceSize = 20;
    mouseInfluenceScalar = 5;
    mouseInfluenceSize *= mouseInfluenceSize;
    
    //console() << xPos << " " << yPos << "\n";
}

VerletPointMass::~VerletPointMass()
{
    //!!delete
    for ( vector<VerletLink*>::iterator linkIter = links.begin(); linkIter != links.end(); linkIter++ ) {
        delete (*linkIter);
    }
}

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
    
    mouseInfluenceScalar = 1.0/timeStep; //?? How much to push PointMasses when the user is interacting
    
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

void VerletPointMass::updateInteractions(Vec2f mousePos, Vec2f prevMousePos)
{
    //console() << "hello";
    
    // this is where our interaction comes in.
    float distanceSquared = distPointToSegmentSquared( prevMousePos.x, prevMousePos.y ,mousePos.x, mousePos.y ,x ,y );
    if (distanceSquared < mouseInfluenceSize) { // remember mouseInfluenceSize was squared in setup()
        //console() << "hi";
        
        // To change the velocity of our PointMass, we subtract that change from the lastPosition.
        // When the physics gets integrated (see updatePhysics()), the change is calculated
        // Here, the velocity is set equal to the cursor's velocity
        lastX = x - (mousePos.x - prevMousePos.x) * mouseInfluenceScalar;
        lastY = y - (mousePos.y - prevMousePos.y) * mouseInfluenceScalar;
    }
}

void VerletPointMass::draw()
{
    // draw the links and points
    glLineWidth(1.0f);
    if (links.size() > 0) {
        for ( vector<VerletLink*>::iterator linkIter = links.begin(); linkIter != links.end(); linkIter++ ) {
            (*linkIter)->draw();
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
    for ( vector<VerletLink*>::iterator linkIter = links.begin(); linkIter != links.end(); linkIter++ ) {
        (*linkIter)->solve();
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
    links.push_back( new VerletLink(this, P, restingDist, stiff, tearSensitivity, drawLink) );
    
    //console() << "--\n";
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

// Using http://www.codeguru.com/forum/showpost.php?p=1913101&postcount=16
// We use this to have consistent interaction
// so if the cursor is moving fast, it won't interact only in spots where the applet registers it at
float VerletPointMass::distPointToSegmentSquared(float lineX1, float lineY1, float lineX2, float lineY2, float pointX, float pointY)
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

/*******/

VerletLink::VerletLink(VerletPointMass *which1, VerletPointMass *which2, float restingDist, float stiff, float tearSensitivity, BOOL drawMe)
{
    p1 = which1;
    p2 = which2;
    
    //console() << p1->x << " " << p1->y << " " << p2->x << " " << p2->y << "\n";
    
    mRestingDistance = restingDist;
    mStiffness = stiff;
    mDrawThis = drawMe;
    mTearSensitivity = tearSensitivity;
}

VerletLink::~VerletLink(){}

// Solve the link constraint
void VerletLink::solve()
{
    //console() << p1->x << " " << p2->x << "\n";
    
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
    
//    console() << diffX << " " << diffY << " " << scalarP1 << " " << scalarP2 << " " << difference << "\n";
    
//    console() << "position:" << p1->x << "  " << p1->y << "\n";
//    console() << "diff:" << diffX << "  " << diffY << "\n";
//    console() << "scalar:" << scalarP1 << "  " << scalarP2 << "\n";
}

// Draw if it's visible
void VerletLink::draw()
{
//    console() << "-----------\n";
    
    if (mDrawThis)
    {
  //      console() << Vec2f(p1->x, p1->y) << " " << Vec2f(p2->x, p2->y) << "\n";
        gl::drawLine(Vec2f(p1->x, p1->y), Vec2f(p2->x, p2->y));
    }
}

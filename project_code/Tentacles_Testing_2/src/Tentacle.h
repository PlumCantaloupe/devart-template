//
//  Tentacle.h
//  Tentacles_Testing_2
//
//  Created by Anthony Scavarelli on 2/25/2014.
//
//

#ifndef __Tentacles_Testing_2__Tentacle__
#define __Tentacles_Testing_2__Tentacle__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "VectorField.h"
#include "Utility_3D.h"

using namespace ci;
using namespace ci::app;
using namespace std;

struct TentacleSkeletonPoint
{
    TentacleSkeletonPoint(){}
    ~TentacleSkeletonPoint(){}
    
    ci::Vec3f positionPrev;
    ci::Vec3f positionCurr;
    ci::Vec3f velocity;
};

class Tentacle
{
    public:
    std::vector<TentacleSkeletonPoint> mSkeletonPoints; //index 0 will be root point
    float mMaxBoneLengthSquared;
    
    Tentacle();
    ~Tentacle();
    
    void setup(const int numSegments, const float maxBoneLength, const Vec3f rootPoint);
    void update(const VectorField *vfRef, const Utility_3D *utility3D);
    void draw();
};

#endif /* defined(__Tentacles_Testing_2__Tentacle__) */

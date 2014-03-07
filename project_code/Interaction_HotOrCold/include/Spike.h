//
//  Spike.h
//  Game_HotOrCold
//
//  Created by Anthony Scavarelli on 2/27/2014.
//
//

#ifndef __Game_HotOrCold__Spike__
#define __Game_HotOrCold__Spike__

#include "cinder/app/AppNative.h"
#include "cinder/CinderMath.h"
#include "cinder/Timeline.h"
#include "cinder/Rand.h"
#include "BasicModel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//functor for anim
struct SetAnimationComplete {
	SetAnimationComplete( BOOL *isComplete )
    : mComplete( isComplete )
	{}
	
	void operator()() {
		*mComplete = true;
	}
	
	BOOL *mComplete;
};

class Spike : public BasicModel
{
    public:
    Vec3f           mInitPos;
    Vec3f           mTargetPos;
    Quatf           m3DRot;
    Anim<Vec3f>     mAnimPos;
    float           mScale;
    
    BOOL            mAnimComplete;
    BOOL            mExtracting;
    
    //init vars
    Vec3f mConvertedTopLeftCorner;
    Vec3f mConvertedBottomRightCorner;
    float mIgnoreRadiusInit;
    float mIgnoreRadiusTarget;
    
    Spike();
    ~Spike();
    
    void setup(ResourceManager *resourceManager, const int modelType, Vec3f convertedTopLeftCorner, Vec3f convertedBottomRightCorner, float ignoreRadiusInit, float ignoreRadiusTarget);
    void update();
    void draw() const;
    
    void extract();
    void retract();
    void randomizeInit();
};

#endif /* defined(__Game_HotOrCold__Spike__) */

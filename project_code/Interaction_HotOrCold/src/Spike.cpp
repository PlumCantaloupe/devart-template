//
//  Spike.cpp
//  Game_HotOrCold
//
//  Created by Anthony Scavarelli on 2/27/2014.
//
//

#include "Spike.h"

Spike::Spike()
{}

Spike::~Spike()
{}

void Spike::setup(ResourceManager *resourceManager, const int modelType, Vec3f convertedTopLeftCorner, Vec3f convertedBottomRightCorner, float ignoreRadiusInit, float ignoreRadiusTarget)
{
    mResourceManager = resourceManager;
    mModel = mResourceManager->getModelRef(modelType);
    mConvertedTopLeftCorner = convertedTopLeftCorner;
    mConvertedBottomRightCorner = convertedBottomRightCorner;
    mIgnoreRadiusInit = ignoreRadiusInit;
    mIgnoreRadiusTarget = ignoreRadiusTarget;
    mAnimComplete = false;
    mExtracting = false;
    
    randomizeInit();
}

void Spike::update()
{}

void Spike::draw() const
{
    gl::color(1.0f, 1.0f, 1.0f);
    gl::pushMatrices();
    gl::translate( mAnimPos );
    gl::rotate( m3DRot );
    gl::scale( Vec3f(mScale, mScale, mScale) );
    gl::draw( *mModel );
    gl::popMatrices();
}

void Spike::extract()
{
    if(!mExtracting) {
        
        if(mAnimComplete) {
            randomizeInit();
        }
    
        mExtracting = true;
        mAnimComplete = false;
        timeline().apply( &mAnimPos, mTargetPos, Rand::randFloat(4.0f, 20.0f), EaseInCubic() )
            .finishFn( SetAnimationComplete( &mAnimComplete ) );
    }
}

void Spike::retract()
{
    if (mExtracting) {
        mExtracting = false;
        mAnimComplete = false;
        timeline().apply( &mAnimPos, mInitPos, Rand::randFloat(4.0f, 10.0f), EaseInCubic() )
            .finishFn( SetAnimationComplete( &mAnimComplete ) );
    }
}

void Spike::randomizeInit()
{
    //want to make sure that spike does not penetrate sphere by ignoring certain starting and ending positions
    mInitPos = Vec3f::zero();
    while( (mInitPos.x < mIgnoreRadiusInit) && (mInitPos.x > -mIgnoreRadiusInit) && (mInitPos.y < mIgnoreRadiusInit) && (mInitPos.y > -mIgnoreRadiusInit) ) {
        mInitPos = Vec3f( Rand::randFloat(mConvertedTopLeftCorner.x, mConvertedBottomRightCorner.x), Rand::randFloat(mConvertedTopLeftCorner.y, mConvertedBottomRightCorner.y), -10.0f );
    }
    
    mTargetPos = Vec3f::zero();
    while( (mTargetPos.x < mIgnoreRadiusTarget) && (mTargetPos.x > -mIgnoreRadiusTarget) && (mTargetPos.y < mIgnoreRadiusTarget) && (mTargetPos.y > -mIgnoreRadiusTarget) ) {
        mTargetPos = Vec3f( Rand::randFloat(mConvertedTopLeftCorner.x, mConvertedBottomRightCorner.x), Rand::randFloat(mConvertedTopLeftCorner.y, mConvertedBottomRightCorner.y), -2.0f );
    }
    
    mScale = Rand::randFloat(0.6f, 0.8f);
    mAnimPos = mInitPos;
    mDirVec = mTargetPos - mInitPos;
    mDirVec.normalize();
    m3DRot = Quatf(Vec3f(0.0f, 0.0f, 1.0f), mDirVec);
}

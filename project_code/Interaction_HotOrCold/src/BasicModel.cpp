//
//  BasicModel.cpp
//  Game_HotOrCold
//
//  Created by Anthony Scavarelli on 2/23/2014.
//
//

#include "BasicModel.h"

BasicModel::BasicModel()
{}

BasicModel::~BasicModel()
{}

void BasicModel::setup(ResourceManager *resourceManager, int modelType, ci::Vec3f initPos)
{
    mResourceManager = resourceManager;
    mPos = initPos;
    mRot = 0.0f;
    mDirVec = Vec3f(1.0f, 0.0f, 0.0f);
    mModel = mResourceManager->getModelRef(modelType);
}

void BasicModel::setPosition(Vec3f newPos)
{
    mPos = newPos;
}

const Vec3f& BasicModel::getPosition()
{
    return mPos;
}

const Vec3f& BasicModel::getDirection()
{
    return mDirVec;
}

void BasicModel::update()
{}

void BasicModel::faceTowards(Vec3f target)
{
    mDirVec = target - mPos;
    mDirVec.normalize();
    mDirVec.z = 0.0f;
    mRot = math<float>::atan2( mDirVec.y, mDirVec.x ) * (180.0f/M_PI);
}

void BasicModel::draw() const
{
    gl::color(1.0f, 1.0f, 1.0f);
    gl::pushMatrices();
    gl::translate(mPos);
    gl::rotate( Vec3f(0.0f, 0.0f, mRot) );
    gl::draw(*mModel);
    gl::popMatrices();
}
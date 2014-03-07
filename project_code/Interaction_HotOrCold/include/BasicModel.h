//
//  BasicModel.h
//  Game_HotOrCold
//
//  Created by Anthony Scavarelli on 2/23/2014.
//
//

#ifndef __Game_HotOrCold__BasicModel__
#define __Game_HotOrCold__BasicModel__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Vbo.h"
#include "cinder/CinderMath.h"

#include "Constants.h"
#include "ResourceManager.h"

class BasicModel
{
public:
    BasicModel();
    ~BasicModel();
    
    void setup(ResourceManager *resourceManager, const int modelType, const ci::Vec3f initPos = Vec3f::zero());
    void update();
    void draw() const;
    void faceTowards(const Vec3f target);
    void setPosition(const Vec3f newPos);
    const Vec3f& getPosition();
    const Vec3f& getDirection();
    
protected:
    float               mRot;
    Vec3f               mDirVec;
    ci::Vec3f           mPos;
    gl::VboMesh*        mModel;
    ResourceManager*    mResourceManager;
};

#endif /* defined(__Game_HotOrCold__BasicModel__) */

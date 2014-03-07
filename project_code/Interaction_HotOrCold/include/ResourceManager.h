//
//  ResourceManager.h
//  Game_BadDreams
//
//  Created by Anthony Scavarelli on 2/21/2014.
//
//

#ifndef __Game_BadDreams__ResourceManager__
#define __Game_BadDreams__ResourceManager__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/ObjLoader.h"
#include "cinder/TriMesh.h"
#include "cinder/gl/Vbo.h"

#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ResourceManager
{
    public:
    
    enum {
        MODEL_PLAYER_SHIP,
        MODEL_CENTRAL_SPHERE,
        MODEL_GROUND_PLANE,
        MODEL_PROJECTILE,
        MODEL_SPIKE_1,
        MODEL_SPIKE_2,
        MODEL_SPIKE_3,
        NUM_MODELS
    };
    
    private:
    BOOL    mAssetsLoaded;
    
    //models
    gl::VboMesh mPlayerShipVbo;
    gl::VboMesh mCentralSphereVbo;
    gl::VboMesh mGroundPlane;
    gl::VboMesh mProjectile;
    gl::VboMesh mSpike1;
    gl::VboMesh mSpike2;
    gl::VboMesh mSpike3;
    
    public:
    ResourceManager(){ mAssetsLoaded = false; }
    ~ResourceManager(){}
    
    void setup()
    {
        if (!mAssetsLoaded) {
            //loading code here
            
            TriMesh tempTrimesh;
            ObjLoader loader( (DataSourceRef)loadResource( RES_MODEL_PLAYER_SHIP ) );
            loader.load( &tempTrimesh );
            mPlayerShipVbo = gl::VboMesh( tempTrimesh );
            
            ObjLoader loader2( (DataSourceRef)loadResource( RES_MODEL_CENTRAL_SPHERE ) );
            loader2.load( &tempTrimesh );
            mCentralSphereVbo = gl::VboMesh( tempTrimesh );
            
            ObjLoader loader3( (DataSourceRef)loadResource( RES_MODEL_GROUND_PLANE ) );
            loader3.load( &tempTrimesh );
            mGroundPlane = gl::VboMesh( tempTrimesh );
            
            ObjLoader loader4( (DataSourceRef)loadResource( RES_MODEL_PROJECTILE ) );
            loader4.load( &tempTrimesh );
            mProjectile = gl::VboMesh( tempTrimesh );
            
            ObjLoader loader5( (DataSourceRef)loadResource( RES_MODEL_SPIKE_1 ) );
            loader5.load( &tempTrimesh );
            mSpike1 = gl::VboMesh( tempTrimesh );
            
            ObjLoader loader6( (DataSourceRef)loadResource( RES_MODEL_SPIKE_2 ) );
            loader6.load( &tempTrimesh );
            mSpike2 = gl::VboMesh( tempTrimesh );
            
            ObjLoader loader7( (DataSourceRef)loadResource( RES_MODEL_SPIKE_3 ) );
            loader7.load( &tempTrimesh );
            mSpike3 = gl::VboMesh( tempTrimesh );
            
            mAssetsLoaded = true;
        }
        else {
            console() << "Warning: Assets already loaded \n";
        }
    }
    
    //get references
    gl::VboMesh* getModelRef(int modelType)
    {
        gl::VboMesh* modelRef;
        
        switch(modelType) {
            case MODEL_PLAYER_SHIP:
            {
                modelRef = &mPlayerShipVbo;
            }
                break;
            case MODEL_CENTRAL_SPHERE:
            {
                modelRef = &mCentralSphereVbo;
            }
                break;
            case MODEL_GROUND_PLANE:
            {
                modelRef = &mGroundPlane;
            }
                break;
            case MODEL_PROJECTILE:
            {
                modelRef = &mProjectile;
            }
                break;
            case MODEL_SPIKE_1:
            {
                modelRef = &mSpike1;
            }
                break;
            case MODEL_SPIKE_2:
            {
                modelRef = &mSpike2;
            }
                break;
            case MODEL_SPIKE_3:
            {
                modelRef = &mSpike3;
            }
                break;
            default:
                break;
        }
        
        return modelRef;
    }
};

#endif /* defined(__Game_BadDreams__ResourceManager__) */

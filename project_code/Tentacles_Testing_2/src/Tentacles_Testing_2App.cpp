#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"

#include "vectorField.h"
#include "Tentacle.h"
#include "Utility_3D.h"

#include "VerletWorld.h"
#include "VerletCurtain.h"

using namespace ci;
using namespace ci::app;
using namespace std;

static const Vec2i APP_RES = Vec2i(640, 480);

class Tentacles_Testing_2App : public AppNative {
  public:
//    VectorField     mVectorField;
//    Tentacle        mTestTentacle;
//    Utility_3D      mUtility3D;
//    CameraPersp     mCam;
    VerletWorld     mVerletWorld;
    VerletCurtain   mVerletCurtain;
    
    void prepareSettings(Settings *settings);
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void Tentacles_Testing_2App::prepareSettings(Settings *settings)
{
    settings->setWindowSize(APP_RES);
    settings->setFrameRate(30.0f);
}

void Tentacles_Testing_2App::setup()
{
    //set up physics
    mVerletCurtain.setup(40, 60, 25, 6, 1, 500);
    mVerletWorld.addCurtain(&mVerletCurtain);
    
    //set up vector field
//    mVectorField.setupField(32, 16, APP_RES.x, APP_RES.y);
//    mVectorField.addOutwardCircle((float)APP_RES.x/2.0f, (float)APP_RES.y/2.0f, (float)APP_RES.x/2.0f + 100.0f, 20.0f);
    
//    //set up camera
//	mCam.setPerspective( 45.0f, getWindowAspectRatio(), 0.1f, 10000.0f );
//    mCam.lookAt(Vec3f( 0.0f, 0.0f, 7.5f ), Vec3f::zero(), Vec3f(0.0f, 0.0f, 1.0f) );
//    mCam.setCenterOfInterestPoint(Vec3f::zero());
    
    //set up 3D utility
//    mUtility3D.setModelView(mCam.getModelViewMatrix());
//    mUtility3D.setProjection(mCam.getProjectionMatrix());
//    mUtility3D.setViewport(gl::getViewport());
//    mUtility3D.setWindowSize(Rectf(0.0f, 0.0f, (float)getWindowWidth(), (float)getWindowHeight()));
    
    //set up test tentacle
//    mTestTentacle.setup(5, 5.0f, Vec3f::zero());
}

void Tentacles_Testing_2App::mouseDown( MouseEvent event )
{}

void Tentacles_Testing_2App::update()
{
    mVerletWorld.update(); //update physics
//    mTestTentacle.update(&mVectorField, &mUtility3D); //update tentacles
}

void Tentacles_Testing_2App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
//    gl::setMatricesWindow(getWindowSize());
//    mVectorField.draw();
    
//    gl::setMatrices(mCam);
//    mTestTentacle.draw();
    
    mVerletWorld.draw();
}

CINDER_APP_NATIVE( Tentacles_Testing_2App, RendererGl )

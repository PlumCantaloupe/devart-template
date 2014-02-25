#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/MayaCamUI.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

#include "Tube.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Tentacles_TestingApp : public AppNative {
  public:
    Tube					mTube;
	std::vector<Vec3f>		mBasePoints;
	std::vector<Vec3f>		mCurPoints;
	BSpline3f				mBSpline;
	TriMesh					mTubeMesh;
	
	MayaCamUI				mMayaCam;
	
	bool					mDrawCurve;
	bool					mDrawFrames;
	bool					mDrawMesh;
	bool					mDrawSlices;
	bool					mWireframe;
	bool					mAnimate;
	int32_t					mNumSegs;
    float                   mAvgFramerate;
    
    params::InterfaceGlRef	mParams;
    
    void prepareSettings(Settings *settings);
	void setup();
	void mouseDown( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void update();
	void draw();
    
    void updateTubeMesh();
};

void Tentacles_TestingApp::prepareSettings(Settings *settings)
{
    settings->setWindowSize( 800, 850 );
    settings->setFrameRate(60.0f);
}

void Tentacles_TestingApp::setup()
{
    //setup camera
    //set up camera
    CameraPersp initCam;
	initCam.setPerspective( 45.0f, getWindowAspectRatio(), 0.1f, 10000.0f );
    initCam.lookAt(Vec3f( 0.0f, 0.0f, 7.5f ), Vec3f::zero(), Vec3f(0.0f, 0.0f, 1.0f) );
    initCam.setCenterOfInterestPoint(Vec3f::zero());
    mMayaCam.setCurrentCam(initCam);
    
    // BSpline
	mBasePoints.push_back( Vec3f( 0, -1, 0 ) );
	mBasePoints.push_back( Vec3f( 0, 0, 0 ) );
	mBasePoints.push_back( Vec3f( 0, 1, 0 ) );
    mBasePoints.push_back( Vec3f( 0, 2, 0 ) );
	mCurPoints = mBasePoints;
	int  degree = 3;
	bool loop = false;
	bool open = true;
	mBSpline = BSpline3f( mCurPoints, degree, loop, open );
    
    mNumSegs = 32;
    mDrawCurve = true;
	mDrawFrames = true;
	mDrawMesh = true;
	mDrawSlices = true;
	mWireframe = true;
	mAnimate = false;
	mNumSegs = 32;
    
    mParams = params::InterfaceGl::create( getWindow(), "Parameters", Vec2i( 200, 200 ) );
    mParams->addParam( "Framerate",     &mAvgFramerate,    "", true );
    mParams->addSeparator();
	mParams->addParam( "Draw Curve",    &mDrawCurve,    "key=c" );
	mParams->addParam( "Wireframe",     &mWireframe,    "key=w" );
	mParams->addParam( "Draw Mesh",     &mDrawMesh,     "key=m" );
	mParams->addParam( "Draw Slices",   &mDrawSlices,   "key=l" );
	mParams->addParam( "Draw Frames",   &mDrawFrames,   "key=t" );
    mParams->addParam( "Animate",       &mAnimate,      "key=p" );
	mParams->addParam( "Segments",      &mNumSegs,      "min=4 max=1024 keyIncr== keyDecr=-" );
}

void Tentacles_TestingApp::mouseDown( MouseEvent event )
{
    if( event.isAltDown() ) {
		mMayaCam.mouseDown( event.getPos() );
    }
}

void Tentacles_TestingApp::mouseDrag( MouseEvent event )
{
    if( event.isAltDown() ) {
		mMayaCam.mouseDrag( event.getPos(), event.isLeftDown(), event.isMiddleDown(), event.isRightDown() );
    }
}

void Tentacles_TestingApp::update()
{
    updateTubeMesh();
    mAvgFramerate = getAverageFps();
}

void Tentacles_TestingApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
	gl::setMatrices( mMayaCam.getCamera() );
    
	gl::disableAlphaBlending();
	if( mWireframe && mTubeMesh.getNumTriangles() ) {
		gl::enableWireframe();
		gl::color( Color( 0.2f, 0.2f, 0.5f ) );
		gl::draw( mTubeMesh );
		gl::disableWireframe();
	}
	
	gl::enableAdditiveBlending();
	if( mDrawMesh && mTubeMesh.getNumTriangles() ) {
		gl::color( ColorA( 1, 1, 1, 0.25f ) );
		gl::draw( mTubeMesh );
	}
	
	if( mDrawSlices ) {
		mTube.drawFrameSlices( 0.25f );
	}
	
	if( mDrawCurve ) {
		gl::color( Color( 1, 1, 1 ) );
		mTube.drawPs();
	}
    
	if( mDrawFrames ) {
		mTube.drawFrames( 0.5f );
	}
	
	mParams->draw();
}

#pragma mark - additional tube functions
void Tentacles_TestingApp::updateTubeMesh()
{
    // Profile
	std::vector<Vec3f> prof;
    makeCircleProfile( prof, 0.25f, 16 );
	mTube.setProfile( prof );
	
	// BSpline
	if( mAnimate ) {
		float t = getElapsedSeconds();
//		for( size_t i = 0; i < mBasePoints.size(); ++i ) {
//			float dx = 0;
//			float dy = 0;
//			float dz = 0;
//			if( i > 0 && ( i < mBasePoints.size() - 1 ) ) {
//				dx = sin( t*i )*2.0f;
//				dy = sin( t*i/3.0f );
//				dz = cos( t*i )*4.0f;
//			}
//			mCurPoints[i] = mBasePoints[i] + Vec3f( dx, dy, dz );
//		}
        
        //snakey along x
        //move first point
        
        for( size_t i = 0; i < mBasePoints.size(); ++i ) {
			float dx = 0;
			float dy = 0;
			float dz = 0;
            //if( i > mBasePoints.size() - 2 ) //only end point
            if( i > 0 ) //all points except first
			//if( i > 0 && ( i < mBasePoints.size() - 1 ) ) //all points except ends
            {
//                if(i%2==0) {
                    dx = sin( t*i*mBasePoints.size() );// * ((float)i/(float)mBasePoints.size());
//                }
//                else {
//                    dx = sin( t*i*mBasePoints.size() );// * ((float)i/(float)mBasePoints.size());
//                }
				//dy = sin( t*i/3.0f );
				//dz = cos( t*i )*4.0f;
			}
			mCurPoints[i] = mBasePoints[i] + Vec3f( dx, dy, dz );
		}

	}
	
	// Make the b-spline
	int degree = 3;
	bool loop = false;
	bool open = true;
	mBSpline = BSpline3f( mCurPoints, degree, loop, open );
	
	// Tube
	mTube.setBSpline( mBSpline );
	mTube.setNumSegments( mNumSegs );
	mTube.sampleCurve();
    mTube.buildPTF();
	mTube.buildMesh( &mTubeMesh );
}

CINDER_APP_NATIVE( Tentacles_TestingApp, RendererGl )

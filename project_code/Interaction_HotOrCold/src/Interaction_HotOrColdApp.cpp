#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"
#include "cinder/CinderMath.h"
#include "cinder/Rand.h"

#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "boost/lambda/lambda.hpp"
#include "boost/lexical_cast.hpp"

#include "DeferredRenderer.h"

#include "Constants.h"
#include "Utility_3D.h"
#include "ResourceManager.h"
#include "KeyboardHandler.h"
#include "BasicModel.h"
#include "Spike.h"

#include "cinder/Font.h"
#include "cinder/Text.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Interaction_HotOrColdApp : public AppNative {
public:
    void shutdown();
    void prepareSettings(Settings *settings);
	void setup();
    void keyDown( KeyEvent event );
    void keyUp( KeyEvent event );
    void mouseMove(MouseEvent event);
    void mouseDown(MouseEvent event);
	void update();
	void draw();
    //void shutdown();
    
    CameraPersp     mCam;
    Utility_3D      m3DUtility;
    
    //game objects
    vector<int>         mHeldKeys;
    vector<Spike*>      mSpikes;
    ResourceManager     mResourceManager;
    KeyboardHandler     mKeyboardHandler;
    BasicModel          mCentralSphere;
    BasicModel          mGroundPlane;
    Light_PS            *mHeatSource;
    Light_PS            *mColdSource;
    
    //deferred misc.
    DeferredRenderer    mDeferredRenderer;
    int                 mRenderView;
    void drawShadowCasters(gl::GlslProg* deferShader);
    void drawNonShadowCasters(gl::GlslProg* deferShader);
    void drawOverlay() const;
    void drawDepthParticles() const;
};

void Interaction_HotOrColdApp::shutdown()
{
    for(vector<Spike*>::iterator spikeIter = mSpikes.begin(); spikeIter != mSpikes.end(); spikeIter++) {
        delete (*spikeIter);
    }
}

void Interaction_HotOrColdApp::prepareSettings(Settings *settings)
{
    settings->setFrameRate( ProjectConstants::APP_DESIRED_FRAMERATE );
    settings->setWindowSize( ProjectConstants::APP_RES );
    settings->setBorderless();
}

void Interaction_HotOrColdApp::setup()
{
	//hide mouse
	hideCursor();

    mResourceManager.setup(); //!!MUST BE DONE FIRST
    mCentralSphere.setup(&mResourceManager, ResourceManager::MODEL_CENTRAL_SPHERE, Vec3f::zero());
    mGroundPlane.setup(&mResourceManager, ResourceManager::MODEL_GROUND_PLANE, Vec3f(0.0f, 0.0f, -2.0f));
    
    //set up camera
	mCam.setPerspective( 45.0f, getWindowAspectRatio(), 0.1f, 10000.0f );
    mCam.lookAt(Vec3f( 0.0f, 0.0f, 7.5f ), Vec3f::zero(), Vec3f(0.0f, 0.0f, 1.0f) );
    mCam.setCenterOfInterestPoint(Vec3f::zero());
    
    //set up 3D utility
    m3DUtility.setModelView(mCam.getModelViewMatrix());
    m3DUtility.setProjection(mCam.getProjectionMatrix());
    m3DUtility.setViewport(gl::getViewport());
    m3DUtility.setWindowSize(Rectf(0.0f, 0.0f, (float)getWindowWidth(), (float)getWindowHeight()));
    
    //setup deferred renderer
    //create functions pointers to send to deferred renderer
    boost::function<void(gl::GlslProg*)> fRenderShadowCastersFunc = boost::bind( &Interaction_HotOrColdApp::drawShadowCasters, this, boost::lambda::_1 );
    boost::function<void(gl::GlslProg*)> fRenderNotShadowCastersFunc = boost::bind( &Interaction_HotOrColdApp::drawNonShadowCasters, this,  boost::lambda::_1 );
    boost::function<void(void)> fRenderOverlayFunc = boost::bind( &Interaction_HotOrColdApp::drawOverlay, this );
    boost::function<void(void)> fRenderParticlesFunc = boost::bind( &Interaction_HotOrColdApp::drawDepthParticles, this );
    mRenderView = DeferredRenderer::SHOW_FINAL_VIEW;
    mDeferredRenderer.setup( fRenderShadowCastersFunc, fRenderNotShadowCastersFunc, NULL, NULL, &mCam, ProjectConstants::APP_RES, 1024, true, true);
    mColdSource = mDeferredRenderer.addCubeLight( Vec3f(-3.0f, 0.0f, 3.0f), ProjectConstants::COLOR_BLUE * LIGHT_BRIGHTNESS_DEFAULT * 0.3f, false, false);
    mHeatSource = mDeferredRenderer.addCubeLight( Vec3f(3.0f, 0.0f, 3.0f), ProjectConstants::COLOR_RED * LIGHT_BRIGHTNESS_DEFAULT * 0.3f, true, false);
    
    //determine openGL coordinates relative to window coordinates
    Vec3f convertedTopLeftCorner = m3DUtility.screenToWorld( Vec2i(0, 0) );
    Vec3f convertedBottomRightCorner = m3DUtility.screenToWorld( getWindowSize() );
    float ignoreRadiusInit = convertedTopLeftCorner.y * 0.3f;
    float ignoreRadiusTarget = convertedTopLeftCorner.y * 0.5f;
    
    //create spikes first
    for (int i=0; i < ProjectConstants::NUM_INIT_SPIKES; i++) {
        Spike *newSpike = new Spike();
        int model = Rand::randInt(ResourceManager::MODEL_SPIKE_1, ResourceManager::MODEL_SPIKE_3);
        mSpikes.push_back( newSpike );
        newSpike->setup(&mResourceManager, model, convertedTopLeftCorner, convertedBottomRightCorner, ignoreRadiusInit, ignoreRadiusTarget);
    }
    
    glShadeModel(GL_FLAT); //help make sure low-poly look in case default is GL_SMOOTH
}

void Interaction_HotOrColdApp::keyDown( KeyEvent event )
{
    mKeyboardHandler.setState(event.getCode(), true);
    
    //toggle through deferred render modes using - and + keys
    switch (event.getCode()) {
        case KeyEvent::KEY_EQUALS:
        {
            mRenderView++;
            if(mRenderView>(DeferredRenderer::NUM_RENDER_VIEWS - 1)) {
                mRenderView = 0;
            }
            
            console() << mRenderView << "\n";
        }
            break;
        case KeyEvent::KEY_KP_MINUS:
        {
            mRenderView--;
            if(mRenderView<0) {
                mRenderView = DeferredRenderer::NUM_RENDER_VIEWS - 1;
            }
            
            console() << mRenderView << "\n";
        }
            break;
        case KeyEvent::KEY_SPACE:
        {}
            break;
        case KeyEvent::KEY_s:
        {
            for(vector<Spike*>::iterator spikeIter = mSpikes.begin(); spikeIter != mSpikes.end(); spikeIter++) {
                (*spikeIter)->extract();
            }
        }
            break;
        case KeyEvent::KEY_r:
        {
            for(vector<Spike*>::iterator spikeIter = mSpikes.begin(); spikeIter != mSpikes.end(); spikeIter++) {
                (*spikeIter)->retract();
            }
        }
            break;
        case KeyEvent::KEY_RETURN:
        {}
            break;
		case KeyEvent::KEY_ESCAPE:
        {
            exit(1);
        }
            break;
        default:
            break;
    }
}

void Interaction_HotOrColdApp::keyUp( KeyEvent event )
{
    mKeyboardHandler.setState(event.getCode(), false);
}

void Interaction_HotOrColdApp::mouseMove(MouseEvent event)
{}

void Interaction_HotOrColdApp::mouseDown(MouseEvent event)
{
    if(event.isLeftDown()) {
        Vec2i mousePos = getMousePos() - getWindowPos();
        Vec3f convertedPos = m3DUtility.screenToWorld(mousePos); //translate mousePos to OpenGL coordinates
        console() << convertedPos << "\n";
    }
}

void Interaction_HotOrColdApp::update()
{
    //update central sphere
    mCentralSphere.update();
    
    //update projectile lights
    int counter = 0;
    float speedRot = 0.0f;
    for( vector<Light_PS*>::iterator lightIter = mDeferredRenderer.mCubeLights.begin(); lightIter != mDeferredRenderer.mCubeLights.end(); lightIter++ ) {
        speedRot = ((float)getElapsedSeconds() * 0.5f) + ((float)M_PI * (float)counter);
        (*lightIter)->setPos(Vec3f( math<float>::sin(speedRot) * 3.0f, math<float>::cos(speedRot) * 3.0f, 3.0f));
        ++counter;
        
        if(counter > 1) {
            break;
        }
    }
}

void Interaction_HotOrColdApp::draw()
{
    glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
    
    mDeferredRenderer.renderFullScreenQuad(mRenderView);
}

#pragma mark - deferred render function

void Interaction_HotOrColdApp::drawShadowCasters(gl::GlslProg* deferShader)
{
//    mPlayer1.draw();
    mCentralSphere.draw();
    
    for(vector<Spike*>::iterator spikeIter = mSpikes.begin(); spikeIter != mSpikes.end(); spikeIter++) {
        (*spikeIter)->draw();
    }
}

void Interaction_HotOrColdApp::drawNonShadowCasters(gl::GlslProg* deferShader)
{
    mGroundPlane.draw();
}

void Interaction_HotOrColdApp::drawOverlay() const
{}

void Interaction_HotOrColdApp::drawDepthParticles() const
{}

CINDER_APP_NATIVE( Interaction_HotOrColdApp, RendererGl )

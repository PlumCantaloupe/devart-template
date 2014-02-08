#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MedusaApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void MedusaApp::setup()
{
}

void MedusaApp::mouseDown( MouseEvent event )
{
}

void MedusaApp::update()
{
}

void MedusaApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( MedusaApp, RendererGl )

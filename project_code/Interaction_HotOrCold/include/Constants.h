//
//  Constants.h
//  Game_BadDreams
//
//  Created by Anthony Scavarelli on 2/21/2014.
//
//

#ifndef Game_BadDreams_Constants_h
#define Game_BadDreams_Constants_h

#include "cinder/app/AppNative.h"

namespace ProjectConstants {
    
static const ci::Vec2i  APP_RES( 1000, 512 );
static const float      APP_DESIRED_FRAMERATE = 60.0f;

static const ci::Color  COLOR_RED(0.94f, 0.15f, 0.23f);
static const ci::Color  COLOR_BLUE(0.10f, 0.69f, 0.93f);
    
static const int        NUM_INIT_SPIKES = 300;

};
#endif

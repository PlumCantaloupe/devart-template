//
//  KeyboardHandler.h
//  Game_BadDreams
//
//  Created by Anthony Scavarelli on 2/21/2014.
//
//

#ifndef Game_BadDreams_KeyboardHandler_h
#define Game_BadDreams_KeyboardHandler_h

#include "cinder/app/AppNative.h"

using namespace ci;
using namespace ci::app;

class KeyboardHandler
{
    public:
    KeyboardHandler()
    {
        for(int i=0; i<KeyEvent::KEY_LAST; i++) {
            mAllKeys[i] = false;
        }
    }
    
    ~KeyboardHandler(){}
    
    void setState(int keyCode, BOOL state)
    {
        mAllKeys[keyCode] = state;
    }
    
    BOOL getState(int keyCode)
    {
        return mAllKeys[keyCode];
    }
    
    private:
    BOOL mAllKeys[KeyEvent::KEY_LAST];
};

#endif

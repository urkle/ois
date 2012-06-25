/*
The zlib/libpng License

Copyright (c) 2005-2007 Phillip Castaneda (pjcast -- www.wreckedgames.com)

This software is provided 'as-is', without any express or implied warranty. In no event will
the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following
restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that 
		you wrote the original software. If you use this software in a product, 
		an acknowledgment in the product documentation would be appreciated but is 
		not required.

    2. Altered source versions must be plainly marked as such, and must not be 
		misrepresented as being the original software.

    3. This notice may not be removed or altered from any source distribution.
*/
#include "SDL/SDLJoyStick.h"
#include "SDL/SDLInputManager.h"
#include "OISException.h"
#include "OISEvents.h"

using namespace OIS;

//-------------------------------------------------------------------//
SDLJoyStick::SDLJoyStick(InputManager* creator, bool buffered, const JoyStickInfo& js)
    : JoyStick(js.vendor, buffered, js.devId, creator)
{
    mJoyStick = 0;
    
	mState.mAxes.clear();
	mState.mAxes.resize(js.axes);
	mState.mButtons.clear();
	mState.mButtons.resize(js.buttons);

	mPOVs = js.hats;
    mBalls = js.balls;

	mButtonMap = js.button_map;
	mAxisMap = js.axis_map;
}

SDLJoyStick::~SDLJoyStick()
{
    if (mJoyStick) {
        SDL_JoystickClose(mJoyStick);
    }
}

//-------------------------------------------------------------------//
void SDLJoyStick::_initialize()
{
    mJoyStick = SDL_JoystickOpen(mDevID);
	//Clear old joy state
	mState.mAxes.resize(mAxisMap.size());
	mState.clear();

	if( mJoyStick == 0 )
		OIS_EXCEPT(E_InputDeviceNonExistant, "SDLJoyStick::_initialize() >> JoyStick Not Found!");
}

//-------------------------------------------------------------------//
void SDLJoyStick::capture()
{
	//Used to determine if an axis has been changed and needs an event
	bool axisMoved[32] = {false, false, false, false, false, false, false, false, false, false, false, false, false,
						  false, false, false, false, false, false, false, false, false, false, false, false, false,
						  false, false, false, false, false, false};

	//We are in non blocking mode - we just read once, and try to fill up buffer
	SDL_Event events[OIS_SDL_JOY_BUFF];
    int count = SDL_PeepEvents(events, OIS_SDL_JOY_BUFF, SDL_GETEVENT,
            SDL_JOYAXISMOTIONMASK | SDL_JOYBALLMOTIONMASK | SDL_JOYHATMOTIONMASK| SDL_JOYBUTTONDOWNMASK | SDL_JOYBUTTONUPMASK);

    for ( int i =0; i < count; ++i )
	{
        switch( events[i].type )
        {
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
            {
                int button = mButtonMap[events[i].jbutton.button];
                if (events[i].jbutton.state == SDL_PRESSED)
                {
                    mState.mButtons[button] = true;
                    if( mBuffered && mListener )
    						if(!mListener->buttonPressed(JoyStickEvent(this,mState), button)) return;
                }
                else
                {
                    mState.mButtons[button] = false;
                    if( mBuffered && mListener )
    						if(!mListener->buttonReleased(JoyStickEvent(this,mState), button)) return;
                }
                break;
            }
            case SDL_JOYAXISMOTION:
            {
                int axis = mAxisMap[events[i].jaxis.axis];
                axisMoved[axis] = true;
                mState.mAxes[axis].abs = events[i].jaxis.value;
                break;
            }
            case SDL_JOYHATMOTION:
            {
                int hatpos = 0;
                switch(events[i].jhat.value) {
                    case SDL_HAT_CENTERED: hatpos = Pov::Centered; break;
                    case SDL_HAT_UP: hatpos = Pov::North; break;
                    case SDL_HAT_RIGHT: hatpos = Pov::East; break;
                    case SDL_HAT_DOWN: hatpos = Pov::South; break;
                    case SDL_HAT_LEFT: hatpos = Pov::West; break;
                    case SDL_HAT_RIGHTUP: hatpos = Pov::NorthEast; break;
                    case SDL_HAT_RIGHTDOWN: hatpos = Pov::SouthEast; break;
                    case SDL_HAT_LEFTUP: hatpos = Pov::NorthWest; break;
                    case SDL_HAT_LEFTDOWN: hatpos = Pov::SouthWest; break;
                }
                
                mState.mPOV[events[i].jhat.hat].direction = hatpos;
                if( mBuffered && mListener )
                    if( mListener->povMoved( JoyStickEvent(this,mState), events[i].jhat.hat) == false ) return;
            }
            case SDL_JOYBALLMOTION:
            {
                // I don't have one witha  ball so I can't test.
            }
        }
	}

	//All axes are combined into one movement per pair per captured frame
	if( mBuffered && mListener )
	{
        size_t count = std::max((int)mAxisMap.size(), 32);
		for( int i = 0; i < count; ++i )
			if( axisMoved[i] )
				if( mListener->axisMoved( JoyStickEvent(this,mState), i) == false )
					return;
	}
}

//-------------------------------------------------------------------//
void SDLJoyStick::setBuffered(bool buffered)
{
	if( buffered != mBuffered )
	{
		mBuffered = buffered;
		_initialize();
	}
}

//-------------------------------------------------------------------//
JoyStickInfo SDLJoyStick::_getJoyInfo()
{
	JoyStickInfo js;

	js.devId = mDevID;
	js.vendor = mVendor;
	js.axes = (int)mState.mAxes.size();
	js.buttons = (int)mState.mButtons.size();
	js.hats = mPOVs;
    js.balls = mBalls;
	js.button_map = mButtonMap;
	js.axis_map = mAxisMap;

	return js;
}

//-------------------------------------------------------------------//
JoyStickInfoList SDLJoyStick::_scanJoys()
{
	JoyStickInfoList joys;

    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
        SDL_JoystickEventState(SDL_ENABLE);
    }
    int count = SDL_NumJoysticks();

    // Scan through joysticks
    for(int i = 0; i < count; ++i )
	{
        JoyStickInfo joyinfo;
        joyinfo.vendor.assign(SDL_JoystickName(i));
        SDL_Joystick *joy = SDL_JoystickOpen(i);
        if (joy)
        {
            joyinfo.devId = i;
            joyinfo.axes = SDL_JoystickNumAxes(joy);
            joyinfo.buttons = SDL_JoystickNumButtons(joy);
            joyinfo.hats = SDL_JoystickNumHats(joy);
            joyinfo.balls = SDL_JoystickNumBalls(joy);
            SDL_JoystickClose(joy);

            joyinfo.button_map.clear();
            for (int b = 0; b < joyinfo.buttons; ++b)
            {
                joyinfo.button_map[b] = b;
            }

            joyinfo.axis_map.clear();
            for (int a = 0; a < joyinfo.axes; ++a)
            {
                joyinfo.axis_map[a] = a;
                // SDL Range is the same as OIS range, so no need for range maps
            }

            joys.push_back(joyinfo);
        }
	}

	return joys;
}

//-------------------------------------------------------------------//
void SDLJoyStick::_clearJoys(JoyStickInfoList &joys)
{
	joys.clear();
}

//-------------------------------------------------------------------//
Interface* SDLJoyStick::queryInterface(Interface::IType type)
{
	return 0;
}

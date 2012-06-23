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
#include "SDL/SDLKeyboard.h"
#include "SDL/SDLInputManager.h"
#include "OISException.h"
#include "OISEvents.h"
#include <sstream>

using namespace OIS;

//-------------------------------------------------------------------//
SDLKeyboard::SDLKeyboard(InputManager* creator, bool buffered )
    : Keyboard(creator->inputSystemName(), buffered, 0, creator)
{
    mKeyMap.insert( KeyMap::value_type(SDLK_ESCAPE,KC_ESCAPE) );
	mKeyMap.insert( KeyMap::value_type(SDLK_1, KC_1) );
	mKeyMap.insert( KeyMap::value_type(SDLK_2, KC_2) );
	mKeyMap.insert( KeyMap::value_type(SDLK_3, KC_3) );
	mKeyMap.insert( KeyMap::value_type(SDLK_4, KC_4) );
	mKeyMap.insert( KeyMap::value_type(SDLK_5, KC_5) );
	mKeyMap.insert( KeyMap::value_type(SDLK_6, KC_6) );
	mKeyMap.insert( KeyMap::value_type(SDLK_7, KC_7) );
	mKeyMap.insert( KeyMap::value_type(SDLK_8, KC_8) );
	mKeyMap.insert( KeyMap::value_type(SDLK_9, KC_9) );
	mKeyMap.insert( KeyMap::value_type(SDLK_0, KC_0) );
	mKeyMap.insert( KeyMap::value_type(SDLK_MINUS, KC_MINUS) );
	mKeyMap.insert( KeyMap::value_type(SDLK_EQUALS, KC_EQUALS) );
	mKeyMap.insert( KeyMap::value_type(SDLK_BACKSPACE, KC_BACK) );
	mKeyMap.insert( KeyMap::value_type(SDLK_TAB, KC_TAB) );
	mKeyMap.insert( KeyMap::value_type(SDLK_q, KC_Q) );
	mKeyMap.insert( KeyMap::value_type(SDLK_w, KC_W) );
	mKeyMap.insert( KeyMap::value_type(SDLK_e, KC_E) );
	mKeyMap.insert( KeyMap::value_type(SDLK_r, KC_R) );
	mKeyMap.insert( KeyMap::value_type(SDLK_t, KC_T) );
	mKeyMap.insert( KeyMap::value_type(SDLK_y, KC_Y) );
	mKeyMap.insert( KeyMap::value_type(SDLK_u, KC_U) );
	mKeyMap.insert( KeyMap::value_type(SDLK_i, KC_I) );
	mKeyMap.insert( KeyMap::value_type(SDLK_o, KC_O) );
	mKeyMap.insert( KeyMap::value_type(SDLK_p, KC_P) );
	mKeyMap.insert( KeyMap::value_type(SDLK_RETURN, KC_RETURN) );
	mKeyMap.insert( KeyMap::value_type(SDLK_LCTRL, KC_LCONTROL));
	mKeyMap.insert( KeyMap::value_type(SDLK_a, KC_A) );
	mKeyMap.insert( KeyMap::value_type(SDLK_s, KC_S) );
	mKeyMap.insert( KeyMap::value_type(SDLK_d, KC_D) );
	mKeyMap.insert( KeyMap::value_type(SDLK_f, KC_F) );
	mKeyMap.insert( KeyMap::value_type(SDLK_g, KC_G) );
	mKeyMap.insert( KeyMap::value_type(SDLK_h, KC_H) );
	mKeyMap.insert( KeyMap::value_type(SDLK_j, KC_J) );
	mKeyMap.insert( KeyMap::value_type(SDLK_k, KC_K) );
	mKeyMap.insert( KeyMap::value_type(SDLK_l, KC_L) );
	mKeyMap.insert( KeyMap::value_type(SDLK_SEMICOLON, KC_SEMICOLON) );
	mKeyMap.insert( KeyMap::value_type(SDLK_COLON, KC_COLON) );
	mKeyMap.insert( KeyMap::value_type(SDLK_QUOTE, KC_APOSTROPHE) );
	mKeyMap.insert( KeyMap::value_type(SDLK_BACKQUOTE, KC_GRAVE)  );
	mKeyMap.insert( KeyMap::value_type(SDLK_LSHIFT, KC_LSHIFT) );
	mKeyMap.insert( KeyMap::value_type(SDLK_BACKSLASH, KC_BACKSLASH) );
	mKeyMap.insert( KeyMap::value_type(SDLK_SLASH, KC_SLASH) );
	mKeyMap.insert( KeyMap::value_type(SDLK_z, KC_Z) );
	mKeyMap.insert( KeyMap::value_type(SDLK_x, KC_X) );
	mKeyMap.insert( KeyMap::value_type(SDLK_c, KC_C) );
	mKeyMap.insert( KeyMap::value_type(SDLK_v, KC_V) );
	mKeyMap.insert( KeyMap::value_type(SDLK_b, KC_B) );
	mKeyMap.insert( KeyMap::value_type(SDLK_n, KC_N) );
	mKeyMap.insert( KeyMap::value_type(SDLK_m, KC_M) );
	mKeyMap.insert( KeyMap::value_type(SDLK_COMMA, KC_COMMA)  );
	mKeyMap.insert( KeyMap::value_type(SDLK_PERIOD, KC_PERIOD));
	mKeyMap.insert( KeyMap::value_type(SDLK_RSHIFT, KC_RSHIFT));
	mKeyMap.insert( KeyMap::value_type(SDLK_KP_MULTIPLY, KC_MULTIPLY) );
	mKeyMap.insert( KeyMap::value_type(SDLK_LALT, KC_LMENU) );
	mKeyMap.insert( KeyMap::value_type(SDLK_SPACE, KC_SPACE));
	mKeyMap.insert( KeyMap::value_type(SDLK_CAPSLOCK, KC_CAPITAL) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F1, KC_F1) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F2, KC_F2) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F3, KC_F3) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F4, KC_F4) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F5, KC_F5) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F6, KC_F6) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F7, KC_F7) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F8, KC_F8) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F9, KC_F9) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F10, KC_F10) );
	mKeyMap.insert( KeyMap::value_type(SDLK_NUMLOCK, KC_NUMLOCK) );
	mKeyMap.insert( KeyMap::value_type(SDLK_SCROLLOCK, KC_SCROLL));
	mKeyMap.insert( KeyMap::value_type(SDLK_KP7, KC_NUMPAD7) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP8, KC_NUMPAD8) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP9, KC_NUMPAD9) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP_MINUS, KC_SUBTRACT) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP4, KC_NUMPAD4) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP5, KC_NUMPAD5) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP6, KC_NUMPAD6) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP_PLUS, KC_ADD) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP1, KC_NUMPAD1) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP2, KC_NUMPAD2) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP3, KC_NUMPAD3) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP0, KC_NUMPAD0) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP_PERIOD, KC_DECIMAL) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F11, KC_F11) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F12, KC_F12) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F13, KC_F13) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F14, KC_F14) );
	mKeyMap.insert( KeyMap::value_type(SDLK_F15, KC_F15) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP_EQUALS, KC_NUMPADEQUALS) );
	mKeyMap.insert( KeyMap::value_type(SDLK_KP_DIVIDE, KC_DIVIDE) );
	mKeyMap.insert( KeyMap::value_type(SDLK_SYSREQ, KC_SYSRQ) );
	mKeyMap.insert( KeyMap::value_type(SDLK_RALT, KC_RMENU) );
	mKeyMap.insert( KeyMap::value_type(SDLK_HOME, KC_HOME) );
	mKeyMap.insert( KeyMap::value_type(SDLK_UP, KC_UP) );
	mKeyMap.insert( KeyMap::value_type(SDLK_PAGEUP, KC_PGUP) );
	mKeyMap.insert( KeyMap::value_type(SDLK_LEFT, KC_LEFT) );
	mKeyMap.insert( KeyMap::value_type(SDLK_RIGHT, KC_RIGHT) );
	mKeyMap.insert( KeyMap::value_type(SDLK_END, KC_END) );
	mKeyMap.insert( KeyMap::value_type(SDLK_DOWN, KC_DOWN) );
	mKeyMap.insert( KeyMap::value_type(SDLK_PAGEDOWN, KC_PGDOWN) );
	mKeyMap.insert( KeyMap::value_type(SDLK_INSERT, KC_INSERT) );
	mKeyMap.insert( KeyMap::value_type(SDLK_DELETE, KC_DELETE) );
	mKeyMap.insert( KeyMap::value_type(SDLK_LSUPER, KC_LWIN) );
	mKeyMap.insert( KeyMap::value_type(SDLK_RSUPER, KC_RWIN) );
    
    static_cast<SDLInputManager*>(mCreator)->_setKeyboardUsed(true);
}

//-------------------------------------------------------------------//
void SDLKeyboard::_initialize()
{
	//Clear our keyboard state buffer
	memset( &KeyBuffer, 0, 256 );
    mModifiers = 0;

    mSDLBuff = 0;


	SDL_EnableUNICODE(1);
}

//-------------------------------------------------------------------//
SDLKeyboard::~SDLKeyboard()
{
    static_cast<SDLInputManager*>(mCreator)->_setKeyboardUsed(false);
}

//-------------------------------------------------------------------//
bool SDLKeyboard::isKeyDown( KeyCode key ) const
{
	return KeyBuffer[key] == 1 ? true : false;
}

//-------------------------------------------------------------------//
void SDLKeyboard::capture()
{
	SDL_Event events[OIS_SDL_KEY_BUFF];
	int count = SDL_PeepEvents(events, OIS_SDL_KEY_BUFF, SDL_GETEVENT, 
		SDL_EVENTMASK(SDL_KEYDOWN) | SDL_EVENTMASK(SDL_KEYUP));

	for( int i = 0; i < count; ++i )
	{
        if( events[i].key.state == SDL_PRESSED )
        {
            _injectKeyDown(events[i].key.keysym.sym, events[i].key.keysym.unicode);
        }
        else
        {
            _injectKeyUp(events[i].key.keysym.sym);
        }
	}

	//Release Grab mode on Alt-Tab combinations (for non-window systems)
	if( KeyBuffer[KC_RMENU] || KeyBuffer[KC_LMENU])
	{
		if( KeyBuffer[KC_TAB] )
            static_cast<SDLInputManager*>(mCreator)->_setGrabMode(false);
	}
}

//-------------------------------------------------------------------//
void SDLKeyboard::setBuffered(bool buffered)
{
	mBuffered = buffered;
}

//-------------------------------------------------------------------//
bool SDLKeyboard::_injectKeyDown( SDLKey key, int text )
{
	KeyCode kc = mKeyMap[key];
	KeyBuffer[kc] = 1;

	//Turn on modifier flags
	if( kc == KC_LCONTROL || kc == KC_RCONTROL)
		mModifiers |= Ctrl;
	else if( kc == KC_LSHIFT || kc == KC_RSHIFT )
		mModifiers |= Shift;
	else if( kc == KC_LMENU || kc == KC_RMENU )
		mModifiers |= Alt;

	if( mBuffered && mListener )
		return mListener->keyPressed(KeyEvent(this,kc,text));

	return true;
}

//-------------------------------------------------------------------//
bool SDLKeyboard::_injectKeyUp( SDLKey key )
{
	KeyCode kc = mKeyMap[key];
	KeyBuffer[kc] = 0;

	//Turn off modifier flags
	if( kc == KC_LCONTROL || kc == KC_RCONTROL)
		mModifiers &= ~Ctrl;
	else if( kc == KC_LSHIFT || kc == KC_RSHIFT )
		mModifiers &= ~Shift;
	else if( kc == KC_LMENU || kc == KC_RMENU )
		mModifiers &= ~Alt;

	if( mBuffered && mListener )
		return mListener->keyReleased(KeyEvent(this, kc, 0));

	return true;
}

//-------------------------------------------------------------------//
const std::string& SDLKeyboard::getAsString( KeyCode kc )
{
    mGetString = "Unknown";
    char *temp = 0;

    KeyMap::iterator i = mKeyMap.begin(),
            e = mKeyMap.end();

    for( ; i != e; ++i )
    {
        if( i->second == kc )
        {
            temp = SDL_GetKeyName(i->first);
            if( temp )
                mGetString = temp;
            break;
        }
    }
	return mGetString;
}

//-------------------------------------------------------------------//
void SDLKeyboard::copyKeyStates( char keys[256] ) const
{
	for(int i = 0; i < 256; ++i)
		keys[i] = KeyBuffer[i];
}

//-------------------------------------------------------------------//
void SDLKeyboard::setTextTranslation( TextTranslationMode mode )
{
	mTextMode = mode;
	if( mode == Off || mode == Ascii )
		SDL_EnableUNICODE(0);
	else if( mode == Unicode )
		SDL_EnableUNICODE(1);
}

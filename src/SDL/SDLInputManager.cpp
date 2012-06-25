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
#include "SDL/SDLInputManager.h"
#include "SDL/SDLKeyboard.h"
#include "SDL/SDLMouse.h"
#include "SDL/SDLJoyStick.h"
#include "OISException.h"
#include "OISObject.h"

using namespace OIS;

//--------------------------------------------------------------------------------//
SDLInputManager::SDLInputManager() : InputManager("SDLInputManager"),
        mGrabMouse(true), mHideMouse(true), mKeyboardUsed(false), mMouseUsed(false),
        joySticks(0)
{
    mFactories.push_back(this);
}

//--------------------------------------------------------------------------------//
SDLInputManager::~SDLInputManager()
{
    //Close all joysticks
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}

//--------------------------------------------------------------------------------//
void SDLInputManager::_initialize( ParamList &paramList )
{
	Uint32 flags = SDL_WasInit(0);
	if( flags == 0 )
		OIS_EXCEPT( E_General, "SDLInputManager::SDLInputManager >> SDL Not Initialized already!");
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
        SDL_JoystickEventState(SDL_ENABLE);
    }

    _parseConfigSettings( paramList );
	_enumerateDevices();
}

//--------------------------------------------------------------------------------//
void SDLInputManager::_parseConfigSettings( ParamList &paramList )
{
    ParamList::iterator i;

    //--------- Mouse Settings ------------//
    i = paramList.find("sdl_mouse_grab");
    if (i != paramList.end() )
        if ( i->second == "false" )
            mGrabMouse = false;

	i = paramList.find("sdl_mouse_hide");
	if( i != paramList.end() )
		if( i->second == "false" )
			mHideMouse = false;
}

//--------------------------------------------------------------------------------//
void SDLInputManager::_enumerateDevices()
{
    unusedJoyStickList = SDLJoyStick::_scanJoys();
    joySticks = unusedJoyStickList.size();
}

//----------------------------------------------------------------------------//
DeviceList SDLInputManager::freeDeviceList()
{
    DeviceList ret;
    if (mKeyboardUsed == false)
        ret.insert(std::make_pair(OISKeyboard, mInputSystemName));
    if (mMouseUsed == false)
        ret.insert(std::make_pair(OISMouse, mInputSystemName));

    for(JoyStickInfoList::iterator i = unusedJoyStickList.begin(); i != unusedJoyStickList.end(); ++i)
		ret.insert(std::make_pair(OISJoyStick, i->vendor));

    return ret;
}

//----------------------------------------------------------------------------//
int SDLInputManager::totalDevices(Type iType)
{
	switch(iType)
	{
	case OISKeyboard: return 1;
	case OISMouse: return 1;
	case OISJoyStick: return joySticks;
	default: return 0;
	}
}

//----------------------------------------------------------------------------//
int SDLInputManager::freeDevices(Type iType)
{
	switch(iType)
	{
	case OISKeyboard: return mKeyboardUsed ? 0 : 1;
	case OISMouse: return mMouseUsed ? 0 : 1;
	case OISJoyStick: return (int)unusedJoyStickList.size();
	default: return 0;
	}
}

//----------------------------------------------------------------------------//
bool SDLInputManager::vendorExist(Type iType, const std::string & vendor)
{
	if((iType == OISKeyboard || iType == OISMouse) && vendor == mInputSystemName)
	{
		return true;
	}
	else if( iType == OISJoyStick )
	{
		for(JoyStickInfoList::iterator i = unusedJoyStickList.begin(); i != unusedJoyStickList.end(); ++i)
			if(i->vendor == vendor)
				return true;
	}

	return false;
}

//----------------------------------------------------------------------------//
Object* SDLInputManager::createObject(InputManager *creator, Type iType, bool bufferMode, const std::string & vendor)
{
	Object* obj = 0;
	
	switch( iType )
	{
		case OISKeyboard: obj = new SDLKeyboard( this, bufferMode ); break;
		case OISMouse: obj = new SDLMouse( this, bufferMode, mGrabMouse, mHideMouse ); break;
		case OISJoyStick:
            for(JoyStickInfoList::iterator i = unusedJoyStickList.begin(); i != unusedJoyStickList.end(); ++i)
            {
                if(vendor == "" || i->vendor == vendor)
                {
                    obj = new SDLJoyStick(this, bufferMode, *i);
                    unusedJoyStickList.erase(i);
                    break;
                }
            }
            break;
		default:
            break;
	}

    if(obj == 0)
		OIS_EXCEPT(E_InputDeviceNonExistant, "No devices match requested type.");

	return obj;
}

//----------------------------------------------------------------------------//
void SDLInputManager::destroyObject( Object* obj )
{
	if( obj == 0 ) return;

    if(obj->type() == OISJoyStick)
    {
        unusedJoyStickList.push_back( ((SDLJoyStick*)obj)->_getJoyInfo() );
    }

	delete obj;
}

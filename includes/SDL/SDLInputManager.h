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
#ifndef OIS_SDLInputManager_H
#define OIS_SDLInputManager_H

#include "OISFactoryCreator.h"
#include "OISInputManager.h"
#include "SDL/SDLPrereqs.h"

namespace OIS
{
	/**
		SDL Input Manager wrapper
	*/
	class SDLInputManager : public InputManager, public FactoryCreator
	{
	public:
		SDLInputManager();
		virtual ~SDLInputManager();
		
        //InputManager Overrides
		/** @copydoc InputManager::_initialize */
		void _initialize( ParamList &paramList );

        //FactoryCreator Overrides
		/** @copydoc FactoryCreator::deviceList */
		DeviceList freeDeviceList();

		/** @copydoc FactoryCreator::totalDevices */
		int totalDevices(Type iType);

		/** @copydoc FactoryCreator::freeDevices */
		int freeDevices(Type iType);

		/** @copydoc FactoryCreator::vendorExist */
		bool vendorExist(Type iType, const std::string & vendor);

		/** @copydoc FactoryCreator::createObject */
		Object* createObject(InputManager *creator, Type iType, bool bufferMode, const std::string & vendor = "");

		/** @copydoc FactoryCreator::destroyObject */
		void destroyObject(Object* obj);

		//Utility methods to coordinate between mouse and keyboard grabbing
		bool _getGrabMode() {return mGrabMouse;};
		void _setGrabMode(bool grabbed) {mGrabMouse = grabbed;}

        //! Internal method, used for flaggin keyboard as available/unavailable for creation
		void _setKeyboardUsed(bool used) {mKeyboardUsed = used;}

		//! Internal method, used for flaggin mouse as available/unavailable for creation
		void _setMouseUsed(bool used) {mMouseUsed = used;}
	protected:
		//! internal class method for dealing with param list
		void _parseConfigSettings( ParamList &paramList );
		//! internal class method for finding attached devices
		void _enumerateDevices();

        //! List of unused joysticks ready to be used
		JoyStickInfoList unusedJoyStickList;
        //! Number of joysticks found
        char joySticks;

        //! Used to know if we used up keyboard
		bool mKeyboardUsed;

		//! Used to know if we used up mouse
		bool mMouseUsed;

		bool mGrabMouse;
		bool mHideMouse;
	};
}
#endif

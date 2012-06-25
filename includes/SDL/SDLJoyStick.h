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
#ifndef _SDL_JOYSTICK_H_EADER_
#define _SDL_JOYSTICK_H_EADER_

#include "OISJoyStick.h"
#include "SDL/SDLPrereqs.h"

namespace OIS
{
	/**
		SDL specialization of JoyStick class.
	*/
	class SDLJoyStick : public JoyStick
	{
	public:
		SDLJoyStick(InputManager* creator, bool buffered, const JoyStickInfo& js);
		virtual ~SDLJoyStick();

		/** @copydoc Object::setBuffered */
		virtual void setBuffered(bool buffered);

		/** @copydoc Object::capture */
		virtual void capture();

		/** @copydoc Object::queryInterface */
		virtual Interface* queryInterface(Interface::IType type);

		/** @copydoc Object::_initialize */
		virtual void _initialize();

		/**
		@remarks
			For internal use only... Returns a structure to the manager, to make the device
			availiable for use again
		*/
		JoyStickInfo _getJoyInfo();

		static JoyStickInfoList _scanJoys();
	protected:

		SDL_Joystick* mJoyStick;
        unsigned char mBalls;
	};
}

#endif //_SDL_JOYSTICK_H_EADER_

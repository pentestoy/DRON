/**
 *  Input/InputMapper.hpp
 *  (c) Jonathan Capps
 *  Created 12 Sept. 2011
 */

#ifndef _INPUT_MAPPER_HPP_
#define _INPUT_MAPPER_HPP_

#include <WinUser.h>

enum Action;

class InputMapper
{
	public:
		void SetKeyState( char key, bool pressed );

	private:
		bool MapKeyToAction( char key, Action& action );
};

#endif //_INPUT_MAPPER_HPP_

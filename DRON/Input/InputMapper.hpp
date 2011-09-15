/**
 *  Input/InputMapper.hpp
 *  (c) Jonathan Capps
 *  Created 12 Sept. 2011
 */

#ifndef INPUT_MAPPER_HPP
#define INPUT_MAPPER_HPP

#include <WinUser.h>

enum Action;

class InputMapper
{
	public:
		void SetKeyState( char key, bool pressed );

	private:
		bool MapKeyToAction( char key, Action& action );
};

#endif //INPUT_MAPPER_HPP

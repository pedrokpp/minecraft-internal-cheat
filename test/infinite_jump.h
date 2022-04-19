#pragma once
#include <jni.h>
#include <Windows.h>

#include "cheat.h"
#include "utils.h"
#include "player.h"

class infinite_jump {

	jobject playerobj;
	bool enabled;

public:


	infinite_jump( jobject playerobj, bool enabled )
	{
		this->playerobj = playerobj;
		this->enabled = enabled;
	}

	void work( );

};

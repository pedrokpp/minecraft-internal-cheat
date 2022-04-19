#pragma once
#include <jni.h>
#include <Windows.h>

#include "cheat.h"
#include "utils.h"
#include "player.h"

class autoarmor {

	player theplayer = nullptr;
	bool enabled;
	bool only_hotbar;

public:

	autoarmor( player theplayer, bool enabled, bool only_hotbar )
	{
		this->theplayer = theplayer;
		this->enabled = enabled;
		this->only_hotbar = only_hotbar;
	}

	void work( );

};

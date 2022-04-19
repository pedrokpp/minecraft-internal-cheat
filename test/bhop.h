#pragma once
#include <jni.h>
#include <Windows.h>

#include "cheat.h"
#include "utils.h"
#include "player.h"

class bhop {

	player theplayer = nullptr;
	bool enabled;
	float multiplier;

public:


	bhop( player theplayer, bool enabled, float multiplier )
	{
		this->theplayer = theplayer;
		this->enabled = enabled;
		this->multiplier = multiplier;
	}

	void work( );

};
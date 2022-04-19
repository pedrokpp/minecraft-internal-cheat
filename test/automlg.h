#pragma once
#include <jni.h>
#include <Windows.h>

#include "cheat.h"
#include "utils.h"
#include "player.h"

class automlg {

	player theplayer = nullptr;
	bool enabled;
	bool only_hotbar;
	float min_fall_distance;

public:

	automlg( player theplayer, bool enabled, bool only_hotbar, float min_fall_distance )
	{
		this->theplayer = theplayer;
		this->enabled = enabled;
		this->only_hotbar = only_hotbar;
		this->min_fall_distance = min_fall_distance;
	}

	void work( );

};

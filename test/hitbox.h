#pragma once
#include <jni.h>
#include <Windows.h>
#include <vector>

#include "cheat.h"
#include "utils.h"
#include "player.h"
#include "world.h"

using std::vector;

class hitbox {

	player theplayer = nullptr;
	world theworld = nullptr;
	bool enabled;
	double expander;

public:

	hitbox( player theplayer, world theworld, bool enabled, double expander )
	{
		this->theworld = theworld;
		this->theplayer = theplayer;
		this->enabled = enabled;
		this->expander = expander;
	}

	void work( );

};

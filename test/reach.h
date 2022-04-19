#pragma once
#include <jni.h>
#include <Windows.h>

#include "cheat.h"
#include "utils.h"
#include "player.h"

class reach {

	jobject playerobj;
	jobject minecraftobj;

	bool enabled;

	double reach_distance;

public:

	reach( jobject playerobj, jobject minecraftobj, bool enabled, double reach_distance )
	{
		reach::playerobj = playerobj;
		reach::minecraftobj = minecraftobj;
		reach::enabled = enabled;
		reach::reach_distance = reach_distance;
	}

	void work( );

};
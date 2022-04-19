#pragma once
#include <jni.h>
#include <Windows.h>
#include <vector>
#include "player.h"
#include "cheat.h"
#include "utils.h"

using cheat::env;

class world {

	jobject worldobj;

public:

	world( jobject worldobj )
	{
		world::worldobj = worldobj;
	}

	jobject get_jobject( )
	{
		return worldobj;
	}

	bool is_jobject_nullptr( )
	{
		return worldobj == nullptr;
	}

	std::vector<player> get_world_players( );
	player get_closest_player_to_theplayer( );

};
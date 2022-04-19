#pragma once
#include <jni.h>
#include <Windows.h>
#include "cheat.h"
#include "utils.h"

using cheat::env;

class minecraft {

	jobject minecraftobj;

public:

	minecraft( jobject minecraftobj )
	{
		minecraft::minecraftobj = minecraftobj;
	}

	jobject get_jobject( )
	{
		return minecraftobj;
	}

	void change_gamma( );
	jobject get_entity_mouse_over( );
	jobject get_timer_jobject( );

	~minecraft( )
	{
		env->DeleteLocalRef( minecraftobj );
	}

};
#pragma once
#include <jni.h>
#include <Windows.h>
#include <string>
#include "cheat.h"
#include "utils.h"

using cheat::env; using std::string;

class itemstack {

	jobject itemobj;

public:

	itemstack( jobject itemobj )
	{
		this->itemobj = itemobj;
	}

	jobject get_jobject( )
	{
		return this->itemobj;
	}

	string get_name( );
	
	jobject get_item( );

	int get_item_damage( );

};
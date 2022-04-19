#pragma once
#include <jni.h>
#include <Windows.h>
#include <vector>

#include "cheat.h"
#include "utils.h"
#include "minecraft.h"

using std::vector;

class timer {

	minecraft theminecraft = nullptr;
	bool enabled;
	float multiplier;

public:

	timer( minecraft theminecraft, bool enabled, float multiplier )
	{
		this->theminecraft = theminecraft;
		this->enabled = enabled;
		if ( multiplier <= 0 )
			this->multiplier = 1.0;
		else
			this->multiplier = multiplier;
	}

	void work( );

};

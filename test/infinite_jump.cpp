#include "pch.h"
#include "infinite_jump.h"

using cheat::env;

void infinite_jump::work() {
	if (!enabled && playerobj != nullptr)
		return;
	jclass playerclass = env->GetObjectClass(playerobj);
	jfieldID ongroundfid = env->GetFieldID(playerclass, "C", "Z");
	env->SetBooleanField(playerobj, ongroundfid, (jboolean)true);
}

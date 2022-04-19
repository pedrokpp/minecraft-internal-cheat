#include "pch.h"
#include "timer.h"

void timer::work( )
{
	if ( !enabled )
		return;
	jclass minecraftclass = env->GetObjectClass( theminecraft.get_jobject( ) );
	jfieldID timerfid = env->GetFieldID( minecraftclass, "Y", "Lavl;" );
	jobject timerobj = env->GetObjectField( theminecraft.get_jobject( ), timerfid );
	jclass timerclass = env->GetObjectClass( timerobj );
	jfieldID speedfid = env->GetFieldID( timerclass, "a", "F" );
	jfieldID tpsfid = env->GetFieldID( timerclass, "d", "F" );
	env->SetFloatField( theminecraft.get_timer_jobject( ), speedfid, ( jfloat ) multiplier );
	env->SetFloatField( theminecraft.get_timer_jobject( ), tpsfid, ( jfloat ) ( 20 * multiplier ) );
}
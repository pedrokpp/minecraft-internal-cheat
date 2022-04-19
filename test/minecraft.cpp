#include "pch.h"
#include "minecraft.h"

void minecraft::change_gamma( )
{
	jclass mcc = env->GetObjectClass( minecraftobj );
	jfieldID gmfid = env->GetFieldID( mcc, "t", "Lavh;" );
	jobject gmobj = env->GetObjectField( minecraftobj, gmfid );

	jclass gmclass = env->GetObjectClass( gmobj );
	jfieldID gammafid = env->GetFieldID( gmclass, "aJ", "F" );
	env->SetFloatField( gmobj, gammafid, ( jfloat ) 1000.0 );
}

jobject minecraft::get_entity_mouse_over( )
{
	jclass mcclass = env->GetObjectClass( minecraftobj );
	jfieldID obmfid = env->GetFieldID( mcclass, "s", "Lauh;" );
	jobject movingobj = env->GetObjectField( minecraftobj, obmfid );
	jclass movingclass = env->GetObjectClass( movingobj );
	jfieldID entityfid = env->GetFieldID( movingclass, "d", "Lpk;" );
	return env->GetObjectField( movingobj, entityfid );
}

jobject minecraft::get_timer_jobject( )
{
	jclass minecraftclass = env->GetObjectClass( minecraftobj );
	jfieldID timerfid = env->GetFieldID( minecraftclass, "Y", "Lavl;" );
	return env->GetObjectField( minecraftobj, timerfid );
}
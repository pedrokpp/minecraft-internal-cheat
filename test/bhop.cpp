#include "pch.h"
#include "bhop.h"

void bhop::work( )
{
	if ( !enabled )
	{
		jclass playerclass = env->GetObjectClass( theplayer.get_jobject( ) );
		jfieldID speedairfid = env->GetFieldID( playerclass, "bF", "F" );
		env->SetFloatField( theplayer.get_jobject( ), speedairfid, ( jfloat ) 0.02 );
		return;
	}
	jclass playerclass = env->GetObjectClass( theplayer.get_jobject( ) );
	jfieldID speedairfid = env->GetFieldID( playerclass, "bF", "F" );
	env->SetFloatField( theplayer.get_jobject( ), speedairfid, ( jfloat ) (0.02 * (6.0 + multiplier)) );
}
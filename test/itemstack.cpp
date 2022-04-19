#include "pch.h"
#include "itemstack.h"

string itemstack::get_name( )
{
	if ( itemobj == nullptr )
		return "air";
	jobject iobj = this->get_item( );
	jclass iiclass = env->GetObjectClass( iobj );
	jfieldID namefid = env->GetFieldID( iiclass, "l", "Ljava/lang/String;" );
	jstring str = ( jstring ) env->GetObjectField( iobj, namefid );
	if ( str == nullptr )
		return "block";
	return ( string ) env->GetStringUTFChars( str, 0 );
}

jobject itemstack::get_item( )
{
	if ( itemobj == nullptr )
		return nullptr;
	jclass iclass = env->GetObjectClass( itemobj );
	jfieldID ifid = env->GetFieldID( iclass, "d", "Lzw;" );
	return env->GetObjectField( itemobj, ifid );
}

int itemstack::get_item_damage( )
{
	if ( itemobj == nullptr )
		return -7;
	jfieldID ifid = env->GetFieldID( env->GetObjectClass( itemobj ), "f", "I" );
	return env->GetIntField( itemobj, ifid );
}
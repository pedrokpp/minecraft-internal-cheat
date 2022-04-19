#include "pch.h"
#include "world.h"

std::vector<player> world::get_world_players( )
{
	vector<player> response;

	jclass wclass = env->GetObjectClass( worldobj );
	jfieldID playersfid = env->GetFieldID( wclass, "j", "Ljava/util/List;" );
	jclass listclass = env->FindClass( "java/util/List" );
	jmethodID to_array_md = env->GetMethodID( listclass, "toArray", "()[Ljava/lang/Object;" );

	env->DeleteLocalRef( listclass );

	jobject objplayers = env->GetObjectField( worldobj, playersfid );
	jobjectArray arrayplayers = reinterpret_cast< jobjectArray >( env->CallObjectMethod( objplayers, to_array_md ) );

	size_t len = env->GetArrayLength( arrayplayers );

	player theplayer( cheat::get_player( ) );

	for ( int i = 0; i < len; ++i )
	{
		jobject pj = env->GetObjectArrayElement( arrayplayers, i );
		player p( pj );
		if ( p.get_entity_id( ) != theplayer.get_entity_id( ) )
			response.push_back( p );
	}

	return response;
}

player world::get_closest_player_to_theplayer( )
{
	player response = nullptr;
	player theplayer( cheat::get_player( ) );
	float dist = 100;
	for ( player p : get_world_players( ) )
	{
		float d = cheat::calc_distance_from_to_player( theplayer.get_jobject( ), p.get_jobject( ) );
		if ( d <= dist )
		{
			dist = d;
			response = p;
		}
	}

	return response;
}
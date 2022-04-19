#include "pch.h"
#include "hitbox.h"

using cheat::env;

void hitbox::work( )
{

	player p = theworld.get_closest_player_to_theplayer( );

	if ( !p.is_jobject_nullptr( ) )
	{
		if ( player::pidmap[ p.get_entity_id( ) ] == nullptr )
			player::pidmap[ p.get_entity_id( ) ] = p.get_jbounding_box( );
		return;
	}

	if ( !enabled )
		return;

	if ( p.is_jobject_nullptr( ) )
		return;

	jobject og_bbox = player::pidmap[ p.get_entity_id( ) ];
	if ( og_bbox == nullptr )
		return;

	jobject expanded_bbox = p.expand_jbounding_box( og_bbox, expander );
	p.set_jbounding_box( expanded_bbox );

}
#pragma once
#include <jni.h>
#include <Windows.h>
#include <iostream>
#include <unordered_map>
#include "cheat.h"
#include "utils.h"
#include "itemstack.h"

constexpr double PLAYER_WIDTH = 0.6;
constexpr double PLAYER_HEIGHT = 1.8;

using cheat::env; using std::unordered_map;

class player {

	jobject playerobj;
	jobject minecraftobj;

public:

	static unordered_map<int, jobject> pidmap;

	player( jobject playerobj, jobject minecraftobj )
	{
		player::playerobj = playerobj;
		player::minecraftobj = minecraftobj;
	};

	player( jobject playerobj )
	{
		player::playerobj = playerobj;
		player::minecraftobj = nullptr;
	};

	jobject get_jobject( )
	{
		return playerobj;
	}

	bool is_jobject_nullptr( )
	{
		return playerobj == nullptr;
	}

	jobject get_playercontroller_jobject( );

	bool is_blocking( );
	bool is_breaking_blocks( );
	bool is_moving( );
	bool is_sneaking( );

	void set_pitch( float pitch );

	jobject get_inventory_object( );

	itemstack get_current_item( );

	bool has_item_in_inventory( string name );
	bool has_item_in_hotbar( string name );
	int get_item_index_in_inventory( string name );
	bool check_armor_slot( int index );
	int get_current_item_index( );
	void use_current_item( );
	void use_item( itemstack istack );
	itemstack get_itemstack_in_inventory( string name );

	jobject get_world_jobject( );

	void set_item_in_hand( itemstack istack, int index, bool hotbar );

	float get_fall_distance( );

	int get_entity_id( );

	location get_location( );

	location* get_bounding_box( );
	jobject get_jbounding_box( );

	void set_bounding_box( location min, location max );
	void set_jbounding_box( jobject bboxobj );

	jobject expand_jbounding_box( jobject bboxobj, double expander );

	void autosprint( );

};
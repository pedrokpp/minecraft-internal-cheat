#include "pch.h"
#include "autoarmor.h"

void autoarmor::work( )
{
	if ( !enabled )
		return;

	if ( !theplayer.check_armor_slot( 0 ) ) // boots
	{
		bool should_work = only_hotbar ? theplayer.has_item_in_hotbar( "boots" ) : theplayer.has_item_in_inventory( "boots" );
		if ( should_work )
		{
			theplayer.set_item_in_hand( theplayer.get_itemstack_in_inventory( "boots" ), theplayer.get_current_item_index( ), false );
			theplayer.use_current_item( );
		}
	}

	if ( !theplayer.check_armor_slot( 1 ) ) // leggings
	{
		bool should_work = only_hotbar ? theplayer.has_item_in_hotbar( "leggings" ) : theplayer.has_item_in_inventory( "leggings" );
		if ( should_work )
		{
			theplayer.set_item_in_hand( theplayer.get_itemstack_in_inventory( "leggings" ), theplayer.get_current_item_index( ), false );
			theplayer.use_current_item( );
		}
	}

	if ( !theplayer.check_armor_slot( 2 ) ) // chestplate
	{
		bool should_work = only_hotbar ? theplayer.has_item_in_hotbar( "chestplate" ) : theplayer.has_item_in_inventory( "chestplate" );
		if ( should_work )
		{
			theplayer.set_item_in_hand( theplayer.get_itemstack_in_inventory( "chestplate" ), theplayer.get_current_item_index( ), false );
			theplayer.use_current_item( );
		}
	}

	if ( !theplayer.check_armor_slot( 3 ) ) // helmet
	{
		bool should_work = only_hotbar ? theplayer.has_item_in_hotbar( "helmet" ) : theplayer.has_item_in_inventory( "helmet" );
		if ( should_work )
		{
			theplayer.set_item_in_hand( theplayer.get_itemstack_in_inventory( "helmet" ), theplayer.get_current_item_index( ), false );
			theplayer.use_current_item( );
		}
	}

}
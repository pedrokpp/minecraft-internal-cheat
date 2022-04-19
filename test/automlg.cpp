#include "pch.h"
#include "automlg.h"

void automlg::work( )
{
	if ( !enabled )
		return;
	if ( theplayer.has_item_in_hotbar( "bucketWater" ) )
	{
		if ( theplayer.get_fall_distance( ) >= min_fall_distance )
		{
			theplayer.set_pitch( 90 );
			theplayer.set_item_in_hand( theplayer.get_itemstack_in_inventory( "bucketWater" ), theplayer.get_current_item_index( ), false );
			theplayer.use_current_item( );
		}
	}
}
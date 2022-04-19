#include "pch.h"
#include "player.h"
#include <iostream>

unordered_map<int, jobject> player::pidmap;

jobject player::get_playercontroller_jobject( )
{
	jclass mcclass = env->GetObjectClass( this->minecraftobj );
	jfieldID controllerfid = env->GetFieldID( mcclass, "c", "Lbda;" );
	return env->GetObjectField( this->minecraftobj, controllerfid );
}

void player::autosprint( )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jmethodID ismid = env->GetMethodID( playerclass, "aw", "()Z" );
	bool isSprinting = ( bool ) env->CallBooleanMethod( playerobj, ismid );
	if ( !isSprinting && is_moving( ) && !is_blocking( ) && !is_sneaking( ) )
	{
		jmethodID ssmid = env->GetMethodID( playerclass, "d", "(Z)V" );
		env->CallVoidMethod( playerobj, ssmid, ( jboolean ) true );
	}
}

bool player::is_moving( )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jfieldID zfid = env->GetFieldID( playerclass, "x", "D" );
	jfieldID xfid = env->GetFieldID( playerclass, "v", "D" );
	double z = ( double ) env->GetDoubleField( playerobj, zfid );
	double x = ( double ) env->GetDoubleField( playerobj, xfid );
	return !( ( z == 0.0 ) && ( x == 0.0 ) );
}

bool player::is_blocking( )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jmethodID blockmid = env->GetMethodID( playerclass, "bW", "()Z" );
	return ( bool ) env->CallBooleanMethod( playerobj, blockmid );
}

bool player::is_sneaking( )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jmethodID sneakingmid = env->GetMethodID( playerclass, "av", "()Z" );
	return ( bool ) env->CallBooleanMethod( playerobj, sneakingmid );
}

bool player::is_breaking_blocks( )
{
	jclass mcc = env->GetObjectClass( minecraftobj );
	jfieldID fid = env->GetFieldID( mcc, "s", "Lauh;" );
	jobject objectMouseOver = env->GetObjectField( minecraftobj, fid );

	if ( objectMouseOver != nullptr )
	{
		jclass objc = env->GetObjectClass( objectMouseOver );
		jmethodID objmid = env->GetMethodID( objc, "toString", "()Ljava/lang/String;" );
		jstring type = ( jstring ) env->CallObjectMethod( objectMouseOver, objmid );
		string strReturn = ( string ) env->GetStringUTFChars( type, 0 );
		string actualtype = strReturn.substr( 15, 15 );
		return ( actualtype == "BLOCK, blockpos" );
	}

	return true;
}

jobject player::get_inventory_object( )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jfieldID invfid = env->GetFieldID( playerclass, "bi", "Lwm;" );
	return env->GetObjectField( playerobj, invfid );
}

jobject player::get_world_jobject( )
{
	jfieldID fid = env->GetFieldID( env->GetObjectClass( this->playerobj ), "o", "Ladm;" );
	return env->GetObjectField( this->playerobj, fid );
}

itemstack player::get_current_item( )
{
	jobject invobj = this->get_inventory_object( );
	jmethodID gcmid = env->GetMethodID( env->GetObjectClass( invobj ), "h", "()Lzx;" );
	return itemstack( env->CallObjectMethod( invobj, gcmid ) );
}

void player::use_current_item( )
{
	jmethodID mid = env->GetMethodID( env->GetObjectClass( this->get_playercontroller_jobject( ) ), "a", "(Lwn;Ladm;Lzx;)Z" );
	env->CallBooleanMethod( this->get_playercontroller_jobject( ), mid, this->playerobj, this->get_world_jobject( ), this->get_current_item( ).get_jobject( ) );
}

void player::use_item( itemstack istack )
{
	jmethodID mid = env->GetMethodID( env->GetObjectClass( this->get_playercontroller_jobject( ) ), "a", "(Lwn;Ladm;Lzx;)Z" );
	env->CallBooleanMethod( this->get_playercontroller_jobject( ), mid, this->playerobj, this->get_world_jobject( ), istack.get_jobject( ) );
}

int player::get_current_item_index( )
{
	jobject playercontrollerobj = this->get_playercontroller_jobject( );
	jfieldID itemfid = env->GetFieldID( env->GetObjectClass( playercontrollerobj ), "j", "I" );
	return env->GetIntField( playercontrollerobj, itemfid );
}

int player::get_item_index_in_inventory( string name )
{
	jobject invobj = this->get_inventory_object( );
	jfieldID maininv_fid = env->GetFieldID( env->GetObjectClass( invobj ), "a", "[Lzx;" );
	jobjectArray inv_array = reinterpret_cast< jobjectArray >( env->GetObjectField( invobj, maininv_fid ) );

	// size_t len = env->GetArrayLength( inv_array );

	for ( int i = 0; i < 36; ++i )
	{
		jobject istackobj = env->GetObjectArrayElement( inv_array, i );
		itemstack istack( istackobj );
		if ( istack.get_name( ).find( name ) != string::npos )
			return i;
	}

	return -1;
}

itemstack player::get_itemstack_in_inventory( string name )
{
	jobject invobj = this->get_inventory_object( );
	jfieldID maininv_fid = env->GetFieldID( env->GetObjectClass( invobj ), "a", "[Lzx;" );
	jobjectArray inv_array = reinterpret_cast< jobjectArray >( env->GetObjectField( invobj, maininv_fid ) );

	// size_t len = env->GetArrayLength( inv_array );

	for ( int i = 0; i < 36; ++i )
	{
		jobject istackobj = env->GetObjectArrayElement( inv_array, i );
		itemstack istack( istackobj );
		if ( istack.get_name( ) == name )
			return istack;
	}

	return nullptr;
}

bool player::check_armor_slot( int index )
{
	jobject invobj = this->get_inventory_object( );
	jfieldID maininv_fid = env->GetFieldID( env->GetObjectClass( invobj ), "b", "[Lzx;" );
	jobjectArray inv_array = reinterpret_cast< jobjectArray >( env->GetObjectField( invobj, maininv_fid ) );

	jobject istackobj = env->GetObjectArrayElement( inv_array, index );

	return istackobj != nullptr;
}

bool player::has_item_in_hotbar( string name )
{
	int item_index = this->get_item_index_in_inventory( name );

	return (item_index >= 0 && item_index <= 8);
}

bool player::has_item_in_inventory( string name )
{
	int item_index = this->get_item_index_in_inventory( name );

	return item_index != -1;
}

void player::set_item_in_hand( itemstack istack, int index, bool hotbar )
{
	jobject invobj = this->get_inventory_object( );
	jmethodID setmid = env->GetMethodID( env->GetObjectClass( invobj ), "a", "(Lzw;IZZ)V" );
	env->CallVoidMethod( invobj, setmid, istack.get_item( ), ( jint ) istack.get_item_damage( ), ( jboolean ) true, ( jboolean ) hotbar );
}

void player::set_pitch( float pitch )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jfieldID pfid = env->GetFieldID( playerclass, "z", "F" );
	env->SetFloatField( playerobj, pfid, ( jfloat ) pitch );
}

float player::get_fall_distance( )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jfieldID pfid = env->GetFieldID( playerclass, "O", "F" );
	return env->GetFloatField( playerobj, pfid );
}

int player::get_entity_id( )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jfieldID idfid = env->GetFieldID( playerclass, "c", "I" );
	return env->GetIntField( playerobj, idfid );
}

location player::get_location( )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jfieldID xfid = env->GetFieldID( playerclass, "s", "D" );
	jfieldID yfid = env->GetFieldID( playerclass, "t", "D" );
	jfieldID zfid = env->GetFieldID( playerclass, "u", "D" );
	return location {
		env->GetDoubleField( playerobj, xfid ),
		env->GetDoubleField( playerobj, yfid ),
		env->GetDoubleField( playerobj, zfid )
	};
}

jobject player::get_jbounding_box( )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jfieldID bboxfid = env->GetFieldID( playerclass, "f", "Laug;" );
	return env->GetObjectField( playerobj, bboxfid );
}

location *player::get_bounding_box( )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jfieldID bboxfid = env->GetFieldID( playerclass, "f", "Laug;" );
	jobject bboxobj = env->GetObjectField( playerobj, bboxfid );

	jclass bboxclass = env->GetObjectClass( bboxobj );
	jfieldID minXfid = env->GetFieldID( bboxclass, "a", "D" );
	jfieldID maxXfid = env->GetFieldID( bboxclass, "d", "D" );

	jfieldID minYfid = env->GetFieldID( bboxclass, "b", "D" );
	jfieldID maxYfid = env->GetFieldID( bboxclass, "e", "D" );

	jfieldID minZfid = env->GetFieldID( bboxclass, "c", "D" );
	jfieldID maxZfid = env->GetFieldID( bboxclass, "f", "D" );

	location min {
	env->GetDoubleField( playerobj, minXfid ),
	env->GetDoubleField( playerobj, minYfid ),
	env->GetDoubleField( playerobj, minZfid )
	};
	location max {
	env->GetDoubleField( playerobj, maxXfid ),
	env->GetDoubleField( playerobj, maxZfid ),
	env->GetDoubleField( playerobj, maxYfid )
	};

	location locations[ ] = { min, max };

	return locations;
}

void player::set_jbounding_box( jobject bboxobj )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jfieldID bboxfid = env->GetFieldID( playerclass, "f", "Laug;" );
	env->SetObjectField( playerobj, bboxfid, bboxobj );
}

void player::set_bounding_box( location min, location max )
{
	jclass playerclass = env->GetObjectClass( playerobj );
	jfieldID bboxfid = env->GetFieldID( playerclass, "f", "Laug;" );
	jobject bboxobj = env->GetObjectField( playerobj, bboxfid );

	jclass bboxclass = env->GetObjectClass( bboxobj );
	jfieldID minXfid = env->GetFieldID( bboxclass, "a", "D" );
	jfieldID maxXfid = env->GetFieldID( bboxclass, "d", "D" );

	jfieldID minYfid = env->GetFieldID( bboxclass, "b", "D" );
	jfieldID maxYfid = env->GetFieldID( bboxclass, "e", "D" );

	jfieldID minZfid = env->GetFieldID( bboxclass, "c", "D" );
	jfieldID maxZfid = env->GetFieldID( bboxclass, "f", "D" );

	env->SetDoubleField( playerobj, minXfid, min.x );
	env->SetDoubleField( playerobj, maxXfid, max.x );

	env->SetDoubleField( playerobj, minYfid, min.y );
	env->SetDoubleField( playerobj, maxYfid, max.y );

	env->SetDoubleField( playerobj, minZfid, min.z );
	env->SetDoubleField( playerobj, maxZfid, max.z );
}

jobject player::expand_jbounding_box( jobject bboxobj, double expander )
{
	jclass bboxclass = env->GetObjectClass( bboxobj );
	jmethodID expandmid = env->GetMethodID( bboxclass, "b", "(DDD)Laug;" );
	return env->CallObjectMethod( bboxobj, expandmid, ( jdouble ) expander, ( jdouble ) expander, ( jdouble ) expander );
}
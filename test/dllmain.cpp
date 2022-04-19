#include "pch.h"
#include "cheat.h"

#include <iostream>
#include <Windows.h>
#include <string>
#include <random>
#include <jni.h>
#include <thread>
#include <chrono>

#include "hook.h"

#include "utils.h"

#include "player.h"
#include "world.h"
#include "minecraft.h"

#include "infinite_jump.h"
#include "hitbox.h"
#include "bhop.h"
#include "automlg.h"
#include "autoarmor.h"

HMODULE hModuleDLL;

using std::cout; using std::string; using namespace std::chrono;

void self( )
{
	hook::detach( );
	FreeLibraryAndExitThread( hModuleDLL, 0 );
}

DWORD WINAPI main( )
{
	if ( !cheat::attach( ) )
	{
		MessageBox( NULL, "could not attach to javaw", "ERROR", MB_ICONERROR | MB_OK );
		FreeLibraryAndExitThread( hModuleDLL, 0 );
		return EXIT_FAILURE;
	}

	if ( MH_Initialize( ) != MH_OK )
	{
		MessageBox( NULL, "can not initialize minhook", "ERROR", MB_ICONERROR | MB_OK );
		FreeLibraryAndExitThread( hModuleDLL, 0 );
		return EXIT_FAILURE;
	}

	if ( MH_CreateHookApi( L"Gdi32", "SwapBuffers", &hook::hk_swapbuffers, reinterpret_cast< LPVOID * >( &og_swapbuffers ) ) != MH_OK )
	{
		MessageBox( NULL, "could not create hook api", "ERROR", MB_ICONERROR | MB_OK );
		FreeLibraryAndExitThread( hModuleDLL, 0 );
		return EXIT_FAILURE;
	}

	if ( MH_EnableHook( MH_ALL_HOOKS ) != MH_OK )
	{
		MessageBox( NULL, "could not enable hooks", "ERROR", MB_ICONERROR | MB_OK );
		FreeLibraryAndExitThread( hModuleDLL, 0 );
		return EXIT_FAILURE;
	}

	auto placeholder_ms = duration_cast< milliseconds >(
		system_clock::now( ).time_since_epoch( )
		).count( );

	while ( true )
	{
		auto current_ms = duration_cast< milliseconds >(
			system_clock::now( ).time_since_epoch( )
			).count( );

		if ( current_ms - placeholder_ms >= 50 )
		{

			placeholder_ms = current_ms;

			jobject playerobj = cheat::get_player( );
			jobject worldobj = cheat::get_world( );
			jobject minecraftobj = cheat::get_minecraft( );

			if ( minecraftobj == nullptr )
			{
				MessageBox( NULL, "could not get minecraft instance", "ERROR", MB_ICONERROR | MB_OK );
				return EXIT_FAILURE;

			}

			minecraft theminecraft( minecraftobj );

			player theplayer( playerobj, minecraftobj );
			world theworld( worldobj );

			if ( !theplayer.is_jobject_nullptr( ) && !theworld.is_jobject_nullptr( ) )
			{

				if ( GetAsyncKeyState( VK_HOME ) & 0x8000 )
				{
					MessageBox( NULL, std::to_string( theplayer.check_armor_slot( 2 ) ).c_str( ), "", NULL );
					MessageBox( NULL, std::to_string( theplayer.get_item_index_in_inventory( "chestplate" ) ).c_str( ), "", NULL );
				}

				if ( hook::sprint_state )
					theplayer.autosprint( );

				infinite_jump ij_module( theplayer.get_jobject( ), hook::ij_state );
				bhop bhop_module( theplayer, hook::bhop_state, hook::bhop_value );
				hitbox hitbox_module( theplayer, theworld, hook::hitbox_state, hook::hitbox_value );
				automlg automlg_module( theplayer, hook::mlg_state, true, 4 );
				autoarmor autoarmor_module( theplayer, hook::autoarmor_state, hook::autoarmor_only_hotbar );
				

				ij_module.work( );
				bhop_module.work( );
				hitbox_module.work( );
				automlg_module.work( );
				autoarmor_module.work( );

			}

			if ( GetAsyncKeyState( VK_END ) & 0x8000 )
			{
				self( );
			}

		}

	}

}


BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch ( ul_reason_for_call )
	{
		case DLL_PROCESS_ATTACH:
			CreateThread( nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( main ), 0, 0, nullptr );
			hModuleDLL = hModule;
			break;
		case DLL_PROCESS_DETACH:
			Beep( 523, 150 );
			cheat::vm->DetachCurrentThread( );
			break;
	}
	return TRUE;
}


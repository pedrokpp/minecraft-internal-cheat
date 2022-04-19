#pragma once
#include "pch.h"
#include <Windows.h>
#include <chrono>
#include <string>
#include <mutex>

using std::string;

struct location {
	double x, y, z;
};

namespace utils
{

	struct context {
		HDC m_hdc_devicectx;
		HGLRC m_glrenderctx;
		HGLRC m_oglrenderctx;
	};

	inline void setup_console( )
	{
		FILE *pFile = nullptr;
		AllocConsole( );
		freopen_s( &pFile, "CONOUT$", "w", stdout );
	}

	inline int randint( int min, int max )
	{
		srand( time( 0 ) );
		return std::rand( ) % ( max + 1 - min ) + min;
	}

	inline void *get_proc_address( const char *name, void *handle )
	{
		auto p_procedure = GetProcAddress( reinterpret_cast< HMODULE >( handle ), name );
		return p_procedure;
	}

	inline void *get_module_handle( const char *name )
	{
		auto h_module = GetModuleHandleA( name );
		return h_module;
	}

	inline RECT get_window_rect( )
	{
		RECT res;
		GetWindowRect( FindWindow( "LWJGL", nullptr ), &res );
		return res;
	}

	inline static string get_window_title( )
	{
		char wnd_title[ 256 ];
		HWND hwnd = FindWindow( "LWJGL", nullptr );
		GetWindowText( hwnd, wnd_title, sizeof( wnd_title ) );
		return wnd_title;
	}

}
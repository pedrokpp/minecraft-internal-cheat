#pragma once
#include <Windows.h>
#include <shared_mutex>
#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_win32.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

#include <MinHook.h>

using std::string;

typedef LRESULT( CALLBACK *pWindowProc ) ( _In_ HWND   hwnd, _In_ UINT   uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam );
pWindowProc og_wnd_proc { nullptr };

extern auto ImGui_ImplWin32_WndProcHandler( HWND, UINT, WPARAM, LPARAM )->LRESULT;

decltype( &SwapBuffers ) og_swapbuffers;
WNDPROC org_wnd_proc { nullptr };

HDC hdc_device;

namespace hook
{
	bool is_gui_open = false, is_running = true;
	bool ij_state, sprint_state, bhop_state, hitbox_state, mlg_state, autoarmor_state;

	bool autoarmor_only_hotbar;
	float timer_value = 1.0;
	float bhop_value = 0.0;
	float hitbox_value = 0.0;

	inline auto detach( )
	{
		ImGui_ImplOpenGL2_Shutdown( );
		ImGui_ImplGlfw_Shutdown( );
		ImGui::DestroyContext( );
		MH_DisableHook( MH_ALL_HOOKS );
		MH_Uninitialize( );

		SetWindowLongPtrA( FindWindowA( "LWJGL", nullptr ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( org_wnd_proc ) );
	}

	inline auto hwnd_proc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) -> LRESULT WINAPI
	{
		if ( msg == WM_KEYDOWN && wparam == VK_INSERT )
			is_gui_open = !is_gui_open;

		if ( msg == WM_KEYDOWN && wparam == VK_END )
		{
			is_gui_open = false;
			is_running = false;
		}

		if ( is_gui_open && ImGui_ImplWin32_WndProcHandler( hwnd, msg, wparam, lparam ) )
			return 1l;

		return CallWindowProcA( og_wnd_proc, hwnd, msg, wparam, lparam );
	}

	inline void set_colors( )
	{
		ImColor mainColor = ImColor( int( 15 ), int( 135 ), int( 105 ), 255 );
		ImColor bodyColor = ImColor( int( 24 ), int( 24 ), int( 24 ), 255 );
		ImColor fontColor = ImColor( int( 255 ), int( 255 ), int( 255 ), 255 );

		ImGuiStyle &style = ImGui::GetStyle( );

		ImVec4 mainColorHovered = ImVec4( mainColor.Value.x + 0.1f, mainColor.Value.y + 0.1f, mainColor.Value.z + 0.1f, mainColor.Value.w );
		ImVec4 mainColorActive = ImVec4( mainColor.Value.x + 0.2f, mainColor.Value.y + 0.2f, mainColor.Value.z + 0.2f, mainColor.Value.w );
		ImVec4 menubarColor = ImVec4( bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w - 0.8f );
		ImVec4 frameBgColor = ImVec4( bodyColor.Value.x + 0.1f, bodyColor.Value.y + 0.1f, bodyColor.Value.z + 0.1f, bodyColor.Value.w + .1f );
		ImVec4 tooltipBgColor = ImVec4( bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .05f );

		style.Alpha = 1.0f;
		style.WindowPadding = ImVec2( 8, 8 );
		style.WindowMinSize = ImVec2( 32, 32 );
		style.WindowRounding = 0.0f;
		style.WindowTitleAlign = ImVec2( 0.5f, 0.5f );
		style.ChildRounding = 0.0f;
		style.FramePadding = ImVec2( 4, 3 );
		style.FrameRounding = 2.0f;
		style.ItemSpacing = ImVec2( 4, 3 );
		style.ItemInnerSpacing = ImVec2( 4, 4 );
		style.TouchExtraPadding = ImVec2( 0, 0 );
		style.IndentSpacing = 21.0f;
		style.ColumnsMinSpacing = 3.0f;
		style.ScrollbarSize = 8.f;
		style.ScrollbarRounding = 0.0f;
		style.GrabMinSize = 1.0f;
		style.GrabRounding = 0.0f;
		style.ButtonTextAlign = ImVec2( 0.5f, 0.5f );
		style.DisplayWindowPadding = ImVec2( 22, 22 );
		style.DisplaySafeAreaPadding = ImVec2( 4, 4 );
		style.AntiAliasedLines = true;
		style.CurveTessellationTol = 1.25f;

		style.Colors[ ImGuiCol_Text ] = fontColor;

		style.Colors[ ImGuiCol_TextDisabled ] = ImVec4( 0.24f, 0.23f, 0.29f, 1.00f );
		style.Colors[ ImGuiCol_WindowBg ] = bodyColor;
		style.Colors[ ImGuiCol_ChildBg ] = ImVec4( .0f, .0f, .0f, .0f );
		style.Colors[ ImGuiCol_PopupBg ] = tooltipBgColor;
		style.Colors[ ImGuiCol_Border ] = ImColor( 200, 200, 200, 220 );
		style.Colors[ ImGuiCol_BorderShadow ] = ImVec4( 0.92f, 0.91f, 0.88f, 0.00f );
		style.Colors[ ImGuiCol_FrameBg ] = frameBgColor;
		style.Colors[ ImGuiCol_FrameBgHovered ] = mainColorHovered;
		style.Colors[ ImGuiCol_FrameBgActive ] = mainColorActive;
		style.Colors[ ImGuiCol_TitleBg ] = mainColor;
		style.Colors[ ImGuiCol_TitleBgCollapsed ] = ImVec4( 1.00f, 0.98f, 0.95f, 0.75f );
		style.Colors[ ImGuiCol_TitleBgActive ] = mainColor;
		style.Colors[ ImGuiCol_MenuBarBg ] = menubarColor;
		style.Colors[ ImGuiCol_ScrollbarBg ] = ImVec4( frameBgColor.x + .05f, frameBgColor.y + .05f, frameBgColor.z + .05f, frameBgColor.w );
		style.Colors[ ImGuiCol_ScrollbarGrab ] = mainColor;
		style.Colors[ ImGuiCol_ScrollbarGrabHovered ] = mainColorHovered;
		style.Colors[ ImGuiCol_ScrollbarGrabActive ] = mainColorActive;
		style.Colors[ ImGuiCol_CheckMark ] = mainColor;
		style.Colors[ ImGuiCol_SliderGrab ] = mainColorHovered;
		style.Colors[ ImGuiCol_SliderGrabActive ] = mainColorActive;
		style.Colors[ ImGuiCol_Button ] = mainColor;
		style.Colors[ ImGuiCol_ButtonHovered ] = mainColorHovered;
		style.Colors[ ImGuiCol_ButtonActive ] = mainColorActive;
		style.Colors[ ImGuiCol_Header ] = mainColor;
		style.Colors[ ImGuiCol_HeaderHovered ] = mainColorHovered;
		style.Colors[ ImGuiCol_HeaderActive ] = mainColorActive;


		style.Colors[ ImGuiCol_ResizeGrip ] = mainColor;
		style.Colors[ ImGuiCol_ResizeGripHovered ] = mainColorHovered;
		style.Colors[ ImGuiCol_ResizeGripActive ] = mainColorActive;
		style.Colors[ ImGuiCol_PlotLines ] = mainColor;
		style.Colors[ ImGuiCol_PlotLinesHovered ] = mainColorHovered;
		style.Colors[ ImGuiCol_PlotHistogram ] = mainColor;
		style.Colors[ ImGuiCol_PlotHistogramHovered ] = mainColorHovered;
		style.Colors[ ImGuiCol_TextSelectedBg ] = ImVec4( 0.25f, 1.00f, 0.00f, 0.43f );
	}

	inline void TextCentered( string text )
	{
		auto windowWidth = ImGui::GetWindowSize( ).x;
		auto textWidth = ImGui::CalcTextSize( text.c_str( ) ).x;

		ImGui::SetCursorPosX( ( windowWidth - textWidth ) * 0.5f );
		ImGui::Text( text.c_str( ) );
	}

	inline auto create_window( const HDC hdc ) -> void
	{
		auto hwnd { FindWindowA( "LWJGL", nullptr ) };
		auto window_dc { WindowFromDC( hdc ) };

		RECT window;
		GetClientRect( window_dc, &window );

		static std::once_flag imgui_setup;

		std::call_once( imgui_setup, [ & ]( )
		{
			hdc_device = GetDC( hwnd );

			auto ogl_render = wglGetCurrentContext( );
			auto gl_render = wglCreateContext( hdc_device );
			ImGui::CreateContext( );
			set_colors( );
			if ( is_gui_open )
			{
				ImGui::GetIO( ).MouseDrawCursor = true;
				ImGui::GetIO( ).ConfigFlags &= ImGuiConfigFlags_NoMouse;
			}
			else
			{
				ImGui::GetIO( ).MouseDrawCursor = false;
				ImGui::GetIO( ).ConfigFlags |= ~ImGuiConfigFlags_NoMouse;
			}
			ImGui_ImplWin32_Init( hwnd );
			ImGui_ImplOpenGL2_Init( );
			ImGui::GetIO( ).IniFilename = nullptr;
			og_wnd_proc = reinterpret_cast< pWindowProc >( SetWindowLongPtrA( hwnd, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( hwnd_proc ) ) );
		} );

		if ( is_gui_open && is_running )
		{
			ImGui_ImplOpenGL2_NewFrame( );
			ImGui_ImplWin32_NewFrame( );

			ImGui::NewFrame( );
			{
				ImGui::Begin( "r$.", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar );
				ImGui::Checkbox( "Auto Sprint", &sprint_state );
				if ( ImGui::IsItemHovered( ) )
					ImGui::SetTooltip( "sprints automatically" );
				ImGui::Checkbox( "Infinite Jump", &ij_state );
				if ( ImGui::IsItemHovered( ) )
					ImGui::SetTooltip( "enables you jumping in the air" );
				ImGui::Checkbox( "AutoMLG", &mlg_state );
				if ( ImGui::IsItemHovered( ) )
					ImGui::SetTooltip( "only works when water bucket is in hotbar" );
				ImGui::Checkbox( "AutoArmor", &autoarmor_state );
				if ( ImGui::IsItemHovered( ) )
					ImGui::SetTooltip( "automatically sets armor to you" );
				if ( autoarmor_state )
				{
					ImGui::Text( "  " ); ImGui::SameLine( );
					ImGui::Checkbox( "only hotbar", &autoarmor_only_hotbar );
				}
				ImGui::NewLine( );
				ImGui::Checkbox( "Bunny Hop", &bhop_state );
				if ( ImGui::IsItemHovered( ) )
					ImGui::SetTooltip( "increases speed while jumping" );
				if ( bhop_state )
				{
					ImGui::SliderFloat( "speed multiplier", &bhop_value, 0, 1, "%.1f" );
					ImGui::NewLine( );
				}
				ImGui::Checkbox( "Hitbox", &hitbox_state );
				if ( ImGui::IsItemHovered( ) )
					ImGui::SetTooltip( "expand other player's hitbox" );
				if ( hitbox_state )
				{
					ImGui::SliderFloat( "expander", &hitbox_value, 0, 2, "%.1f" );
				}
				ImGui::NewLine( );
				TextCentered( "r$ version 0.1" );
				if ( ImGui::IsItemHovered( ) )
					ImGui::SetTooltip( "by kp" );
				ImGui::End( );
			}
			ImGui::Render( );

			glViewport( 0, 0, window.right, window.top );
			ImGui_ImplOpenGL2_RenderDrawData( ImGui::GetDrawData( ) );
		}

	}

	inline auto hk_swapbuffers( HDC hdc ) -> BOOL WINAPI
	{
		if ( hdc )
			create_window( hdc );

		return og_swapbuffers( hdc );
	}
}
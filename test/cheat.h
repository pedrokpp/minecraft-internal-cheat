#pragma once
#include "pch.h"
#include <jni.h>
#include <vector>

#include "utils.h"

using std::vector;

namespace cheat
{

	inline JNIEnv *env;
	inline JavaVM *vm;

	inline bool attach( )
	{
		auto jvm_dll = utils::get_module_handle( "jvm.dll" );

		auto created_java_vms = reinterpret_cast< jint( __stdcall * )( JavaVM **, jsize, jsize * ) >( utils::get_proc_address( "JNI_GetCreatedJavaVMs", jvm_dll ) );

		auto ret = created_java_vms( &vm, 1, nullptr );

		if ( ret != JNI_OK )
			return false;

		ret = vm->AttachCurrentThread( reinterpret_cast< void ** >( &env ), nullptr );

		if ( ret != JNI_OK )
			return false;

		vm->GetEnv( reinterpret_cast< void ** >( &env ), JNI_VERSION_1_6 );

		if ( !env )
			return false;

		if ( env == nullptr || vm == nullptr )
			return false;

		try
		{
			if ( env->FindClass( "ahahseaaaseehhpahhhepppes" ) == nullptr )
			{
				MessageBox( NULL, "could not get minecraft instance (might be using an unsupported version)", "ERROR", MB_ICONERROR | MB_OK );
				return false;
			}
			else
			{
				MessageBox( NULL, "got mc instance", "GOOD", MB_ICONINFORMATION | MB_OK );

			}
		}
		catch ( const std::exception & )
		{
			MessageBox( NULL, "could not get minecraft instance (might be using an unsupported version)", "ERROR", MB_ICONERROR | MB_OK );
			return false;
		}

		return true;
	}

	inline jobject get_minecraft( )
	{
		jclass mcclass = env->FindClass( "ave" );
		jfieldID mcfid = env->GetStaticFieldID( mcclass, "S", "Lave;" );
		return env->GetStaticObjectField( mcclass, mcfid );
	}

	inline jobject get_player( )
	{
		jclass mcclass = env->GetObjectClass( get_minecraft( ) );
		jfieldID pfid = env->GetFieldID( mcclass, "h", "Lbew;" );
		return env->GetObjectField( get_minecraft( ), pfid );
	}

	inline jobject get_world( )
	{
		jclass mcclass = env->GetObjectClass( get_minecraft( ) );
		jfieldID wfid = env->GetFieldID( mcclass, "f", "Lbdb;" );
		return env->GetObjectField( get_minecraft( ), wfid );
	}
	
	inline float calc_distance_from_to_player( jobject from, jobject to )
	{
		jclass fromclass = env->GetObjectClass( from );
		jmethodID distancemid = env->GetMethodID( fromclass, "g", "(Lpk;)F" );
		return env->CallFloatMethod( from, distancemid, to );
	}

	inline jobject get_current_screen( )
	{
		jfieldID fid = env->GetFieldID( env->GetObjectClass( get_minecraft( ) ), "m", "Laxu;" );
		return env->GetObjectField( get_minecraft( ), fid );
	}

}
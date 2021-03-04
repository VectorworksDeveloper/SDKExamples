//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// Define export and import flags for all libraries.
//

#ifndef _IMPORTANDEXPORTDEFINES_H_
#define _IMPORTANDEXPORTDEFINES_H_ 1

#pragma once

#if GS_INTERFACE_FACTORING

	/////////////////////////////////////////////////////////////////////////////////////
	// Define to 1 if building *.dll, 0 or undefine if building *.lib
	#if _WINDOWS
		#define GS_SHELL_DLL		0
		#define GS_COMP_DLL			0
		#define GS_CORE_DLL			0
		#define GS_PROTECTION_DLL	0
	#endif

	// If shell is a DLL, than either (or both) Core, Components or Protection better also be a DLL.
	#if GS_SHELL_DLL && !GS_CORE_DLL && !GS_COMP_DLL && !GS_PROTECTION_DLL
		#error If Application is a DLL, either Core, Components or Protection should also be a DLL.
	#endif


	/////////////////////////////////////////////////////////////////////////////////////
	// UI Shell (Application)

	#if GS_SHELL_DLL
		// Application is a DLL.
		#if GS_SHELL_BUILD
			// Building shell application.
			#define GS_SHELL_API			__declspec(dllexport)
		#else
			// Building a client of the shell application.
			#define GS_SHELL_API			__declspec(dllimport)
		#endif
	#else
		// Application shell is a LIB, no need to export or import anything.
		#define GS_SHELL_API
	#endif


	/////////////////////////////////////////////////////////////////////////////////////
	// Components

	#if GS_COMP_DLL
		// Components is a DLL.
		#if GS_COMP_BUILD
			// Building Components.
			#define GS_COMP_API			__declspec(dllexport)
		#else
			// Building a client of Components.
			#define GS_COMP_API			__declspec(dllimport)
		#endif
	#else
		// Components is a LIB, no need to export or import anything.
		#define GS_COMP_API
	#endif

	
	/////////////////////////////////////////////////////////////////////////////////////
	// Protection

	#if GS_PROTECTION_DLL
		// Protection is a DLL.
		#if GS_PROTECTION_BUILD
			// Building Components.
			#define GS_PROTECTION_API			__declspec(dllexport)
		#else
			// Building a client of Components.
			#define GS_PROTECTION_API			__declspec(dllimport)
		#endif
	#else
		// Components is a LIB, no need to export or import anything.
		#define GS_PROTECTION_API
	#endif
	/////////////////////////////////////////////////////////////////////////////////////
	// Core

	#if GS_CORE_DLL
		// Core is a DLL.
		#if GS_CORE_BUILD
			// Building Core.
			#define GS_CORE_API			__declspec(dllexport)
		#else
			// Building a client of Core.
			#define GS_CORE_API			__declspec(dllimport)
		#endif
	#else
		// Core is a LIB, no need to export or import anything.
		#define GS_CORE_API
	#endif


#else // GS_INTERFACE_FACTORING

	// UI Shell (Application)
	#define GS_SHELL_API

	// Components
	#define GS_COMP_API

	// Core
	#define GS_CORE_API

#endif // GS_INTERFACE_FACTORING


/////////////////////////////////////////////////////////////////////////////////////////
#if _WINDOWS
	#define MACAPI GS_COMP_API _stdcall
#else
	#define MACAPI pascal
#endif

#if _WINDOWS
    #define GS_HIDDEN_VISIBILITY
#else
    #define GS_HIDDEN_VISIBILITY __attribute__((visibility("hidden")))
#endif

#endif // _IMPORTANDEXPORTDEFINES_H_

//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "VWPluginLibraryArgTable.h"

// dispatch routine definition
#define		DEFINE_LIB_DISPATCH_MAP					virtual void DispatchRoutine(Sint32 routineSelector, VWPluginLibraryArgTable& argTable)
#define		BEGIN_LIB_DISPATCH_MAP(clas	)			void clas::DispatchRoutine(Sint32 routineSelector, VWPluginLibraryArgTable& argTable) { switch( routineSelector ) {
#define		ADD_LIB_FUNCTION(id, fun)					case id: this->fun( argTable ); break;
#define		END_LIB_DISPATCH_MAP						case -2: case -1: break; default: break; } }

// dispatch routine extended definition
#define		BEGIN_LIB_DISPATCH_MAP_Ex(clas,TArr)	void clas::DispatchRoutine(Sint32 routineSelector, VWPluginLibraryArgTable& argTable) { \
														if ( routineSelector < 0 ) return; \
														const SFunctionDef& funcDef = TArr[ routineSelector ];
#define		ADD_LIB_FUNCTION_Ex(funcName, fun)			if ( strcmp( funcDef.fName, funcName ) == 0 ) { this->fun( argTable ); return; }
#define		END_LIB_DISPATCH_MAP_Ex					}

namespace VWFC
{
	namespace PluginSupport
	{
		class VWPluginLibraryRoutine
		{
		public:
												VWPluginLibraryRoutine();
			virtual								~VWPluginLibraryRoutine();

		public:
			virtual void						SetUserData(SintptrT userData);
			virtual SintptrT					GetUserData() const;
			virtual void						DispatchRoutine(Sint32 routineSelector, VWPluginLibraryArgTable& argTable) = 0;

		// VCOM
		public:
			virtual VCOMError					RegisterInterfaces(void* pModule);
			virtual void						CreateInterfaceInstance(const VWIID& iid, IVWUnknown** ppOutInterface);
			virtual void						DeleteInterfaceInstance(const VWIID& iid, IVWUnknown* pInterface);
		};
	}
}
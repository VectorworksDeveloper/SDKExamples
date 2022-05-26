//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "VWFC/VWUI/StyleButtonCtrl.h"
#include "VWFC/Tools/DataSerializerSimple.h"


//const OSType kPluginStyleMapDataTag					= 'PSMP';


using namespace VWFC::VWUI;

namespace VWFC
{
	namespace VWObjects
	{
		// ------------------------------------------------------------------------------
		enum ESymbolDefType {
			kSymbolDefType_2D			= k2DSym,
			kSymbolDefType_3D			= k3DSym,
			kSymbolDefType_Hybrid		= kHybridSym
		};

		enum ESymbolInsertMode {
			kSymbolInsertMode_Edge						= kSymInsertOnEdge,
			kSymbolInsertMode_Center					= kSymInsertOnCenter,
			kSymbolInsertMode_LeftEdge					= kSymInsertOnLeftEdge,
			kSymbolInsertMode_RightEdge					= kSymInsertOnRightEdge,
			kSymbolInsertMode_CoreComponentCenter		= kSymInsertOnCoreComponentCenter,
			kSymbolInsertMode_CoreComponentLeftEdge		= kSymInsertOnCoreComponentLeftEdge,
			kSymbolInsertMode_CoreComponentRightEdge	= kSymInsertOnCoreComponentRightEdge
		};

		enum ESymbolBreakMode {
			kSymbolBreakMode_FullCaps		= kSymFullBreakWithCaps,
			kSymbolBreakMode_FullNoCaps		= kSymFullBreakNoCaps,
			kSymbolBreakMode_Half			= kSymHalfBreak,
			kSymbolBreakMode_None			= kSymNoBreak

		};


		// ------------------------------------------------------------------------------
		class VWSymbolDefObj : public VWGroupObj
		{
		public:
									VWSymbolDefObj(const TXString& symDefName);
									VWSymbolDefObj(MCObjectHandle hSymbolDef);
									VWSymbolDefObj(const VWSymbolDefObj& src);
			virtual					~VWSymbolDefObj();

			VWSymbolDefObj&			operator=(const VWSymbolDefObj& src);

		public:
			void					SetAsActiveSymbolDef();
			ESymbolDefType			GetType() const;

			ESymbolInsertMode		GetInsertMode() const;
			void					SetInsertMode(ESymbolInsertMode mode);
			ESymbolBreakMode		GetBreakMode() const;
			void					SetBreakMode(ESymbolBreakMode mode);

			bool					IsContainingLight() const;

			bool					GetInsertAsGroup() const;
			void					SetInsertAsGroup(bool bInsertAsGroup);

			// Makes a copy of the symbol's geometry and return a VWGroupObj of it
			VWGroupObj				GetSymbolGroup() const;

			bool					HasPluginStyleSupport() const;
			TInternalID				PluginStyleObjectID() const;
/*
			void					LoadPluginStyleMap();
			void					SavePluginStyleMap();
			
			void					SetPluginStyleParamaterStyleType( TXString & parmaName, EPluginStyleParameter paramType );
			EPluginStyleParameter	GetPluginStyleParameterStyleType( TXString & paramName );

			void					SetPluginStyleParamaterStyleType( Sint32 & parmaIndex, EPluginStyleParameter paramType );
			EPluginStyleParameter	GetPluginStyleParameterStyleType( Sint32 & parmaIndex );
*/

		// tool
		public:
			// Return true if the specified object handle is a symbol def
			static bool				IsSymbolDefObject(MCObjectHandle hObj);
			static bool				IsSymbolDefObject(const TXString& symDefName);
			static MCObjectHandle	GetActiveSymbolDef();

		};

	}
}
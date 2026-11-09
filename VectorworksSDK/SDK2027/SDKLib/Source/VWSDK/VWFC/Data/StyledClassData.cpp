//
//	Copyright Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

using namespace VWFC::Data;

CStyledClassData::CStyledClassData()
: fClassID(-1)
, fIsClassByStyle(false)
{}

CStyledClassData::~CStyledClassData()
{}

void CStyledClassData::LoadClassData(MCObjectHandle hObject)
{
	MCObjectHandle		hParentObj		= gSDK->ParentObject( hObject );
	short				type			= gSDK->GetObjectTypeN( hParentObj );
	if ( type == kSymDefNode )
	{
		fClassID					= this->GetClassFromStyle( hParentObj ); // class should be get from the SymDefNode
		fIsClassByStyle				= gSDK->GetClassByStyle( hObject );
	}
	else if ( gSDK->GetObjectTypeN( hObject ) != kFormatNode )
	{
		fClassID					= gSDK->GetObjectClass( hObject );
		fIsClassByStyle				= gSDK->GetClassByStyle( hObject );
	}
}

void CStyledClassData::SaveClassData(MCObjectHandle hObject)
{
	MCObjectHandle		hParentObj		= gSDK->ParentObject( hObject );
	short				type			= gSDK->GetObjectTypeN( hParentObj );
	if ( type == kSymDefNode )
	{
		gSDK->SetClassByStyle( 	hObject, fIsClassByStyle );
		if( fClassID == -1 ) // <Active class>
		{
			gSDK->SetObjectVariable( hParentObj, ovSymDefUseClass, TVariableBlock ((Boolean) false)		);
		}
		else
		{
			gSDK->SetObjectVariable(	hParentObj, ovSymDefUseClass, TVariableBlock ((Boolean) true)	);
			gSDK->SetObjectClass(		hParentObj,	fClassID											); // class should be set to SymDefNode in order to be translated to the instances
		}
	}
	else if ( gSDK->GetObjectTypeN( hObject ) != kFormatNode )
	{
		gSDK->SetClassByStyle( 	hObject,	fIsClassByStyle		);
		gSDK->SetObjectClass( 	hObject,	fClassID			);
	}
}

InternalIndex CStyledClassData::GetClassFromStyle(MCObjectHandle hSymDef)
{
	InternalIndex result = -1;
	if ( hSymDef )
	{
		TVariableBlock	value;
		gSDK->GetObjectVariable( hSymDef, ovSymDefUseClass, value );
		bool	hasAssocClass;
		result	= value.GetBoolean( hasAssocClass ) && hasAssocClass
				? gSDK->GetObjectClass( hSymDef )
				: -1; // <Active class>
	}
	return result;
}

void CStyledClassData::GetClassParamsFromSymDef(const TXString& styleName, bool& isClassByStyle, InternalIndex& classID)
{
	isClassByStyle = false;
	if( !styleName.IsEmpty() ) // has active style
	{
		MCObjectHandle hStyleSym = gSDK->GetNamedObject( styleName );

		if( VWSymbolDefObj::IsSymbolDefObject( hStyleSym ) )
		{
			VWSymbolDefObj			styleSym( hStyleSym );
			VWStyleSupport			styleSupport;

			if( styleSym.HasPluginStyleSupport() )
			{
				styleSupport.InitFromSymbolDefinition( styleSym );

				isClassByStyle	= gSDK->GetClassByStyle( styleSupport.GetStyleSourceObject() );
				classID			= GetClassFromStyle( hStyleSym );
			}
		}
	}
}

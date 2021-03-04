//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "LineObjSelection.h"

using namespace TesterModule;

// ------------------------------------------------------------------------------------------------------
CLineObjSelection::CLineObjSelection()
{
}

CLineObjSelection::~CLineObjSelection()
{
}

/*static*/ CLineObjSelection& CLineObjSelection::Instance()
{
	static CLineObjSelection s_Instance;
	return s_Instance;
}

bool CLineObjSelection::InitializeFromSelection()
{
	MCObjectHandle		hCurrLayer	= VWLayerObj::GetCurrentLayer();
	if ( hCurrLayer == NULL )
	{
		return	hCurrLayer;
	}

	fLineObj						= NULL;

	VWObjectIterator	itObj( gSDK->FirstMemberObj( hCurrLayer ) );
	while( *itObj )
	{
		VWObject		obj( *itObj );
		if ( obj.IsSelected() )	
		{
			if ( obj.GetType() == kLineNode )
			{
				fLineObj			= obj;
				break;
			}
		}
		itObj ++;
	}

	return	( fLineObj != NULL );
}

void CLineObjSelection::Clear()
{
	fLineObj	= NULL;
}

MCObjectHandle CLineObjSelection::Get() const
{
	return	fLineObj;
}
#include "StdAfx.h"

#include "UpdateSupport.h"
#include "DataPaneProvider_UpdateSupportSampleFormat.h"

using namespace Updater;

CUpdateSupport::CUpdateSupport(CallBackPtr)
{
}

CUpdateSupport::~CUpdateSupport()
{
}

void CUpdateSupport::Init(IObjUpdateSupportContext* pContext)
{
//	fOnState_WallObjIndex		= pContext->AcceptState2( kWallNode );
//	fOnState_RWallObjIndex		= pContext->AcceptState2( kRoundWallNode );
//	fOnState_SlabObjIndex		= pContext->AcceptState2( kSlabNode );
//	fOnState_LayerObjIndex		= pContext->AcceptState2( kLayerNode );
//	fOnState_Slab2ObjIndex		= pContext->AcceptState( "Slab" );
	fOnState_MyObjIndex			= pContext->AcceptState( "SampleUpdaterObj" );
	pContext->AcceptNotification( kNotifyUndoEndEvent );

//	pContext->AcceptWeilerOperations( "SampleUpdaterObj" );

//	pContext->AcceptNotification('Udee');

	// Register our data pane provider to be responsible for formats with the specified name
	pContext->AddDataPaneProvider( "Update Support Sample Format", IID_DataPaneProvider_UpdateSupportSampleFormat );
}

void CUpdateSupport::OnState(IObjUpdateSupportContext* pContext, const ObjectState& state)
{
	TParametricFileIndex	fileIndex	= pContext->GetFileIndex();
	MCObjectHandle			hObject		= pContext->GetObject();
	if ( fileIndex == fOnState_WallObjIndex )
	{
		TXString	msg;
		msg.Format( "Wall Object: state: %d  h: 0x%X", state.fSpecifier, hObject );
		gSDK->AlertInform( "CUpdateSupport::OnState", msg, false, "sample", "CUpdateSupport::OnState" );
	}
	else if ( fileIndex == fOnState_RWallObjIndex )
	{
		TXString	msg;
		msg.Format( "Round Wall Object: state: %d  h: 0x%X", state.fSpecifier, hObject );
		gSDK->AlertInform( "CUpdateSupport::OnState", msg, false, "sample", "CUpdateSupport::OnState" );
	}
	else if ( fileIndex == fOnState_SlabObjIndex )
	{
		TXString	msg;
		msg.Format( "Slab Object: state: %d  h: 0x%X", state.fSpecifier, hObject );
		gSDK->AlertInform( "CUpdateSupport::OnState", msg, false, "sample", "CUpdateSupport::OnState" );
	}
	else if ( fileIndex == fOnState_Slab2ObjIndex )
	{
		TXString	msg;
		msg.Format( "Slab Parametric Object: state: %d  h: 0x%X", state.fSpecifier, hObject );
		gSDK->AlertInform( "CUpdateSupport::OnState", msg, false, "sample", "CUpdateSupport::OnState" );
	}
	else if ( fileIndex == fOnState_LayerObjIndex )
	{
		TXString	msg;
		msg.Format( "Layer: state: %d  h: 0x%X", state.fSpecifier, hObject );
		gSDK->AlertInform( "CUpdateSupport::OnState", msg, false, "sample", "CUpdateSupport::OnState" );
	}
	else if ( fileIndex == fOnState_MyObjIndex )
	{
		TXString	msg;
		msg.Format( "SampleUpdaterObj: state: %d  h: 0x%X", state.fSpecifier, hObject );
		gSDK->AlertInform( "CUpdateSupport::OnState", msg, false, "sample", "CUpdateSupport::OnState" );

		if (	state.fSpecifier == ObjectState::kMovedReset 
			||	state.fSpecifier == ObjectState::kRotatedReset )
		{
			const ObjectStateData_Position*	theData	= (const ObjectStateData_Position*) state.fData;

			TransformMatrix		objMatrix;
			gSDK->GetEntityMatrix( hObject, objMatrix );

			objMatrix = objMatrix;
			theData = theData;
		}
		else
		{
			TransformMatrix		objMatrix;
			gSDK->GetEntityMatrix( hObject, objMatrix );

			objMatrix = objMatrix;
		}
	}
}

void CUpdateSupport::OnNotification(IObjUpdateSupportContext* pContext)
{
	StatusID	whichChange		= 0;
	StatusData	additionalData	= 0;
	pContext->GetNotification( whichChange, additionalData );

	char	buffer[ 5 ];
	buffer[3]	= (char) ((whichChange & 0x000000FF));
	buffer[2]	= (char) ((whichChange & 0x0000FF00) >> 1 * 8);
	buffer[1]	= (char) ((whichChange & 0x00FF0000) >> 2 * 8);
	buffer[0]	= (char) ((whichChange & 0xFF000000) >> 3 * 8);
	buffer[4]	= NULL;

	TXString	msg;
	msg.Format( "whichChange=%s. additionalData=0x%X", buffer, additionalData );
	gSDK->AlertInform( "CUpdateSupport::OnNotification", msg, false, "sample", "CUpdateSupport::OnNotification" );
}

#include "StdAfx.h"

#include "UpdateSupport.h"

using namespace TesterModule;

CUpdateSupport::CUpdateSupport(CallBackPtr)
{
}

CUpdateSupport::~CUpdateSupport()
{
}

void CUpdateSupport::Init(IObjUpdateSupportContext* pContext)
{
	fOnState_MyObjIndex		= pContext->AcceptState( "ProviderTestObj" );
	fOnWeiler_MyObjIndex	= pContext->AcceptWeilerOperations( "ProviderTestObj" );
	pContext->AcceptNotification( 'SELC' );
}

void CUpdateSupport::OnState(IObjUpdateSupportContext* pContext, const ObjectState& state)
{
	TParametricFileIndex	fileIndex	= pContext->GetFileIndex();
	MCObjectHandle			hObject		= pContext->GetObject();
	if ( fileIndex == fOnState_MyObjIndex ) {
		TXString	msg;
		msg.Format( "received state %d changed for 'ProviderTestObj' object instance 0x%X", state.fSpecifier, hObject );
		gSDK->AlertInform( "CUpdateSupport::OnState", msg, false, "sample", "CUpdateSupport::OnState" );
	}
}

void CUpdateSupport::OnNotification(IObjUpdateSupportContext* pContext)
{
	StatusID	whichChange		= 0;
	StatusData	additionalData	= 0;
	pContext->GetNotification( whichChange, additionalData );
	if ( whichChange == 'SELC' ) {
		TXString	msg;
		msg.Format( "relection changed in the document. additionalData=0x%X", additionalData );
		gSDK->AlertInform( "CUpdateSupport::OnNotification", msg, false, "sample", "CUpdateSupport::OnNotification" );
	}
}

EWeilerOperationResult CUpdateSupport::OnWeilerOperation(IObjUpdateSupportContext* pContext)
{
	TParametricFileIndex	fileIndex	= pContext->GetFileIndex();
	EWeilerClipAction		clipAction	= pContext->GetWeilerClipAction();
	EWeilerOperationResult	result		= eWeilerOperationResult_NotHandled;

	if ( fileIndex == fOnWeiler_MyObjIndex ) {
		// do we have what we think we have?

		TXString	msg;
		switch( clipAction ) {
			case eWeilerClipAction_Clip:
				msg	= "clipAction: eWeilerClipAction_Clip";
				break;
			case eWeilerClipAction_Union:
				msg	= "clipAction: eWeilerClipAction_Union";
				break;
			case eWeilerClipAction_Intersect:
				msg	= "clipAction: eWeilerClipAction_Intersect";
				break;
			default:
				msg	= "clipAction: unknown";
				break;
		}
		gSDK->AlertInform( "CUpdateSupport::OnWeilerOperation", msg );

		result		= eWeilerOperationResult_NotHandled;
	}

	return result;
}

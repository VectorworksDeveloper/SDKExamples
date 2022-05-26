//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC//PluginSupport/VWExtensions.h"
#include "VWFC//PluginSupport/VWExtensionTool.h"
#include "VWFC//PluginSupport/VWPluginToolProviders.h"

using namespace VWFC::PluginSupport;
using namespace VWFC::Math;

// --------------------------------------------------------------------------------------------------------
VWExtensionTool::VWExtensionTool(	CallBackPtr cbp,
									const SToolDef& toolDef)
	: fCBP( cbp )
	, fToolType			  ( toolDef.fToolType			  )
	, fPickAndUpdate	  ( toolDef.fPickAndUpdate	  	  )
	, fNeedScreenPlane	  ( toolDef.fNeedScreenPlane	  )
	, fNeed3DView		  ( toolDef.fNeed3DView		  	  )
	, fUseCursor		  ( toolDef.fUseCursor		  	  )
	, fConstrainCursor	  ( toolDef.fConstrainCursor	  )
	, fNeedPerspective	  ( toolDef.fNeedPerspective	  )
	, fShowScreenHints	  ( toolDef.fShowScreenHints	  )
	, fNeedsPlanarContext ( toolDef.fNeedsPlanarContext   )
	, fWaitMoveDistance	  ( toolDef.fWaitMoveDistance	  )
	, fConstraintFlags	  ( toolDef.fConstraintFlags	  )
	, fBarDisplay		  ( toolDef.fBarDisplay				)
	, fMinimumCompatibleVersion( toolDef.fMinimumCompatibleVersion	  )
	, fIconSpec			  ( toolDef.fIconSpec			  )
	, fCursorImageSpec	  ( toolDef.fCursorImageSpec	  )
	, fVersionCreated	  ( toolDef.fVersionCreated	  	  )
	, fVersoinModified	  ( toolDef.fVersoinModified	  )
	, fVersoinRetired	  ( toolDef.fVersoinRetired	  	  )
	, fToolEventSink( NULL )
	, fProtectionObtained( false )
	, fHasProtection( false )
	, fProtectionSink( NULL )
{
	gCBP			= fCBP;
	if ( toolDef.fTitle.fResNameWithoutPathOrExtension != 0 && toolDef.fTitle.fStringIdentifier != 0 )
	{
		fstrTitle = TXResStr( toolDef.fTitle.fResNameWithoutPathOrExtension, toolDef.fTitle.fStringIdentifier, eAllowEmptyResult );
	}
	if ( (toolDef.fCategory.fResNameWithoutPathOrExtension != 0) && (toolDef.fCategory.fStringIdentifier != 0) )
	{
		fstrCategory = TXResStr( toolDef.fCategory.fResNameWithoutPathOrExtension, toolDef.fCategory.fStringIdentifier, eAllowEmptyResult );
	}
	fstrMessage = TXResStr( toolDef.fMessage.fResNameWithoutPathOrExtension, toolDef.fMessage.fStringIdentifier, eAllowEmptyResult );

	fstrHelp = TXResStr( toolDef.fHelpText.fResNameWithoutPathOrExtension, toolDef.fHelpText.fStringIdentifier, eAllowEmptyResult );

	

	if ( toolDef.fParametricName ) {
		fstrParametricName	= toolDef.fParametricName;
	}

	if ( toolDef.fOverrideHelpID ) {
		fstrOverrideHelpID	= toolDef.fOverrideHelpID;
	}
}

VWExtensionTool::VWExtensionTool(	CallBackPtr cbp,
									const SToolDef_Legacy& toolDef)
	: fCBP( cbp )
	, fToolType			  ( toolDef.fToolType			  )
	, fPickAndUpdate	  ( toolDef.fPickAndUpdate	  	  )
	, fNeedScreenPlane	  ( toolDef.fNeedScreenPlane	  )
	, fNeed3DView		  ( toolDef.fNeed3DView		  	  )
	, fUseCursor		  ( toolDef.fUseCursor		  	  )
	, fConstrainCursor	  ( toolDef.fConstrainCursor	  )
	, fNeedPerspective	  ( toolDef.fNeedPerspective	  )
	, fShowScreenHints	  ( toolDef.fShowScreenHints	  )
	, fNeedsPlanarContext ( toolDef.fNeedsPlanarContext   )
	, fWaitMoveDistance	  ( toolDef.fWaitMoveDistance	  )
	, fConstraintFlags	  ( toolDef.fConstraintFlags	  )
	, fBarDisplay		  ( toolDef.fBarDisplay				)
	, fMinimumCompatibleVersion( toolDef.fMinimumCompatibleVersion	  )
	, fIconSpec			  ( toolDef.fIconSpec			  )
	, fCursorImageSpec	  ( toolDef.fCursorImageSpec	  )
	, fVersionCreated	  ( toolDef.fVersionCreated	  	  )
	, fVersoinModified	  ( toolDef.fVersoinModified	  )
	, fVersoinRetired	  ( toolDef.fVersoinRetired	  	  )
	, fToolEventSink( NULL )
	, fProtectionObtained( false )
	, fHasProtection( false )
	, fProtectionSink( NULL )
{
	gCBP			= fCBP;
	if ( toolDef.fTitle.fListID > 0 && toolDef.fTitle.fIndex > 0 )
	{
		fstrTitle = TXString(L"Bogus");
		fstrTitle = TXLegacyResource( toolDef.fTitle.fListID, toolDef.fTitle.fIndex, eAllowEmptyResult );
	}
	if ( (toolDef.fCategory.fListID > 0) && (toolDef.fCategory.fIndex > 0) )
	{
		fstrCategory = TXLegacyResource( toolDef.fCategory.fListID, toolDef.fCategory.fIndex, eAllowEmptyResult );
	}
	fstrMessage = TXLegacyResource( toolDef.fMessage.fListID, toolDef.fMessage.fIndex, eAllowEmptyResult );

	fstrHelp = TXLegacyResource( toolDef.fHelpText.fID );

	

	if ( toolDef.fParametricName ) {
		fstrParametricName	= toolDef.fParametricName;
	}

	if ( toolDef.fOverrideHelpID ) {
		fstrOverrideHelpID	= toolDef.fOverrideHelpID;
	}
}

VWExtensionTool::~VWExtensionTool()
{
}

void VWExtensionTool::OnRefCountZero()
{
	if ( fToolEventSink ) {
		delete fToolEventSink;
		fToolEventSink	= NULL;
	}

	if ( fProtectionSink ) {
		delete fProtectionSink;
		fProtectionSink	= NULL;
	}
}

bool VWExtensionTool::IsToolEventSink(const TSinkIID& iid)
{
	return IID_ToolEventSink == iid;
}

IEventSink* VWExtensionTool::QueryEventSink(const TSinkIID& iid)
{
	if ( fProtectionObtained == false ) {
		fHasProtection			= this->GetProtectionSinkIID( fProtectionSinkIID );
		fProtectionObtained		= true;
	}

	IEventSink*	pResult	= NULL;
	if ( this->IsToolEventSink( iid ) ) {
		if ( fToolEventSink == NULL ) {
			fToolEventSink	= this->CreateToolEventSink( this );
			fToolEventSink->AddRef();
			VWToolDefault_EventSink*	defaultSink	= dynamic_cast<VWToolDefault_EventSink*>( fToolEventSink );
			if ( defaultSink ) {
				defaultSink->Init( this->GetUniversalName() );
			}
			else {
				VWTool_EventSink*	vwfcSink	= dynamic_cast<VWTool_EventSink*>( fToolEventSink );
				if ( vwfcSink ) {
					vwfcSink->SetUniversalName( this->GetUniversalName() );
				}
			}
		}
		pResult	= fToolEventSink;
	}
	else if ( fHasProtection && fProtectionSinkIID == iid ) {
		if ( fProtectionSink == NULL ) {
			fProtectionSink	= this->CreateProtectionSink( this );
			if ( fProtectionSink == NULL ) {
				fHasProtection	= false;
			}
		}

		if ( fProtectionSink ) {
			fProtectionSink->AddRef();
			pResult	= fProtectionSink;
		}
	}

	return pResult;
}

bool VWExtensionTool::GetProtectionSinkIID(TSinkIID& outIID)
{
	return false;
}

IProviderProtection* VWExtensionTool::CreateProtectionSink(IVWUnknown* parent)
{
	return NULL;
}

EExtensionToolType VWExtensionTool::GetType()
{
	return fToolType;
}

const TXString& VWExtensionTool::GetTitle()
{
	return fstrTitle;
}

const TXString& VWExtensionTool::GetCategory()
{
	return fstrCategory;
}

const TXString& VWExtensionTool::GetHelpText()
{
	return fstrHelp;
}

const TXString& VWExtensionTool::GetMessageText()
{
	return fstrMessage;
}

const TXString& VWExtensionTool::GetOverrideHelpID()
{
	return fstrOverrideHelpID;
}

const TXString&	VWExtensionTool::GetParametricName()
{
	return fstrParametricName;
}

bool VWExtensionTool::GetPickAndUpdate()
{
	return fPickAndUpdate == ToolDef::pickAndUpdate;
}

bool VWExtensionTool::GetNeedScreenPlane()
{
	return fNeedScreenPlane == ToolDef::needsScreenPlane;
}

bool VWExtensionTool::GetNeed3DProjection()
{
	return fNeed3DView == ToolDef::needs3DView;
}

bool VWExtensionTool::GetUse2DCursor()
{
	return fUseCursor == ToolDef::use2DCursor;
}

bool VWExtensionTool::GetConstrainCursor()
{
	return fConstrainCursor == ToolDef::constrainCursor;
}

bool VWExtensionTool::GetNeedPerspective()
{
	return fNeedPerspective == ToolDef::needsPerspective;
}

bool VWExtensionTool::GetShowScreenHints()
{
	return fShowScreenHints == ToolDef::showScreenHints;
}

bool VWExtensionTool::GetNeedsPlanarContext()
{
	return fNeedsPlanarContext == ToolDef::needsPlanarContext;
} 

void VWExtensionTool::GetIconSpec(TXString& imageSpec)
{
	imageSpec = fIconSpec;
}

void VWExtensionTool::GetDefaultCursorImageSpec(TXString& imageSpec)
{
	imageSpec = fCursorImageSpec;
}

Sint16 VWExtensionTool::GetWaitMoveDistance()
{
	return fWaitMoveDistance;
}

Sint16 VWExtensionTool::GetConstraintFlags()
{
	return fConstraintFlags;
}

EToolBarDisplay VWExtensionTool::GetBarDisplay()
{
	return fBarDisplay;
}

Sint16 VWExtensionTool::GetMinimumCompatibleVersion()
{
	return fMinimumCompatibleVersion;
}

void  VWExtensionTool::GetVersionInfo(Uint16& outCreated, Uint16& outModified, Uint16& outRetired)
{
	outCreated		= fVersionCreated;
	outModified		= fVersoinModified;
	outRetired		= fVersoinRetired;
}

void VWExtensionTool::SetLocalizedTitle( const TXString& localizedTitle )
{
	if ( ! localizedTitle.IsEmpty() )
	{
		fstrTitle = localizedTitle;
	}
}

void VWExtensionTool::SetLocalizedCategory( const TXString& localizedCategory )
{
	if ( ! localizedCategory.IsEmpty() )
	{
		fstrCategory = localizedCategory;
	}
}

void VWExtensionTool::SetLocalizedHelpText( const TXString& localizedHelpText )
{
	if ( ! localizedHelpText.IsEmpty() )
	{
		fstrHelp = localizedHelpText;
	}
}

void VWExtensionTool::SetLocalizedMessage( const TXString& localizedMessage )
{
	if ( ! localizedMessage.IsEmpty() )
	{
		fstrMessage = localizedMessage;
	}
}

// --------------------------------------------------------------------------------------------------------
VWTool_EventSink::VWTool_EventSink(IVWUnknown* parent)
	: VCOMImpl<IToolEventSink>( parent )
{
	fMessage				= NULL;
	fpModeBarProvider		= NULL;
	fResult					= 0;
}

VWTool_EventSink::~VWTool_EventSink()
{
}

void VWTool_EventSink::SetUniversalName(const TXString& name)
{
	fUnivName	= name;
}

Sint32 VWTool_EventSink::Execute(ToolMessage* message)
{
	Sint32	reply	= 0;

	fMessage		= message;

	this->SetResult( 0 );

	//DMSG(( kVStanev, "VWFC::ToolMain: action=%d\n", action ));
	IToolModeBarProvider*	savedModeBarProvider	= fpModeBarProvider;

	CModeBarProvider	modeBarProvider;
	fpModeBarProvider		= & modeBarProvider;

	switch (message->fAction) {
		case ToolSetupMessage::kAction_SetUp: {
				CModeBarInitProvider	modeBarInitProvider;

				ToolSetupMessage*		theMessage = dynamic_cast<ToolSetupMessage*>( message );
				reply	= this->DoSetUp( theMessage->fFlag == kSetupSetdownPauseRestoreFlag, & modeBarInitProvider ) ? this->GetResult() : kToolCouldNotSetUp;
			} break;

		case ToolSetupMessage::kAction_SetDown: {
				CModeBarInitProvider	modeBarInitProvider;

				ToolSetupMessage*		theMessage = dynamic_cast<ToolSetupMessage*>( message );
				this->DoSetDown( theMessage->fFlag == kSetupSetdownPauseRestoreFlag, & modeBarInitProvider );
				reply	= this->GetResult();
			} break;

		case ToolMessage::kAction_DoDrawScrMod:
			this->DoDrawScrMod();
			reply	= this->GetResult();
			break;

		case ToolMessage::kAction_DoUndrawScrMod:
			this->DoUndrawScrMod();
			reply	= this->GetResult();
			break;

		case ToolInitXPropsMessage::kAction: {
				ToolInitXPropsMessage*		theMessage	= dynamic_cast<ToolInitXPropsMessage*>( message );

				CToolPropertiesProvider		propsProvider( theMessage ? theMessage->fCodeRefID : 0 );

				this->SetResult( 0 ); // start off with no errors
				this->OnInitXProperties( & propsProvider );
				reply	= this->GetResult();
			} break;

		case ToolMessage::kAction_OnSelectionChange:
			this->OnSelectionChange();
			reply	= this->GetResult();
			break;

		case CustomBarEventData::kAction: {
				CustomBarEventData* pEventData = dynamic_cast<CustomBarEventData*>( message );
				if ( pEventData ) {
					switch( pEventData->fCustomBarEventSelector ) {
						case kCustomBarSetup:
							this->OnCustomBar_Setup();
							break;
						case kCustomBarSetdown:
							this->OnCustomBar_Setdown();
							break;
						case kCustomBarUpdateValues:
							this->OnCustomBar_UpdateValues();
							break;
						case kCustomBarLockValue: {
							CustomBarLockValueData* pLockData = dynamic_cast<CustomBarLockValueData*>( pEventData->fData );
							if ( pLockData ) {
								this->OnCustomBar_LockValue( pLockData->fFieldIndex, pLockData->fUserLockString );
								this->OnCustomBar_LockValue( *pLockData );
							}
						}break;
						case kCustomBarUnlockValue: {
							this->OnCustomBar_UnlockValue( VERIFYN(kVStanev, pEventData->fData) ? pEventData->fData->fFieldIndex : NULL );

							CustomBarLockValueData* pLockData = dynamic_cast<CustomBarLockValueData*>( pEventData->fData );
							if ( pEventData )
								this->OnCustomBar_UnlockValue( *pLockData );
						}break;
					}
				}
				reply	= this->GetResult();
			} break;

		case ToolGetCursorMessage::kAction_GetCursor:
			{
				ToolGetCursorMessage* theMessage = dynamic_cast<ToolGetCursorMessage*>( message );
				if (theMessage)
				{
					this->GetCursorSpecifier( theMessage->fCursorImageSpec );
					reply = 0;
				}
			}
			break;

		case ToolMessage::kAction_GetStatus: {
				CStatusProvider	statusProvider;

				reply	= this->GetStatus( & statusProvider );
			} break;

		case ToolPointAddedMessage::kAction:
			this->PointAdded();
			reply	= this->GetResult();
			break;

		case ToolPointRemovedMessage::kAction:
			{
				ToolPointRemovedMessage*	theMessage	= dynamic_cast<ToolPointRemovedMessage*>( message );
				this->PointRemoved( theMessage ? (theMessage->fClearingAllPoints?true:false) : false );
				reply	= this->GetResult();
			}
			break;

		case ToolMessage::kAction_Draw: {
				CDrawProvider	drawProvider;
				this->Draw( & drawProvider);
				reply	= this->GetResult();
			} break;

		case ToolMessage::kAction_MouseMove:
			this->MouseMove();
			reply	= this->GetResult();
			break;

		case ToolCompleteMessage::kAction:
			this->HandleComplete();
			reply	= this->GetResult();
			break;

//			case kToolDoInterface:		// DEPRECATED
//				this->DoInterface( VWPoint2D( * ((WorldPt*)message1) ) );
//				break;

		case ToolModeMessage::kAction: {
				ToolModeMessage*	theMessage	= dynamic_cast<ToolModeMessage*>( message );

				size_t		groupID		= theMessage->message1 > 0 ? (size_t)(theMessage->message1) : 0;
				size_t		buttonID	= theMessage->message2 > 0 ? (size_t)(theMessage->message2) : 0;
				size_t		newButtonID	= buttonID & 0x0000FFFF;
				size_t		oldButtonID	= (buttonID & 0xFFFF0000) >> 16;

				if ( groupID > 0 )		groupID--;
				if ( newButtonID > 0 )	newButtonID--;
				if ( oldButtonID > 0 )	oldButtonID--;

				this->DoModeEvent( groupID, newButtonID, oldButtonID );
				reply	= this->GetResult();
			} break;

		case ToolMessage::kAction_DoDoubleClick:
			this->DoDoubleClick();
			reply	= this->GetResult();
			break;

		case ToolMessage::kAction_DrawingDoubleClick:
			this->SetResult( kToolSwitchToCursor );
			reply	= this->DrawingDoubleClick() ? kToolCompleted : this->GetResult();
			break;

		case ToolGenericStateChangeMessage::kAction:
			this->GenericStateChange();
			break;

		case ToolInitByObjectMessage::kAction: {
				ToolInitByObjectMessage*	theMessage	= dynamic_cast<ToolInitByObjectMessage*>( message );

				MCObjectHandle			hTheObject	= theMessage ? theMessage->fObject : NULL;;
				CModeBarInitProvider	modeBarInitProvider;

				this->OnToolInitByObject( hTheObject, & modeBarInitProvider );
			} break;

		case ToolMessage::kAction_OnViewChange:
			this->OnViewChange();
			break;

		default:
			reply = this->OnDefaultEvent( message );
			break;
	}

	// enforce help text if there is a custom one
	if ( ! fCustomHelpText.IsEmpty() )
	{
		gSDK->SetHelpString( fCustomHelpText );
	}

	// restore the mode provider
	fpModeBarProvider		= savedModeBarProvider;

	return reply;
}

Sint32 VWTool_EventSink::GetResult() const
{
	return fResult;
}

void VWTool_EventSink::SetResult(Sint32 result)
{
	fResult	= result;
}

void VWTool_EventSink::SetModeBarHelpText(const TXString& helpText)
{
	fCustomHelpText	= helpText;
}

void VWTool_EventSink::OnInitXProperties(IToolPropertiesProvider* pPropsProvider)
{
	this->Default();
}

void VWTool_EventSink::OnSelectionChange()
{
	this->Default();
}

void VWTool_EventSink::OnCustomBar_Setup()
{
	this->Default();
}

void VWTool_EventSink::OnCustomBar_Setdown()
{
	this->Default();
}

void VWTool_EventSink::OnCustomBar_UpdateValues()
{
	this->Default();
}

void VWTool_EventSink::OnCustomBar_LockValue(size_t fieldIndex, const TXString& userString)
{
	this->Default();
}

void VWTool_EventSink::OnCustomBar_UnlockValue(size_t fieldIndex)
{
	this->Default();
}

void VWTool_EventSink::OnCustomBar_LockValue(const CustomBarLockValueData& lockData)
{
	this->Default();
}

void VWTool_EventSink::OnCustomBar_UnlockValue(const CustomBarLockValueData& lockData)
{
	this->Default();
}


bool VWTool_EventSink::DoSetUp(bool bRestore, const IToolModeBarInitProvider* pModeBarInitProvider)
{
	this->Default();
	return true;
}

void VWTool_EventSink::DoSetDown(bool bRestore, const IToolModeBarInitProvider* pModeBarInitProvider)
{
	this->Default();
}

void VWTool_EventSink::DoDrawScrMod()
{
	this->Default();
}

void VWTool_EventSink::DoUndrawScrMod()
{
	this->Default();
}

void VWTool_EventSink::OnToolInitByObject(MCObjectHandle hObject, const IToolModeBarProvider* pModeBarInitProvider)
{
	this->Default();
}

void VWTool_EventSink::GetCursorSpecifier(TXString& cursorSpecifier)
{
	this->Default();
	cursorSpecifier = "Vectorworks/Cursors/SmallCrosshair.png";
}

TToolStatus VWTool_EventSink::GetStatus(const IToolStatusProvider* pStatusProvider)
{
	fResult	= pStatusProvider->GetOnePointToolStatus();
	this->Default();
	return fResult;
}

void VWTool_EventSink::PointAdded()
{
	this->Default();
}

void VWTool_EventSink::PointRemoved(bool bClearAllPts)
{
	this->Default();
}

void VWTool_EventSink::Draw(IToolDrawProvider* pDrawProvider)
{
	this->Default();
}

void VWTool_EventSink::MouseMove()
{
	this->Default();
}

void VWTool_EventSink::DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID)
{
	this->Default();
}

void VWTool_EventSink::DoDoubleClick()
{
	this->Default();
}

bool VWTool_EventSink::DrawingDoubleClick()
{
	this->Default();
	return true;
}

void VWTool_EventSink::GenericStateChange()
{
	this->Default();
}

size_t VWTool_EventSink::GetToolPointsCount() const
{
	return ::GS_GetNumToolPts( gCBP ); 
}

void VWTool_EventSink::ClearAllToolPoints()
{
	VWFC_VERIFY( ::GS_ClearAllToolPts( gCBP ) );
}

VWPoint2D VWTool_EventSink::GetToolPt2D(size_t ptIndex, bool includeCurrent) const
{
	WorldPt		pt;

	size_t ptsCnt = this->GetToolPointsCount();
	if ( ptsCnt == ptIndex && includeCurrent )
	{
		VWFC_VERIFY( ::GS_GetToolPtCurrent2D( gCBP, pt ) );
	}
	else
	{
		VWFC_ASSERT( ptIndex < ptsCnt );
		VWFC_VERIFY( ::GS_GetToolPt2D( gCBP, DemoteTo<Sint32>( kVStanev, ptIndex ), pt ) );
	}

	return pt;
}

VWPoint3D VWTool_EventSink::GetToolPt3D(size_t ptIndex, bool includeCurrent) const
{
	WorldPt3	pt;

	size_t ptsCnt = this->GetToolPointsCount();
	if ( ptsCnt == ptIndex && includeCurrent )
	{
		VWFC_VERIFY( ::GS_GetToolPtCurrent3D( gCBP, pt ) );
	}
	else
	{
		VWFC_ASSERT( ptIndex < this->GetToolPointsCount() );
		VWFC_VERIFY( ::GS_GetToolPt3D( gCBP, DemoteTo<Sint32>( kVStanev, ptIndex ), pt ) );
	}

	return pt;
}

bool VWTool_EventSink::GetToolPtCurren2D(VWPoint2D& outPt) const
{
	WorldPt		pt;
	bool		ok	= ::GS_GetToolPtCurrent2D( gCBP, pt );
	outPt			= pt;
	return ok;
}

bool VWTool_EventSink::GetToolPtCurren3D(VWPoint3D& outPt) const
{
	WorldPt3	pt;
	bool		ok	= ::GS_GetToolPtCurrent3D( gCBP, pt ) ? true : false;
	outPt			= pt;
	return ok;
}

bool VWTool_EventSink::PopLastToolPt()
{
	return GS_PopLastToolPt( gCBP ) ? true : false;
}

void VWTool_EventSink::RefreshModeBar()
{
	CModeBarProvider	modeBarInitProvider;
	if ( this->OnRefreshModeBar( & modeBarInitProvider ) )
	{
		gSDK->RefreshModeBar();
	}
}

/*static*/ void	VWTool_EventSink::DrawCrosshairHighlight(const WorldPt3& centerPt) 
{
	WorldPt screenCenter;
	gSDK->Project3DModelPtToScreen( centerPt, screenCenter );

	MCObjectHandle poly = gSDK->AddToolHighlightingPolyCreate();
	gSDK->SetPlanarRefID( poly, kPlanarRefID_ScreenPlane );
	gSDK->AddToolHighlightingPolyAddVertex( poly, WorldPt( screenCenter.x - 100	, screenCenter.y ) );
	gSDK->AddToolHighlightingPolyAddVertex( poly, WorldPt( screenCenter.x		, screenCenter.y + 100 ) );
	gSDK->AddToolHighlightingPolyAddVertex( poly, WorldPt( screenCenter.x + 100	, screenCenter.y ) );
	gSDK->AddToolHighlightingPolyAddVertex( poly, WorldPt( screenCenter.x		, screenCenter.y - 100 ) );
	gSDK->AddToolHighlightingPolyAddVertex( poly, WorldPt( screenCenter.x - 100	, screenCenter.y ) );
	gSDK->AddToolHighlightingPoly( poly, true );

	gSDK->AddToolHighlightingSegment( WorldPt( screenCenter.x		, screenCenter.y + 100 )
									, WorldPt( screenCenter.x		, screenCenter.y - 100 ) );
	gSDK->AddToolHighlightingSegment( WorldPt( screenCenter.x - 100	, screenCenter.y )
									, WorldPt( screenCenter.x + 100	, screenCenter.y ) );
}

bool VWTool_EventSink::OnRefreshModeBar(const IToolModeBarProvider* modeBarInitProvider)
{
	return false;
}

void VWTool_EventSink::OnViewChange()
{
}

/*
	extern "C" Boolean GS_CALLBACK GS_GetToolPtCurrentViewPt(CallBackPtr, ViewPt& outToolPt);
	//	Returns in outToolPt the current view space point. 
	extern "C" Boolean GS_CALLBACK GS_GetToolPtCurrentWorkingPlane(CallBackPtr, WorldPt3& outToolPt);
	//	Returns in outToolPt the current 3D working plane point. 
	extern "C" Boolean GS_CALLBACK GS_GetToolPtViewPoint(CallBackPtr, Sint32 inIndex, ViewPt& outToolPoint);
	//		Gets  the specified view space ToolPoint .  The index  is a zero based index .  False is returned if
	//		the index is out of range 0 <= index< GS_GetNumToolPoints.
	extern "C" Boolean GS_CALLBACK GS_GetToolPtWorkingPlane(CallBackPtr, Sint32 inIndex, WorldPt3& outToolPoint);
	//		Gets  the specified 3D working plane ToolPoint .  The index  is a zero based index .  False is
	//		returned if the index is out of range 0 <= index< GS_GetNumToolPoints.
*/
HotSpotRefID VWTool_EventSink::HotSpotAdd(HotSpotType type, const VWPoint3D& pt, const TXString& cursorSpec)
{
	return gSDK->AddHotSpotN(type, pt, cursorSpec, "", 0);
}


HotSpotRefID VWTool_EventSink::HotSpotAdd(HotSpotType type, const VWPoint3D& pt, const TXString& cursorSpec, const TXString& strTip)
{
	return gSDK->AddHotSpotN(type, pt, cursorSpec, strTip, 0);
}

HotSpotRefID VWTool_EventSink::HotSpotTrack(bool& bOutIs3D, VWPoint3D& outLocation)
{
	Boolean		is3d		= false;
	WorldPt3	location;
	HotSpotRefID		hotSpotID	= gSDK->TrackHotSpot( is3d, location );

	bOutIs3D				= is3d ? true : false;
	outLocation				= location;
	return hotSpotID;
}

void VWTool_EventSink::HotSpotRemove(HotSpotRefID hotSpotID)
{
	::GS_RemoveHotSpot( gCBP, hotSpotID );
}

void VWTool_EventSink::SetHotSpotColor(HotSpotRefID inHotSpotID, GSColor color)
{
	gSDK->SetHotSpotColor( inHotSpotID, color );
}

MCObjectHandleID VWTool_EventSink::SnapGeometryAdd(MCObjectHandle hSnapGeometry)
{
	return gSDK->AddToolSnapGeometry( hSnapGeometry );
}

void VWTool_EventSink::SnapGeometryRemove(MCObjectHandleID snapGeometryID)
{
	gSDK->RemoveToolSnapGeometry( snapGeometryID );
}

Sint32 VWTool_EventSink::OnDefaultEvent(ToolMessage* message)
{
	message;
	fResult	= 0;
	this->Default();
	return fResult;
}

void VWTool_EventSink::Default()
{
}

//////////////////////////////////////////////


// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------
VWToolEmpty_EventSink::VWToolEmpty_EventSink(IVWUnknown* parent)
	: VCOMImpl<IToolEventSink>( parent )
{
}

VWToolEmpty_EventSink::~VWToolEmpty_EventSink()
{
}

Sint32 VWToolEmpty_EventSink::Execute(ToolMessage* message)
{
	message;
	return 0;
}


// --------------------------------------------------------------------------------------------------------
VWToolDefault_EventSink::VWToolDefault_EventSink(IVWUnknown* parent, const TXString& objectName)
	: VWTool_EventSink( parent )
{
	fDataContext		= NULL;
	fObjectName			= objectName;
	fToolType			= eDefaultToolType_Point;
	fIsStandardTool		= true;
}

VWToolDefault_EventSink::~VWToolDefault_EventSink()
{
	ToolInitMessage		message( ToolInitMessage::kAction_Destroy, "" );
	gSDK->CallDefaultToolN( fToolType, fIsStandardTool, & message, fDataContext );
}

void VWToolDefault_EventSink::UpdatePreview()
{
	ToolDefaultPreviewUpdateMessage	message( NULL );
	gSDK->CallDefaultToolN( fToolType, fIsStandardTool, & message, fDataContext );
}

void VWToolDefault_EventSink::Init(const TXString& universalName)
{
	fUnivName	= universalName;
}

Sint32 VWToolDefault_EventSink::Execute(ToolMessage* message)
{
	SActionData	data;
	data.fMessage	= message;
	data.fhLastCreated = nullptr;
	fLastActions.push_back( data );

	Sint32	result	= VWTool_EventSink::Execute( message );

	fLastActions.pop_back();

	return result;
}

void VWToolDefault_EventSink::Draw(IToolDrawProvider* pDrawProvider)
{
	this->Default();
}

MCObjectHandle VWToolDefault_EventSink::GetLastCreated()
{
	MCObjectHandle result = nullptr;

	size_t	dataCnt	= fLastActions.size();
	if ( dataCnt > 0 )
	{
		SActionData&	data	= fLastActions[ dataCnt - 1 ];
		result = data.fhLastCreated;
	}

	return result;
}

void VWToolDefault_EventSink::HandleComplete()
{
	this->Default();
}

void VWToolDefault_EventSink::Default()
{
	size_t	dataCnt	= fLastActions.size();
	if ( dataCnt > 0 )
	{
		SActionData&	data	= fLastActions[ dataCnt - 1 ];

		Sint32 result	= gSDK->CallDefaultToolN( fToolType, fIsStandardTool, data.fMessage, fDataContext );

		dataCnt	= fLastActions.size();
		if ( dataCnt > 0 )
		{
			SActionData&	data	= fLastActions[ dataCnt - 1 ];
			if ( data.fMessage && (data.fMessage->fAction == ToolCompleteMessage::kAction || data.fMessage->fAction == ToolCompleteMessage::kAction_Create) )
			{
				ToolCompleteMessage* completeMsg = dynamic_cast<ToolCompleteMessage*>( data.fMessage );
				if ( completeMsg )
					data.fhLastCreated = completeMsg->fResultObject;
			}
		}
		
		this->SetResult( result );
	}
}

// --------------------------------------------------------------------------------------------------------
VWToolDefaultPoint_EventSink::VWToolDefaultPoint_EventSink(IVWUnknown* parent, const TXString& objectName)
	: VWToolDefault_EventSink( parent, objectName )
{
	fToolType		= eDefaultToolType_Point;
}

VWToolDefaultPoint_EventSink::~VWToolDefaultPoint_EventSink()
{
}

void VWToolDefaultPoint_EventSink::Init(const TXString& universalName)
{
	VWToolDefault_EventSink::Init( universalName );

	if ( ! fIsStandardTool ) {
		ToolInitMessage		message( ToolInitMessage::kAction_Init, fObjectName );
		message.fDefaultPointToolInfo	= & fVWToolInfo;
		gSDK->CallDefaultToolN( fToolType, false, & message, fDataContext );
	}
	else {
		ToolInitMessage		message( ToolInitMessage::kAction_Init, fObjectName );
		gSDK->CallDefaultToolN( fToolType, true, & message, fDataContext );
	}
}

const SDefaultPointToolInfo& VWToolDefaultPoint_EventSink::GetToolInfo() const
{
	return fToolInfo;
}

void VWToolDefaultPoint_EventSink::SetToolInfo(const SDefaultPointToolInfo& info)
{
	fToolInfo		= info;
	fVWToolInfo		= info;
	// due to legacy reasons the structure is 1-based
	// VWFC is 0-based, so compensate
	if ( fVWToolInfo.fModeGroup >= 0 )					fVWToolInfo.fModeGroup++;
	if ( fVWToolInfo.fAllowInsertGroup >= 0 )			fVWToolInfo.fAllowInsertGroup++;
	if ( fVWToolInfo.fAlignmentGroup >= 0 )				fVWToolInfo.fAlignmentGroup++;
	if ( fVWToolInfo.fSymbolResourceGroup >= 0 )		fVWToolInfo.fSymbolResourceGroup++;
	if ( fVWToolInfo.fRegularInsChoiceIndex >= 0 )		fVWToolInfo.fRegularInsChoiceIndex++;
	if ( fVWToolInfo.fOffsetInsChoiceIndex >= 0 )		fVWToolInfo.fOffsetInsChoiceIndex++;
	if ( fVWToolInfo.fPickUpChoiceIndex >= 0 )			fVWToolInfo.fPickUpChoiceIndex++;
	if ( fVWToolInfo.fLeftChoiceIndex >= 0 )			fVWToolInfo.fLeftChoiceIndex++;
	if ( fVWToolInfo.fCenterChoiceIndex >= 0 )			fVWToolInfo.fCenterChoiceIndex++;
	if ( fVWToolInfo.fRightChoiceIndex >= 0 )			fVWToolInfo.fRightChoiceIndex++;
	if ( fVWToolInfo.fNaturalChoiceIndex >= 0 )			fVWToolInfo.fNaturalChoiceIndex++;

	fIsStandardTool	= false;
}

Sint32 VWToolDefaultPoint_EventSink::Execute(ToolMessage* message)
{
	if ( ! fIsStandardTool )
	{
		if ( message->fAction == ToolSetupMessage::kAction_SetUp )
		{
			ToolSetupMessage*	theMessage	= dynamic_cast<ToolSetupMessage*>( message );
			theMessage->fDefaultPointToolInfo	= & fVWToolInfo;
		}
	}

	Sint32	result	= VWToolDefault_EventSink::Execute( message );

	return result;
}

// --------------------------------------------------------------------------------------------------------
VWToolDefaultLine_EventSink::VWToolDefaultLine_EventSink(IVWUnknown* parent, const TXString& objectName)
	: VWToolDefault_EventSink( parent, objectName )
{
	fToolType		= eDefaultToolType_Line;
}

VWToolDefaultLine_EventSink::~VWToolDefaultLine_EventSink()
{
}

void VWToolDefaultLine_EventSink::Init(const TXString& universalName)
{
	VWToolDefault_EventSink::Init( universalName );
	
	if ( ! fIsStandardTool ) {
		ToolInitMessage		message( ToolInitMessage::kAction_Init, fObjectName );
		message.fDefaultLineToolInfo	= & fVWToolInfo;
		gSDK->CallDefaultToolN( fToolType, false, & message, fDataContext );
	}
	else {
		ToolInitMessage		message( ToolInitMessage::kAction_Init, fObjectName );
		gSDK->CallDefaultToolN( fToolType, true, & message, fDataContext );
	}
}

const SDefaultLineToolInfo& VWToolDefaultLine_EventSink::GetToolInfo() const
{
	return fToolInfo;
}

void VWToolDefaultLine_EventSink::SetToolInfo(const SDefaultLineToolInfo& info)
{
	fToolInfo		= info;
	fVWToolInfo		= info;
	// due to legacy reasons the structure is 1-based
	// VWFC is 0-based, so compensate
	if ( fVWToolInfo.fModeGroup >= 0 )					fVWToolInfo.fModeGroup++;
	if ( fVWToolInfo.fConstrainedChoiceIndex >= 0 )		fVWToolInfo.fConstrainedChoiceIndex++;
	if ( fVWToolInfo.fUnconstrainedChoiceIndex >= 0 )	fVWToolInfo.fUnconstrainedChoiceIndex++;

	fIsStandardTool	= false;
}

Sint32 VWToolDefaultLine_EventSink::Execute(ToolMessage* message)
{
	if ( ! fIsStandardTool )
	{
		if ( message->fAction == ToolSetupMessage::kAction_SetUp )
		{
			ToolSetupMessage*	theMessage	= dynamic_cast<ToolSetupMessage*>( message );
			theMessage->fDefaultLineToolInfo	= & fVWToolInfo;
		}
	}

	Sint32	result	= VWToolDefault_EventSink::Execute( message );

	return result;
}


// --------------------------------------------------------------------------------------------------------
VWToolDefaultRect_EventSink::VWToolDefaultRect_EventSink(IVWUnknown* parent, const TXString& objectName)
	: VWToolDefault_EventSink( parent, objectName )
{
	fToolType		= eDefaultToolType_Rect;
}

VWToolDefaultRect_EventSink::~VWToolDefaultRect_EventSink()
{
}

void VWToolDefaultRect_EventSink::Init(const TXString& universalName)
{
	VWToolDefault_EventSink::Init( universalName );

	if ( ! fIsStandardTool ) {
		ToolInitMessage		message( ToolInitMessage::kAction_Init, fObjectName );
		message.fDefaultRectToolInfo	= & fVWToolInfo;
		gSDK->CallDefaultToolN( fToolType, false, & message, fDataContext );
	}
	else {
		ToolInitMessage		message( ToolInitMessage::kAction_Init, fObjectName );
		gSDK->CallDefaultToolN( fToolType, true, & message, fDataContext );
	}
}

const SDefaultRectToolInfo& VWToolDefaultRect_EventSink::GetToolInfo() const
{
	return fToolInfo;
}

void VWToolDefaultRect_EventSink::SetToolInfo(const SDefaultRectToolInfo& info)
{
	fToolInfo		= info;
	fVWToolInfo		= info;
	// due to legacy reasons the structure is 1-based
	// VWFC is 0-based, so compensate
	if ( fVWToolInfo.fModeGroup >= 0 )					fVWToolInfo.fModeGroup++;
	if ( fVWToolInfo.fCenterLineChoiceIndex >= 0 )		fVWToolInfo.fCenterLineChoiceIndex++;
	if ( fVWToolInfo.fEdgePlacementChoiceIndex >= 0 )	fVWToolInfo.fEdgePlacementChoiceIndex++;

	fIsStandardTool	= false;
}

Sint32 VWToolDefaultRect_EventSink::Execute(ToolMessage* message)
{
	if ( ! fIsStandardTool )
	{
		if ( message->fAction == ToolSetupMessage::kAction_SetUp )
		{
			ToolSetupMessage*	theMessage	= dynamic_cast<ToolSetupMessage*>( message );
			theMessage->fDefaultRectToolInfo	= & fVWToolInfo;
		}
	}

	Sint32	result	= VWToolDefault_EventSink::Execute( message );

	return result;
}


// --------------------------------------------------------------------------------------------------------
VWToolDefault2DPoly_EventSink::VWToolDefault2DPoly_EventSink(IVWUnknown* parent, const TXString& objectName)
	: VWToolDefault_EventSink( parent, objectName )
{
	fToolType		= eDefaultToolType_Poly2D;
}

VWToolDefault2DPoly_EventSink::~VWToolDefault2DPoly_EventSink()
{
}

void VWToolDefault2DPoly_EventSink::Init(const TXString& universalName)
{
	VWToolDefault_EventSink::Init( universalName );

	if ( ! fIsStandardTool ) {
		ToolInitMessage		message( ToolInitMessage::kAction_Init, fObjectName );
		message.fDefault2DPolyToolInfo	= & fVWToolInfo;
		gSDK->CallDefaultToolN( fToolType, false, & message, fDataContext );
	}
	else {
		ToolInitMessage		message( ToolInitMessage::kAction_Init, fObjectName );
		gSDK->CallDefaultToolN( fToolType, true, & message, fDataContext );
	}
}

const SDefault2DPolyToolInfo& VWToolDefault2DPoly_EventSink::GetToolInfo() const
{
	return fToolInfo;
}

void VWToolDefault2DPoly_EventSink::SetToolInfo(const SDefault2DPolyToolInfo& info)
{
	fToolInfo		= info;
	fVWToolInfo		= info;
	// due to legacy reasons the structure is 1-based
	// VWFC is 0-based, so compensate
	if ( fVWToolInfo.fModeGroup >= 0 )					fVWToolInfo.fModeGroup++;
	if ( fVWToolInfo.fFiletRadiusGroup >= 0 )			fVWToolInfo.fFiletRadiusGroup++;
	if ( fVWToolInfo.fCornerVertChoiceIndex >= 0 )		fVWToolInfo.fCornerVertChoiceIndex++;
	if ( fVWToolInfo.fBezierVertChoiceIndex >= 0 )		fVWToolInfo.fBezierVertChoiceIndex++;
	if ( fVWToolInfo.fCubicVertChoiceIndex >= 0 )		fVWToolInfo.fCubicVertChoiceIndex++;
	if ( fVWToolInfo.fTangetChoiceIndex >= 0 )			fVWToolInfo.fTangetChoiceIndex++;
	if ( fVWToolInfo.fPointOnArcChoiceIndex >= 0 )		fVWToolInfo.fPointOnArcChoiceIndex++;
	if ( fVWToolInfo.fArcVertChoiceIndex >= 0 )			fVWToolInfo.fArcVertChoiceIndex++;

	fIsStandardTool	= false;
}

MCObjectHandle VWToolDefault2DPoly_EventSink::DefaultHandleCreate()
{
	ToolCompleteMessage	message( ToolCompleteMessage::kAction_Create );
	if ( ! fIsStandardTool ) {
		gSDK->CallDefaultToolN( fToolType, false, & message, fDataContext );
	}
	else {
		gSDK->CallDefaultToolN( fToolType, true, & message, fDataContext );
	}

	return message.fResultObject;
}

Sint32 VWToolDefault2DPoly_EventSink::Execute(ToolMessage* message)
{
	if ( ! fIsStandardTool )
	{
		if ( message->fAction == ToolSetupMessage::kAction_SetUp )
		{
			ToolSetupMessage*	theMessage	= dynamic_cast<ToolSetupMessage*>( message );
			theMessage->fDefault2DPolyToolInfo	= & fVWToolInfo;
		}
	}

	Sint32	result	= VWToolDefault_EventSink::Execute( message );

	return result;
}


// --------------------------------------------------------------------------------------------------------
VWToolDefault3DPoly_EventSink::VWToolDefault3DPoly_EventSink(IVWUnknown* parent, const TXString& objectName)
	: VWToolDefault_EventSink( parent, objectName )
{
	fToolType		= eDefaultToolType_Poly3D;
}

VWToolDefault3DPoly_EventSink::~VWToolDefault3DPoly_EventSink()
{
}

void VWToolDefault3DPoly_EventSink::Init(const TXString& universalName)
{
	VWToolDefault_EventSink::Init( universalName );

	if ( ! fIsStandardTool ) {
		ToolInitMessage		message( ToolInitMessage::kAction_Init, fObjectName );
		message.fDefault3DPolyToolInfo	= & fVWToolInfo;
		gSDK->CallDefaultToolN( fToolType, false, & message, fDataContext );
	}
	else {
		ToolInitMessage		message( ToolInitMessage::kAction_Init, fObjectName );
		gSDK->CallDefaultToolN( fToolType, true, & message, fDataContext );
	}
}

const SDefault3DPolyToolInfo& VWToolDefault3DPoly_EventSink::GetToolInfo() const
{
	return fToolInfo;
}

void VWToolDefault3DPoly_EventSink::SetToolInfo(const SDefault3DPolyToolInfo& info)
{
	fToolInfo		= info;
	fVWToolInfo		= info;
	// due to legacy reasons the structure is 1-based
	// VWFC is 0-based, so compensate
	if ( fVWToolInfo.fModeGroup >= 0 )					fVWToolInfo.fModeGroup++;
	if ( fVWToolInfo.fNURBSDegSetGroup >= 0 )			fVWToolInfo.fNURBSDegSetGroup++;
	if ( fVWToolInfo.fNURBSByInterpChoiceIndex >= 0 )	fVWToolInfo.fNURBSByInterpChoiceIndex++;
	if ( fVWToolInfo.fNURBSByCtrlPtChoiceIndex >= 0 )	fVWToolInfo.fNURBSByCtrlPtChoiceIndex++;

	fIsStandardTool	= false;
}

Sint32 VWToolDefault3DPoly_EventSink::Execute(ToolMessage* message)
{
	if ( ! fIsStandardTool )
	{
		if ( message->fAction == ToolSetupMessage::kAction_SetUp )
		{
			ToolSetupMessage*	theMessage	= dynamic_cast<ToolSetupMessage*>( message );
			theMessage->fDefault3DPolyToolInfo	= & fVWToolInfo;
		}
	}

	Sint32	result	= VWToolDefault_EventSink::Execute( message );

	return result;
}



#include "StdHeaders.h"

#include "VWFC/VWUI/SymbolDisplayCtrl.h"



using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWSymbolDisplayCtrl::VWSymbolDisplayCtrl( TControlID id ) : VWControl( id, {eCompSymbolDisplay} )
{
}


VWSymbolDisplayCtrl::~VWSymbolDisplayCtrl( )
{
}


bool VWSymbolDisplayCtrl::CreateControl( VWDialog* pDlg, short width, short height, short margin )
{
	SymbolImgInfo imgInfoIn( width, height, margin, standardViewRightIso, renderSolid, EImageViewComponent::NotSet, ELevelsOfDetail::Medium, false /*scaleByZoom*/);
	gSDK->CreateSymbolDisplayControl( pDlg->GetControlID(), fControlID, TXString(),  imgInfoIn );

	return VWControl::CreateControl( pDlg );
}


void VWSymbolDisplayCtrl::Update( const TXString& resourceName, TRenderMode renderMode, TStandardView view )
{
	SymbolImgInfo imgInfoIn(view, renderMode, EImageViewComponent::NotSet, ELevelsOfDetail::Medium, false /*scaleByZoom*/);
	gSDK->UpdateSymbolDisplayControl( fpParentDlg->GetControlID(), fControlID, resourceName, imgInfoIn );
}

//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/PatternPopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWPatternPopupCtrl::VWPatternPopupCtrl(TControlID id)
: VWControl( id )
{
}

VWPatternPopupCtrl::~VWPatternPopupCtrl()
{
}

bool VWPatternPopupCtrl::CreateControl(VWDialog* pDlg)
{
	::GS_CreatePatternPopup( gCBP, pDlg->GetControlID(), fControlID );
	return VWControl::CreateControl( pDlg );
}

void VWPatternPopupCtrl::GetSelectedPattern(short& outPatternIndex, RGBColor& outForeColor, RGBColor& outBackColor) const
{
	short		foreColorIndex, backColorIndex;
	//ECO_REVISIT_VML Replace GS_ColorIndexToRGB call with new ColorRef-based call when available.
	::GS_GetPatternData( gCBP, fpParentDlg->GetControlID(), fControlID, outPatternIndex, foreColorIndex, backColorIndex );

	::GS_ColorIndexToRGB( gCBP, DemoteTo<ColorRef>(kSteve, foreColorIndex), outForeColor );
	::GS_ColorIndexToRGB( gCBP, DemoteTo<ColorRef>(kSteve, backColorIndex), outBackColor );
}

void VWPatternPopupCtrl::SetSelectedPattern(short patternIndex, const RGBColor& foreColor, const RGBColor& backColor)
{
	ColorRef		foreColorIndex, backColorIndex;
	//ECO_REVISIT_VML Replace GS_RGBToColorIndex call with new ColorRef-based call when available.
	::GS_RGBToColorIndex( gCBP, foreColor, foreColorIndex );
	::GS_RGBToColorIndex( gCBP, backColor, backColorIndex );

	::GS_SetPatternData( gCBP, fpParentDlg->GetControlID(), fControlID, patternIndex, foreColorIndex, backColorIndex );
}

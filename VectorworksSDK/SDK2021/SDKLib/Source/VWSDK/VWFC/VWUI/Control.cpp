//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/Control.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWControl::VWControl(TControlID id)
{
	fControlID			= id;
	fpParentDlg			= NULL;
}

VWControl::~VWControl()
{
}

bool VWControl::CreateControl(VWDialog* pDlg)
{
	fpParentDlg		= pDlg;
	return true;
}

void VWControl::AttachControl()
{
}

TControlID VWControl::GetControlID() const
{
	return fControlID;
}

void VWControl::NotifyEvent()
{
}

void VWControl::Enable(bool bEnable /*=true*/)
{
	::GS_EnableItem( gCBP, fpParentDlg->GetControlID(), fControlID, bEnable );
}

bool VWControl::IsEnabled(void) const
{
	return ::GS_IsItemEnabled( gCBP, fpParentDlg->GetControlID(), fControlID );
}

void VWControl::Show(bool bVisible /*=true*/)
{
	::GS_ShowItem( gCBP, fpParentDlg->GetControlID(), fControlID, bVisible );
}


bool VWControl::IsVisible(void) const
{
	return ::GS_IsItemVisible( gCBP, fpParentDlg->GetControlID(), fControlID );
}


void VWControl::Editable(bool bEditable)
{
	::GS_SetTextEditable( gCBP, fpParentDlg->GetControlID(), fControlID, bEditable );
}

void VWControl::SetControlText(const TXString& text)
{
	::GS_SetItemText( gCBP, fpParentDlg->GetControlID(), fControlID, text );
}

TXString VWControl::GetControlText()
{
	TXString	result;
	gSDK->GetItemText( fpParentDlg->GetControlID(), fControlID, result );
	return result;
}

void VWControl::SetControlText(short strListID, short strTextIndex)
{
	this->SetControlText( TXLegacyResource( strListID, strTextIndex ) );
}

void VWControl::SetHelpText(const TXString& text)
{
	::GS_SetHelpText( gCBP, fpParentDlg->GetControlID(), fControlID, text );
}

void VWControl::SetHelpText(short strListID, short strHelpIndex)
{
	this->SetHelpText( TXLegacyResource( strListID, strHelpIndex ) );
}

void VWControl::AlignLeftEdge(short alingID, EControlAlignMode mode)
{
	::GS_AlignLeftEdge( gCBP, fpParentDlg->GetControlID(), fControlID, alingID, (short) mode );
}

void VWControl::AlignRightEdge(short alingID, EControlAlignMode mode)
{
	::GS_AlignRightEdge( gCBP, fpParentDlg->GetControlID(), fControlID, alingID, (short) mode );
}

void VWControl::AlignBottomEdge(short alingID, EControlAlignMode mode)
{
	::GS_AlignBottomEdge( gCBP, fpParentDlg->GetControlID(), fControlID, alingID, (short) mode );
}

void VWControl::AlignColumnEdge(short alignID, EControlAlignMode mode)
{
	gSDK->AlignColumnEdge( fpParentDlg->GetControlID(), fControlID, alignID, (short)mode );
}

void VWControl::SetEdgeBinding(bool bBoundToLeft, bool bBoundToRight, bool bBoundToTop, bool bBoundToBottom)
{
	::GS_SetEdgeBinding( gCBP, fpParentDlg->GetControlID(), fControlID, bBoundToLeft, bBoundToRight, bBoundToTop, bBoundToBottom );
}

void VWControl::SetFocus()
{
	gSDK->SetFocusOnItem(fpParentDlg->GetControlID(), fControlID);
}

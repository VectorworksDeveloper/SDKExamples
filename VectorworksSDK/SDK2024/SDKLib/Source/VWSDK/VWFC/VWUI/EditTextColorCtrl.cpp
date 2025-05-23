//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include <regex>

using namespace VWFC::VWUI;

VWEditTextColorCtrl::VWEditTextColorCtrl(TControlID id)
: VWControl( id )
{
}

VWEditTextColorCtrl::~VWEditTextColorCtrl()
{
}

bool VWEditTextColorCtrl::CreateControl(VWDialog* pDlg, short widthInStdChar, short heightInLines)
{
	gSDK->CreateEditColorText( pDlg->GetControlID(), fControlID, widthInStdChar, heightInLines );
	return VWControl::CreateControl( pDlg );
}

TXString VWEditTextColorCtrl::GetText() const
{
	TXString	string;
	gSDK->GetItemText( fpParentDlg->GetControlID(), fControlID, string );
	return string;
}

void VWEditTextColorCtrl::SetText(const TXString& text)
{
	gSDK->SetItemText( fpParentDlg->GetControlID(), fControlID, text );
}

TXString VWEditTextColorCtrl::GetControlText()
{
	TXString	string;
	gSDK->GetItemText( fpParentDlg->GetControlID(), fControlID, string );
	return string;
}

void VWEditTextColorCtrl::SetControlText(const TXString& text)
{
	gSDK->SetItemText( fpParentDlg->GetControlID(), fControlID, text );
}

void VWEditTextColorCtrl::SelectContent()
{
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_SELECTALL;" );
}

void VWEditTextColorCtrl::DeselectContent()
{
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_SETSELECTIONSTART|int:0;" );
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_SETSELECTIONEND|int:0;" );
}

void VWEditTextColorCtrl::GetSelectionRange(Sint32& startPos, Sint32& endPos)
{
	VWVariant	a, b;
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_GETSELECTIONSTART:int;", & a );
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_GETSELECTIONEND:int;", & b );
	startPos	= a.GetSint32();
	endPos		= b.GetSint32();
}

void VWEditTextColorCtrl::SetSelectionRange(Sint32 startPos, Sint32 endPos)
{
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_SETSELECTIONSTART|int:%d;", startPos ) );
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_SETSELECTIONEND|int:%d;", endPos ) );
}

void VWEditTextColorCtrl::SetFocus()
{
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_SETFOCUS|int:1|int:1;" );
}

void VWEditTextColorCtrl::SetReadOnly(bool value)
{
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_SETREADONLY|int:1;" );
}

void VWEditTextColorCtrl::SetLineEnding(bool CR, bool LF)
{
	if ( CR && LF )
		gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_SETEOLMODE|int:0;" );
	else if ( CR )
		gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_SETEOLMODE|int:1;" );
	else if ( LF )
		gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_SETEOLMODE|int:2;" );
}

void VWEditTextColorCtrl::GoToLine(size_t line)
{
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_GOTOLINE|int:%d;", line ) );
}

void VWEditTextColorCtrl::GoToPos(size_t pos)
{
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_GOTOPOS|int:%d;", pos ) );
}

size_t VWEditTextColorCtrl::GetCurrLine()
{
	VWVariant	res;
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_GETCURRENTPOS:int;", & res );
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_LINEFROMPOSITION:int|int:%d;", res.GetSint32()), & res );
	return res.GetSint32();
}

size_t VWEditTextColorCtrl::GetCurrPos()
{
	VWVariant	res;
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_GETCURRENTPOS:int;", & res );
	return res.GetSint32();
}

size_t VWEditTextColorCtrl::GetLineFromPos(size_t pos)
{
	VWVariant	res;
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_LINEFROMPOSITION:int|int:%d;", pos), & res );
	return res.GetSint32();
}

size_t VWEditTextColorCtrl::GetTextLength()
{
	VWVariant	res;
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_GETLENGTH:int;", & res );
	return res.GetSint32();
}

void VWEditTextColorCtrl::ClearText()
{
	gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, "SCI_CLEARALL;" );
}

bool VWEditTextColorCtrl::SetStyle(const TXString& strStyle, VWVariant* outResult, VWVariant* outParam2)
{
	return gSDK->SetEditColorTextStyle( fpParentDlg->GetControlID(), fControlID, strStyle, outResult, outParam2 );
}

void VWEditTextColorCtrl::ApplyURLHighlightStyle()
{
	intptr_t styleNumber = 52;
	std::regex pattern("(https?|ftp)://\\S+");
	std::string text = this->GetText().GetStdString();
	std::sregex_iterator it(text.begin(), text.end(), pattern);
	std::sregex_iterator end;
	gSDK->SetEditColorTextStyle(fpParentDlg->GetControlID(), fControlID, "SCI_INDICSETSTYLE|int:INDIC_CONTAINER|int:INDIC_ROUNDBOX;");
    gSDK->SetEditColorTextStyle(fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_STYLESETCHANGABLE|int:%d|int:1;", styleNumber));
	gSDK->SetEditColorTextStyle(fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_STYLESETUNDERLINE|int:%d|int:1;", styleNumber));
    gSDK->SetEditColorTextStyle(fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_STYLESETBOLD|int:%d|int:1;", styleNumber));
	gSDK->SetEditColorTextStyle(fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_STYLESETFORE|int:%d|color:0, 0, 255;", styleNumber));
    gSDK->SetEditColorTextStyle(fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_STYLESETBACK|int:%d|color:255, 255, 0;", styleNumber));
	gSDK->SetEditColorTextStyle(fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_STYLESETHOTSPOT|int:%d|int:1;", styleNumber));
   
	while (it != end)
	{
		std::smatch match = *it;
		gSDK->SetEditColorTextStyle(fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_INDICATORFILLRANGE|int:%d|int:%d;", match.position(), match.str().length()));
		gSDK->SetEditColorTextStyle(fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_STARTSTYLING|int:%d|int:0;", match.position()));
		gSDK->SetEditColorTextStyle(fpParentDlg->GetControlID(), fControlID, TXString::Formatted("SCI_SETSTYLING|int:%d|int:%d;", match.str().length(), styleNumber));
       
		++it;
	}
}

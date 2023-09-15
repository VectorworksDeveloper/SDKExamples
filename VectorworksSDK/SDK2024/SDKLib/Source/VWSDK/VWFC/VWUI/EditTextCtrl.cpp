//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include "VWFC/VWUI/EditTextCtrl.h"


using namespace VWFC::VWUI;

VWEditTextCtrl::VWEditTextCtrl(TControlID id)
: VWControl( id )
{
}

VWEditTextCtrl::~VWEditTextCtrl()
{
}

bool VWEditTextCtrl::CreateControl(VWDialog* pDlg, const TXString& text, short widthInStdChar, short heightInLines/*=1*/)
{
	gSDK->CreateEditText( pDlg->GetControlID(), fControlID, text, widthInStdChar, heightInLines );
	return VWControl::CreateControl( pDlg );
}

TXString VWEditTextCtrl::GetText() const
{
	TXString	string;
	gSDK->GetItemText( fpParentDlg->GetControlID(), fControlID, string );
	return string;
}

void VWEditTextCtrl::SetText(const TXString& text)
{
	gSDK->SetItemText( fpParentDlg->GetControlID(), fControlID, text );
}

void VWEditTextCtrl::SelectContent()
{
	::GS_SelectEditText( gCBP, fpParentDlg->GetControlID(), fControlID );
}

void VWEditTextCtrl::DeselectContent()
{
	gSDK->DeselectEditText( fpParentDlg->GetControlID(), fControlID );
}

void VWEditTextCtrl::GetSelectionRange(Sint32& startPos, Sint32& endPos)
{
	gSDK->GetSelectionRange( fpParentDlg->GetControlID(), fControlID, startPos, endPos );
}

void VWEditTextCtrl::SetSelectionRange(Sint32& startPos, Sint32& endPos)
{
	gSDK->SetSelectionRange( fpParentDlg->GetControlID(), fControlID, startPos, endPos );
}

void VWEditTextCtrl::InsertText(const TXString& text, bool replaceSelectedText )
{
	TXString		currentText	= this->GetControlText();
	Sint32			offset		= 0;
	Sint32			startPos	= (Sint32)currentText.GetLength();
	Sint32			endPos		= startPos;

	if ( replaceSelectedText )
	{
		this->GetSelectionRange( startPos, endPos );
	}

#if GS_WIN
	//Calculate offset for New Line character that are counted two times on Windows
	TXString		newLineSym = VWTextBlockObj::GetNewLineSymbol();

	for ( size_t indx = 0, endIndx = startPos; indx < endIndx; indx++ )
	{
		if ( newLineSym.Find( currentText.GetAt( indx ) ) != -1 )
		{
			//correct the range from text block
			endIndx -= replaceSelectedText ? 1 : 0;
			offset++;
		}
	}

	if ( !replaceSelectedText )
	{
		//correct the carat to be at the end if there are New Lines
		startPos = endPos = startPos + offset;
	}
#endif // GS_WIN

	//Delete selected text if any
	currentText.Delete( startPos - offset, endPos - startPos );

	currentText.Insert( startPos - offset, text );

	this->SetText( currentText );

	//Place the carat at the end of the new definition
	Sint32 endDefinition = startPos + (Sint32)text.GetLength();
	this->SetSelectionRange( endDefinition, endDefinition );
}

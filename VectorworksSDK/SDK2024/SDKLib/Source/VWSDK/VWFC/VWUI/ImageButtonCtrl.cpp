#include "StdHeaders.h"

#include "VWFC/VWUI/ImageButtonCtrl.h"


using namespace VWFC::VWUI;

VWImageButtonCtrl::VWImageButtonCtrl( TControlID id ) : VWControl( id )
{
}


VWImageButtonCtrl::~VWImageButtonCtrl()
{
}


bool VWImageButtonCtrl::CreateControl( VWDialog* pDlg, const TXString& imageSpec, int buttonWidth )
{
	gSDK->CreateImageButton( pDlg->GetControlID(), fControlID, buttonWidth, imageSpec );
	
	return VWControl::CreateControl( pDlg) ;
}


bool VWImageButtonCtrl::UpdateImage( const TXString &imageSpec )
{
	return gSDK->UpdateImageButton( fpParentDlg->GetDialogID(), fControlID, imageSpec );
}

void VWImageButtonCtrl::SetIconPushButtonState(bool pressed)
{
	gSDK->SetIconPushButtonState( fpParentDlg->GetControlID(), fControlID, pressed );
}

bool VWImageButtonCtrl::GetIconPushButtonState() const
{
	Boolean pressed = false;
	gSDK->GetIconPushButtonState( fpParentDlg->GetControlID(), fControlID, pressed );
	return pressed ? true : false;
}

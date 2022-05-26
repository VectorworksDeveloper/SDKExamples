#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ImageButtonCtrl.h"

#include "VWFC/VWUI/Dialog.h"

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
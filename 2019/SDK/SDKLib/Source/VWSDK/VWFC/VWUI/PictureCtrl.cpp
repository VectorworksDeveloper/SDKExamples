//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/PictureCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;
using namespace VectorWorks::Filing;


VWPictureCtrl::VWPictureCtrl(TControlID id)
: VWControl( id )
{
}

VWPictureCtrl::~VWPictureCtrl()
{
}

bool VWPictureCtrl::CreateControl(VWDialog* pDlg, const TXString& imageSpec)
{
	gSDK->CreateImageControl2( pDlg->GetControlID(), fControlID, 0, 0, imageSpec );
	return VWControl::CreateControl( pDlg );
}

bool VWPictureCtrl::CreateControl(VWDialog* pDlg, Sint32 iWidthPixels, Sint32 iHeightPixels)
{
	gSDK->CreateImageControl( pDlg->GetControlID(), fControlID, iWidthPixels, iHeightPixels, NULL );
	return VWControl::CreateControl( pDlg );
}

void VWPictureCtrl::SetImage(const TXString& imageSpec)
{
	gSDK->UpdateImageControl2(fpParentDlg->GetControlID(), fControlID, imageSpec);
}

void VWPictureCtrl::SetImage(VectorWorks::UI::IIconPtr icon)
{
	gSDK->SetImageControlDataN(fpParentDlg->GetControlID(), fControlID, icon);
}

void VWPictureCtrl::SetImageUsingFullFilePath(IFileIdentifier* imgFileID)
{
	gSDK->UpdateImageControlUsingFullFilePath(fpParentDlg->GetControlID(), fControlID, imgFileID);
}


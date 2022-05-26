//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/StyleButtonCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWStyleButtonCtrl::VWStyleButtonCtrl(TControlID id)
: VWImageButtonCtrl( id )
{
}

VWStyleButtonCtrl::~VWStyleButtonCtrl()
{
}
/*
bool VWStyleButtonCtrl::CreateControl(VWDialog* pDlg, const TXString& text)
{
    gSDK->CreatePushButton( pDlg->GetControlID(), fControlID, text );
	return VWControl::CreateControl( pDlg );
}

bool VWStyleButtonCtrl::CreateControl( VWDialog* pDlg, const TXString& imageSpec, int buttonWidth = 1 )
{
	gSDK->CreateImageButton( pDlg->GetControlID(), fControlID, buttonWidth, imageSpec );
	return VWControl::CreateControl( pDlg );
}
*/
void VWStyleButtonCtrl::ClearAssociatedControls()
{
	fAssociatedControls.clear();
}

void VWStyleButtonCtrl::ClearAssoicatedParameters()
{
	fAssociatedParameters.clear();
}

void VWStyleButtonCtrl::SetIconPushButtonImage(const TXString& imageSpec)
{
	gSDK->UpdateImageButton( fpParentDlg->GetControlID(), fControlID, imageSpec );
}


EPluginStyleParameter VWStyleButtonCtrl::GetStyleType()
{
	return fStyleType;
}


void VWStyleButtonCtrl::SetParameterName( const TXString & parameterName )
{
	fParameterName = parameterName;
}

TXString VWStyleButtonCtrl::GetParameterName()
{
	return fParameterName;
}

void VWStyleButtonCtrl::SetStyleType( EPluginStyleParameter type )
{
	fStyleType = type;

	TXString helpText;
	TXString imageSpec = "VWMiscSmallImages/";
	
	switch ( type ) {
		case kPluginStyleParameter_ByInstance :
			imageSpec += "ByInst.png";	
			break;

		case kPluginStyleParameter_ByStyle:
			imageSpec += "ByStyle.png";	
			break;

		case kPluginStyleParameter_ByCatalog:
			imageSpec += "ByCatalog.png";
			break;

		default:
			break;
	}

	this->SetIconPushButtonImage( imageSpec );
	
}

void VWStyleButtonCtrl::AddAssociatedControl( TControlID id )
{
	fAssociatedControls.push_back( id );
}

TControlID VWStyleButtonCtrl::GetPrimaryAssoicatedControl()
{
	TControlID returnID = 0;

	if ( fAssociatedControls.size() > 0 )  {
		returnID = fAssociatedControls[0];
	}

	return returnID;
}

void VWStyleButtonCtrl::UpdateAssociatedControls(bool allowEnabling /*= true*/)
{
	if ( fAssociatedControls.size() > 0 )
	{
		const TControlID	dlgID	= fpParentDlg->GetControlID();
		const bool			enable	= fStyleType == kPluginStyleParameter_ByInstance;
		for ( const auto& associatedControl : fAssociatedControls )
		{
			if ( !enable || allowEnabling )
			{
				gSDK->EnableItem( dlgID, associatedControl, enable );
			}
		}
	}
}

void VWStyleButtonCtrl::EnableAssociatedControls( bool enable)
{
	if ( fAssociatedControls.size() > 0 ) {
		TControlID dlgID = fpParentDlg->GetControlID();
		for ( size_t i = 0; i < fAssociatedControls.size(); i++ ) {
			gSDK->EnableItem( dlgID, fAssociatedControls[ i ], enable );
		}
	}
}

void VWStyleButtonCtrl::AddAssociatedParameter( const TXString& addedParameter )
{
	fAssociatedParameters.push_back( addedParameter );
}


size_t VWStyleButtonCtrl::NumberofAssoicatedParameters()
{
	return fAssociatedParameters.size();
}

TXString VWStyleButtonCtrl::GetAssociatedParameter( size_t index )
{
	TXString paramName;
	paramName.Clear();

	if ( index < fAssociatedParameters.size() ) {
		paramName = fAssociatedParameters[index];
	}

	return paramName;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
VWStyleGroupButtonCtrl::VWStyleGroupButtonCtrl(TControlID id)
: VWControl( id )
{
}

VWStyleGroupButtonCtrl::~VWStyleGroupButtonCtrl()
{
}

bool VWStyleGroupButtonCtrl::CreateControl(VWDialog* pDlg, const TXString& text)
{
	gSDK->CreatePushButton( pDlg->GetControlID(), fControlID, text );
	return VWControl::CreateControl( pDlg );
}

Sint32 VWStyleGroupButtonCtrl::GetGroupID()
{
	return fGroupID;
}

void VWStyleGroupButtonCtrl::SetGroupID( Sint32 groupID )
{
	fGroupID = groupID;
}

void VWStyleGroupButtonCtrl::SetStyleGroupType( EPluginStyleGroup type )
{
	fStyleGroupType = type;

	TXString imageSpec = "VWMiscSmallImages/";
	TXString helptext;

	switch ( type ) {
		case kPluginStyleGroup_ByInstance :
			imageSpec += "ByInst.png";	
			helptext = TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "StyleGroupAllByInstance" );
			break;

		case kPluginStyleGroup_ByStyle:
			imageSpec += "ByStyle.png";	
			helptext = TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "StyleGroupAllByStyle" );
			break;

		case kPluginStyleGroup_Mixed:
			imageSpec += "ByMixed.png"; 
			helptext = TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "StyleGroupMixed" );
			break;

		default:
			break;
	}

	Sint32 dlgID = fpParentDlg->GetControlID();
	gSDK->UpdateImageButton( dlgID, fControlID, imageSpec );
	this->SetHelpText( helptext );
	if ( fTextControlID > 0 ) {
		gSDK->SetHelpText( dlgID, fTextControlID, helptext );

	}
}

EPluginStyleGroup VWStyleGroupButtonCtrl::GetStyleGroupType()
{
	return fStyleGroupType;
}

void VWStyleGroupButtonCtrl::SetTextControlID( TControlID textContrlID )
{
	if ( textContrlID > 0 ) {
		fTextControlID = textContrlID;
	}
}


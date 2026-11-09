#include "StdAfx.h"

#include "DlgResourcePopupSample.h"

// dialog control IDs
#define		kOK                   1
#define		kCancel               2
#define		kTxtLine1             4
#define		kTxtLine2             5
#define		kImagePopup           6

using namespace ResourcePopup;

EVENT_DISPATCH_MAP_BEGIN( CDlgResourcePopupSample );
EVENT_DISPATCH_MAP_END;

CDlgResourcePopupSample::CDlgResourcePopupSample(VectorWorks::Extension::IResourceManagerContentPtr content)
	: fContent( content )
{
	// Assign settings tag to this dialog so it would save it's position and size automatically
	this->SetSavedSettingsTag( "TesterModule", "DlgResourcePopupSample" );
}

CDlgResourcePopupSample::~CDlgResourcePopupSample()
{
}

bool CDlgResourcePopupSample::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "TesterModule/DialogLayout/DlgResourcePopupSample.vs" );
}

void CDlgResourcePopupSample::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	VWImagePopupCtrl* symbolPopup = this->GetImagePopupCtrlByID( kImagePopup );
	symbolPopup->PullDownResourceLayoutInit( fContent );
	symbolPopup->PullDownResourceLayoutSetSelectedResourceName( "" );
}

void CDlgResourcePopupSample::OnDDXInitialize()
{

}

void CDlgResourcePopupSample::OnUpdateUI()
{
	VWDialog::OnUpdateUI();

	VWImagePopupCtrl*	symbolPopup	= this->GetImagePopupCtrlByID( kImagePopup );
	bool				hasResSel	= ! symbolPopup->PullDownResourceLayoutGetSelectedResourceName().IsEmpty();
	this->EnableControl( kOK, hasResSel );
}

#include "StdAfx.h"

#include "SampleDlg4.h"
#include "SampleDlg1.h"

// dialog control IDs
#define		kOK                   1
#define		kCancel               2
#define		kTabControl           4
#define		kButtonsTab           5
#define		kButtonsGrp           6
#define		kButtonText           7
#define		kButtonCtrl           8
#define		kClrButtonText        9
#define		kClrButtonCtrl        10
#define		kColorPopup           11
#define		kUnnamed4             12
#define		kAnotherTab           13
#define		kUnnamed8             14
#define		kSampleText           15
#define		kCustomCtrlTab        16
#define		kUnnamed              17
#define		kUnnamed1             18
#define		kUnnamed2             19
#define		kUnnamed3             20
#define		kTreeCtrlTab          21
#define		kTreeCtrl             22
#define		kLeftButton           2605
#define		kThumbNailTab         24
#define		kThumbCtrlSelGrp      25
#define		kThumbNailCtrl        26
#define		kHatchesRadio         27
#define		kWallHatchesRadio     28
#define		kGradientsRadio       29
#define		kImagesRadio          30
#define		kGetButton            31
#define		kSettButton           32



using namespace UI;

EVENT_DISPATCH_MAP_BEGIN( CSampleDlg4 );
ADD_DISPATCH_EVENT( kButtonCtrl, OnButtonCtrl );
ADD_DISPATCH_EVENT( kClrButtonCtrl, OnColorButton );
ADD_DISPATCH_EVENT( kUnnamed4, OnColorPopup );
ADD_DISPATCH_EVENT( kLeftButton, OnLefButton );

ADD_DISPATCH_EVENT( kHatchesRadio, OnHatchesRadio );
ADD_DISPATCH_EVENT( kWallHatchesRadio, OnWallHatchesRadio );
ADD_DISPATCH_EVENT( kGradientsRadio, OnGradientsRadio );
ADD_DISPATCH_EVENT( kImagesRadio, OnImagesRadio );
ADD_DISPATCH_EVENT( kGetButton, OnGetThumbnailButton );
ADD_DISPATCH_EVENT( kSettButton, OnSetThumbnailButton );
EVENT_DISPATCH_MAP_END;

CSampleDlg4::CSampleDlg4() :
	//fMyOverrideCtrl( kButtonCtrl ),
	fMyCustomCtrl1( kUnnamed, true ),
	fMyCustomCtrl2( kUnnamed3 )
{
	this->SetSavedSettingsTag( "sampleDlg", "CSampleDlg4" ); 

	fActiveType					= kThumbnailType_Gradients;
	fThumbPatternIndex			= 0;

	this->BuildResourceImages( false );
}

CSampleDlg4::~CSampleDlg4()
{
	this->BuildResourceImages( true );
}

bool CSampleDlg4::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "VWUI Dialogs Sample/DialogLayout/SampleDlg4.vs" );
}

void CSampleDlg4::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	// TODO: Fill up your dialog controls here
	VWTreeCtrl*		pTreeCtrl	= this->GetTreeCtrlByID( kTreeCtrl );

	pTreeCtrl->AddChildItem( "hello" );
	pTreeCtrl->AddChildItem( "bye" );
	VWTreeCtrlItem item = pTreeCtrl->AddChildItem( "a" );
	item.AddChildItem( "c" );
	item.AddChildItem( "b" );
	
	this->FillThumbnail( kThumbnailType_Hatches );

	//gSDK->SetImageControlPath( this->GetDialogID(), kUnnamed, "C:\\MyProjects\\NNAWinSDK\\Engineering\\VectorWorks\\Mainline\\AppSource\\Source\\Plug-Ins\\Sample\\VWUI Dialogs Sample\\MacResources\\a.bmp" );
	TXString symbolRefName = "Symbol-1";
	SymbolImgInfo	symbolImgInfo;
	gSDK->UpdateSymbolDisplayControl( this->GetDialogID(), kUnnamed, symbolRefName, symbolImgInfo );
}

void CSampleDlg4::OnDDXInitialize()
{
//	this->AddDDX_Control( & fMyOverrideCtrl );
	this->AddDDX_Control( & fMyCustomCtrl1 );
	this->AddDDX_Control( & fMyCustomCtrl2 );
	this->AddDDX_CheckGroupBox( kUnnamed8, & fUnnamed8 );

	this->AddDDX_ColorButton( kClrButtonCtrl, & fColorButton );
	this->AddDDX_ColorPopup( kUnnamed4, & fColorPopup );
}

void CSampleDlg4::OnUpdateUI()
{
	VWDialog::OnUpdateUI();
}

void CSampleDlg4::OnButtonCtrl(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	CMyDialog dlg; 
	dlg.RunDialogLayout( "" ); 
}

void CSampleDlg4::OnColorButton(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	fColorPopup	= fColorButton;

	this->UpdateData( true );
}

void CSampleDlg4::OnColorPopup(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	fColorButton	= fColorPopup;

	this->UpdateData( true );
}

void CSampleDlg4::OnLefButton(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	VWDialog::AlertInform( "Left button clicked" );
}

void CSampleDlg4::BuildResourceImages(bool bFree)
{
	if ( bFree ) {
		fResourcesHatch.Dispose();
		fResourcesWallHatch.Dispose();
		fResourcesGradient.Dispose();
		fResourcesImage.Dispose();
		fResourcesLineStyle.Dispose();
	}
	else {
		TXString	folderName;

		// build default resource lists
		fResourcesHatch.BuildList( kHatchDefNode, kDefaultHatchesFolder, folderName );
		fResourcesWallHatch.BuildList( kHatchDefNode, kDefaultWallSlabRoofStylesFolder, folderName );
		fResourcesGradient.BuildList( kGradientDefNode, kDefaultGradientsFolder, folderName );
		fResourcesImage.BuildList( kImageDefNode, kDefaultImageFillsFolder, folderName );
		fResourcesLineStyle.BuildList( kLineTypeDefNode, kDefaultLineTypesFolder, folderName );
	}
}

void CSampleDlg4::FillThumbnail(UI::EThumbnailType type)
{
	VWThumbnailPopupCtrl*	pThumbnail		= this->GetThumbnailPopupCtrlByID( kThumbNailCtrl );

	fActiveType		= type;
	pThumbnail->RemoveAllImages();

	VWResourceList*	resList = nullptr;
	switch( type )
	{
		case kThumbnailType_Hatches:
			resList	= & fResourcesHatch;
			break;
		case kThumbnailType_WallHatches:
			resList	= & fResourcesWallHatch;
			break;
		case kThumbnailType_Gradients:
			resList	= & fResourcesGradient;
			break;
		case kThumbnailType_Images:
			resList	= & fResourcesImage;
			break;
		case kThumbnailType_LineStyle:
			resList	= & fResourcesLineStyle;
			break;
	}

	if ( resList )
	{
		for(size_t i=0, cnt=resList->GetNumItems(); i<cnt; ++i)
		{
			pThumbnail->AddImageFromResource( resList->GetListID(), i );
		}
	}

	// ensure selection
	if ( gSDK->InternalIndexToHandle( fThumbPatternIndex ) )
	{
		pThumbnail->SelectItem( fThumbPatternIndex );
		size_t		selIndex	= pThumbnail->GetObjectItemIndex( fThumbPatternIndex );
		if ( selIndex == size_t(-1) && pThumbnail->GetItemsCount() > 0 )
		{
			pThumbnail->SelectItem( size_t(0) );
		}
	}
}

void CSampleDlg4::OnHatchesRadio(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	this->FillThumbnail( kThumbnailType_Hatches );
}

void CSampleDlg4::OnWallHatchesRadio(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	this->FillThumbnail( kThumbnailType_WallHatches );
}

void CSampleDlg4::OnGradientsRadio(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	this->FillThumbnail( kThumbnailType_Gradients );
}

void CSampleDlg4::OnImagesRadio(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	this->FillThumbnail( kThumbnailType_LineStyle );
}

void CSampleDlg4::OnGetThumbnailButton (TControlID controlID, VWDialogEventArgs& eventArgs)
{
	VWThumbnailPopupCtrl*	pThumbnail		= this->GetThumbnailPopupCtrlByID( kThumbNailCtrl );

	fThumbPatternIndex				= 0;

	InternalIndex	popupIntIndex	= pThumbnail->GetSelectedItem();;
	Sint32			popupIndex		= (Sint32) pThumbnail->GetSelectedItemIndex();

	VWResourceList*	resList = nullptr;
	switch( fActiveType )
	{
		case kThumbnailType_Hatches:
			resList	= & fResourcesHatch;
			break;
		case kThumbnailType_WallHatches:
			resList	= & fResourcesWallHatch;
			break;
		case kThumbnailType_Gradients:
			resList	= & fResourcesGradient;
			break;
		case kThumbnailType_Images:
			resList	= & fResourcesImage;
			break;
		case kThumbnailType_LineStyle:
			resList	= & fResourcesLineStyle;
			break;
	}

	if( resList )
	{
		TXString	name;
		gSDK->InternalIndexToNameN( popupIntIndex, name );

		if ( popupIndex != size_t(-1) && name[0] == 0 )
		{
			MCObjectHandle	hResource	= resList->ImportResourceToCurrentFile( popupIndex );

			gSDK->GetObjectName( hResource, name );
			if ( ! gSDK->NameToInternalIndexN( name, popupIntIndex ) ) {
				popupIntIndex	= 0;
			}
		}

		fThumbPatternIndex	= popupIntIndex;
	}

	TXString text;
	text.Format( "Selected pattern index=0x%X\nPress 'Set' to select this one in the thumbnail", fThumbPatternIndex );
	VWDialog::AlertInform( text );

	// reload the thumbnail so it shows correct values after we have imported
	// this is needed because we need to have the thumbnail update
	this->BuildResourceImages( true );
	this->BuildResourceImages( false );
	this->FillThumbnail( fActiveType );
}

void CSampleDlg4::OnSetThumbnailButton(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	// recongnize the pattern index
	MCObjectHandle		hPatObject		= ::GS_InternalIndexToHandle( gCBP, fThumbPatternIndex );
	short				patObjType		= ::GS_GetObjectType( gCBP, hPatObject );

	this->GetRadioButtonCtrlByID( kHatchesRadio )->SetState( false );
	this->GetRadioButtonCtrlByID( kWallHatchesRadio )->SetState( false );
	this->GetRadioButtonCtrlByID( kGradientsRadio )->SetState( false );
	this->GetRadioButtonCtrlByID( kImagesRadio )->SetState( false );

	switch( patObjType ) {
		case kGradientDefNode:
			this->FillThumbnail( kThumbnailType_Gradients );
			this->GetRadioButtonCtrlByID( kGradientsRadio )->SetState( true );
			break;
		case kImageDefNode:
			this->FillThumbnail( kThumbnailType_Images );
			this->GetRadioButtonCtrlByID( kImagesRadio )->SetState( true );
			break;
		case kHatchDefNode:
		default:
			this->FillThumbnail( kThumbnailType_Hatches );
			this->GetRadioButtonCtrlByID( kHatchesRadio )->SetState( true );
			break;
	}
}




//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include "VWFC/VWUI/SelectSymbolDlg.h"

constexpr auto kStaticTextCtrl		= 4;
constexpr auto kResourcePopupCtrl	= 5;

using namespace VWFC::VWUI;
using namespace VectorWorks::Extension;

CStandardSelectSymbolDlg::CStandardSelectSymbolDlg(
												const TXString&						title						/*= ""*/,
												const TXString&						emptyMessage				/*= ""*/,
												const TXString&						okBtnText					/*= ""*/,
												const TXString&						cancelBntText				/*= ""*/,
												const TXString&						helpText					/*= ""*/,
												const TXString&						label						/*= ""*/,
												bool								preserveFolders				/*= false*/,
												const TFolderSpecifierArray&		folderSpecifiers			/*= VectorWorks::Extension::TFolderSpecifierArray()*/,
												const THandleFilterCallback2&		filterCallback				/*= nullptr*/,
												const TPropertiesFilterCallback&	propertiesFilterCallback	/*= nullptr*/)
	: fTitle				( title						)
	, fOkBtnText			( okBtnText					)
	, fCancelBntText		( cancelBntText				)
	, fHelpText				( helpText					)
	, fLabel				( label						)
	, fResourcePopupCtrl	( kResourcePopupCtrl		)
	, fStaticTextCtrl		( kStaticTextCtrl			)
	, fFilterCallback		( filterCallback			)
	, fPropsFilterCallback	( propertiesFilterCallback	)
	, fPreserveFolders		( preserveFolders			)
{
	if ( fTitle.IsEmpty() )	fTitle						= TXResource( "Vectorworks/Strings/ResourceManager.vwstrings", "SelectSymbolDialogTitle" );
	if ( fLabel.IsEmpty() )	fLabel						= TXResource( "Vectorworks/Strings/ResourceManager.vwstrings", "SelectSymbolDialogLbl" );
	if ( fOkBtnText.IsEmpty()		)	fOkBtnText		= TXResource( "Vectorworks/Strings/144 *", "1" );
	if ( fCancelBntText.IsEmpty()	)	fCancelBntText	= TXResource( "Vectorworks/Strings/144 *", "6" );

	fContent->SetEmptyMessage( emptyMessage );
	fContent->InitByTDType( kSymDefNode );

	for ( const auto& folderSpec : folderSpecifiers )
	{
		fContent->AddContent( folderSpec );
	}

	if ( fFilterCallback )
	{
		fContent->SetFilter( fFilterCallback );
	}

	if ( fPropsFilterCallback )
	{
		fContent->SetResourcePropertiesFilter( fPropsFilterCallback );
	}
}

MCObjectHandle CStandardSelectSymbolDlg::GetSelectedSymbol() const
{
	MCObjectHandle		hSymbol = nullptr;
	SResourceSelection	resSelection;

	if ( fContent->GetCurrentSelection( resSelection ) )
	{
		hSymbol = fContent->ImportSelectedResourceToCurrentFile( VectorWorks::EImportResourceConflictResult::eImportResourceConflictResult_AskWithUI, fPreserveFolders );
	}

	return hSymbol;
}

bool CStandardSelectSymbolDlg::CreateDialogLayout()
{
	bool isOK = VWDialog::CreateDialog( fTitle, fOkBtnText, fCancelBntText, !fHelpText.IsEmpty(), false, false );

	isOK = isOK && fResourcePopupCtrl.CreateControl( this );
	isOK = isOK && fStaticTextCtrl.CreateControl( this, fLabel );

	if ( isOK )
	{
		if ( !fHelpText.IsEmpty() )
		{
			fResourcePopupCtrl.SetHelpText( fHelpText );
			fStaticTextCtrl.SetHelpText( fHelpText );
		}

		VWDialog::AddFirstGroupControl( &fStaticTextCtrl );
		VWDialog::AddRightControl( &fStaticTextCtrl, &fResourcePopupCtrl );
	}

	return isOK;
}

void CStandardSelectSymbolDlg::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	TXString resName;
	gSDK->PullDownResourceLayoutInit( this->GetDialogID(), kResourcePopupCtrl, fContent );
	fContent->SelectFirstAvailableResource( resName, SSearchProperties() );
}

void CStandardSelectSymbolDlg::OnDefaultButtonEvent()
{
	SResourceSelection	resSelection;
	bool				isOK = false;

	if ( fContent->GetCurrentSelection( resSelection ) )
	{
		isOK = true;
	}

	if ( isOK )
	{
		VWDialog::OnDefaultButtonEvent();
	}
	else
	{
		gSDK->SysBeep( 200 );
	}
}

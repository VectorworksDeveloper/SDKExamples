//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include "VWFC/VWUI/StandardInfoDlg.h"

constexpr auto kStaticTextCtrl			= 4;
constexpr auto kStaticTextCtrl2			= 5;
constexpr auto kImageCtrl				= 6;
constexpr auto kCheckboxDontShowCtrl	= 7;

using namespace VWFC::VWUI;

EVENT_DISPATCH_MAP_BEGIN( CStandardInfoDlg )
{
	ADD_DISPATCH_EVENT( kCheckboxDontShowCtrl, OnCheckboxDontShow )
}
EVENT_DISPATCH_MAP_END

CStandardInfoDlg::CStandardInfoDlg(	const TXString&	text,
												const TXString&	advice,
												const TXString&	imagePath,
												const short&	imageWidth				/*= 300*/,
												const short&	imageHeight				/*= 300*/,
												const short&	textWidth				/*= 50*/,
												const TXString&	savedSettingCategory	/*= ""*/,
												const TXString&	savedSettingItem		/*= ""*/,
												const TXString&	title					/*= ""*/,
												const TXString&	dontShowAgain			/*= ""*/,
												const TXString&	okBtnText				/*= ""*/,
												const TXString&	cancelBntText			/*= ""*/,
												const TXString&	helpText				/*= ""*/)
	: fStaticTextCtrl		( kStaticTextCtrl		)
	, fStaticTextCtrl2		( kStaticTextCtrl2		)
	, fImageCtrl			( kImageCtrl			)
	, fCheckboxCtrl			( kCheckboxDontShowCtrl	)
	, fText					( text					)
	, fAdvice				( advice				)
	, fImagePath			( imagePath				)
	, fImageWidth			( imageWidth			)
	, fImageHeight			( imageHeight			)
	, fTextWidth			( textWidth				)
	, fSavedSettingCategory	( savedSettingCategory	)
	, fSavedSettingItem		( savedSettingItem		)
	, fTitle				( title					)
	, fDontShowAgain		( dontShowAgain			)
	, fOkBtnText			( okBtnText				)
	, fCancelBntText		( cancelBntText			)
	, fHelpText				( helpText				)
{
	if ( fTitle.IsEmpty()			)	fTitle			= TXResource( "Vectorworks/Strings/144 *", "5" );
	if ( fDontShowAgain.IsEmpty()	)	fDontShowAgain	= TXResource( "Vectorworks/Strings/144 *", "15" );
	if ( fOkBtnText.IsEmpty()		)	fOkBtnText		= TXResource( "Vectorworks/Strings/144 *", "1" );
	if ( fCancelBntText.IsEmpty()	)	fCancelBntText	= TXResource( "Vectorworks/Strings/144 *", "6" );
}

bool CStandardInfoDlg::CreateDialogLayout()
{
	bool isOK = VWDialog::CreateDialog( fTitle, fOkBtnText, fCancelBntText, !fHelpText.IsEmpty(), false, false );

	if ( TXString checkBoxStr; gSDK->GetSavedSetting( fSavedSettingCategory, fSavedSettingItem, checkBoxStr ) )
	{
		double	checkBoxVal = 0;	gSDK->StringToDouble( nsGeneral, checkBoxStr, checkBoxVal );
		isOK = isOK && checkBoxVal == 0;
	}

	isOK = isOK && fStaticTextCtrl	.CreateControl( this, fText				, fTextWidth, eStaticTextTypeBold	);
	isOK = isOK && fStaticTextCtrl2	.CreateControl( this, fAdvice			, fTextWidth						);
	isOK = isOK && fImageCtrl		.CreateControl( this					, fImageWidth, fImageHeight			);
	isOK = isOK && fCheckboxCtrl	.CreateControl( this, fDontShowAgain										);

	if ( isOK )
	{
		if ( !fHelpText.IsEmpty() )
		{
			fStaticTextCtrl.SetHelpText( fHelpText );
			fStaticTextCtrl2.SetHelpText( fHelpText );
		}

		VWDialog::AddFirstGroupControl( &fStaticTextCtrl );

		VWDialog::AddBelowControl( &fStaticTextCtrl		, &fStaticTextCtrl2	);
		VWDialog::AddBelowControl( &fStaticTextCtrl2	, &fImageCtrl		);

		if ( !fDontShowAgain.IsEmpty() && !fSavedSettingCategory.IsEmpty() && !fSavedSettingItem.IsEmpty() )
		{
			VWDialog::AddBelowControl( &fImageCtrl		, &fCheckboxCtrl	);
		}
	}

	return isOK;
}

void CStandardInfoDlg::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	fImageCtrl.SetImage( fImagePath );
}

void CStandardInfoDlg::OnCheckboxDontShow(TControlID, VWDialogEventArgs&)
{
	TXString	checkBoxStr;	gSDK->DoubleToString( nsGeneral, 0, 0, 1, checkBoxStr );
	gSDK->SetSavedSetting( fSavedSettingCategory, fSavedSettingItem, checkBoxStr );
}

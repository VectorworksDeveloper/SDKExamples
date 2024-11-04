//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace VWUI
	{
		class CStandardInfoDlg : public VWDialog
		{
			DEFINE_EVENT_DISPATH_MAP;

		public:
			CStandardInfoDlg(	const TXString&	text,
									const TXString&	advice,
									const TXString&	image,
									const short&	imageWidth				= 300,
									const short&	imageHeight				= 300,
									const short&	textWidth				= 50,
									const TXString&	savedSettingCategory	= "",
									const TXString&	savedSettingItem		= "",
									const TXString&	title					= "",
									const TXString&	dontShowAgain			= "",
									const TXString&	okBtnText				= "",
									const TXString&	cancelBntText			= "",
									const TXString&	helpText				= "");
			~CStandardInfoDlg() final = default;

		protected:
			void				OnDDXInitialize()		final {};
			bool				CreateDialogLayout()	final;
			void				OnInitializeContent()	final;

		//	Dispatch map events
			void				OnCheckboxDontShow(TControlID controlID, VWDialogEventArgs& eventArgs);

		private:
			VWStaticTextCtrl	fStaticTextCtrl;
			VWStaticTextCtrl	fStaticTextCtrl2;
			VWPictureCtrl		fImageCtrl;
			VWCheckButtonCtrl	fCheckboxCtrl;

			TXString			fText;
			TXString			fAdvice;
			TXString			fImagePath;

			short				fImageWidth;
			short				fImageHeight;
			short				fTextWidth;

			TXString			fSavedSettingCategory;
			TXString			fSavedSettingItem;
			TXString			fTitle;
			TXString			fDontShowAgain;
			TXString			fOkBtnText;
			TXString			fCancelBntText;
			TXString 			fHelpText;
		};
	}
}

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
		class CStandardSelectSymbolDlg : public VWDialog
		{
		public:
			CStandardSelectSymbolDlg(
									const TXString&												title						= "",
									const TXString&												emptyMessage				= "",
									const TXString&												okBtnText					= "",
									const TXString&												cancelBntText				= "",
									const TXString&												helpText					= "",
									const TXString&												label						= "",
									bool														preserveFolders				= false,
									const VectorWorks::Extension::TFolderSpecifierArray&		folderSpecifiers			= VectorWorks::Extension::TFolderSpecifierArray(),
									const VectorWorks::Extension::THandleFilterCallback2&		filterCallback				= nullptr,
									const VectorWorks::Extension::TPropertiesFilterCallback&	propertiesFilterCallback	= nullptr);
			~CStandardSelectSymbolDlg() final = default;

			MCObjectHandle		GetSelectedSymbol() const;

		protected:
			void				OnDDXInitialize()		final override {};
			bool				CreateDialogLayout()	final override;
			void				OnInitializeContent()	final override;
			void				OnDefaultButtonEvent()	final override;

		private:
			VWThumbnailPopupCtrl	fResourcePopupCtrl;
			VWStaticTextCtrl		fStaticTextCtrl;

			TXString				fTitle;
			TXString				fOkBtnText;
			TXString				fCancelBntText;
			TXString 				fHelpText;
			TXString 				fLabel;

			const VectorWorks::Extension::THandleFilterCallback2&		fFilterCallback;
			const VectorWorks::Extension::TPropertiesFilterCallback&	fPropsFilterCallback;
			VectorWorks::Extension::IResourceManagerContentPtr			fContent = VectorWorks::Extension::IID_ResourceManagerContent;

			bool					fPreserveFolders = false;
		};
	}
}

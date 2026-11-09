//
//	Copyright  Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Dialog.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWEditStyleDialog : public VWDialog
		{
			public:
								VWEditStyleDialog();
				virtual			~VWEditStyleDialog();

				void			SetWidgetsProvider( IWidgetsProvider * pWidgetsProvider );
				virtual void	SetStyleSupport(VWStyleSupport * pStyleSupport, bool styleMode);

				void			SetStyleName( const TXString & styleName );

				void			ShowCurrentValues( bool bShow ) { fbShowCurrentValues = bShow;}

			// virtuals
			protected:
				virtual bool	CreateDialogLayout();
				virtual void	OnInitializeContent();
				virtual	void	OnDDXInitialize();
				virtual void	OnUpdateUI();

				virtual void	OnDefaultButtonEvent();
				virtual void	OnCancelButtonEvent();


			// dispatch map
			protected:
				DEFINE_EVENT_DISPATH_MAP;
				void	OnChooseCatalogItem(Sint32 controlID, VWDialogEventArgs& eventArgs);
				void	OnChooseCatalog(Sint32 controlID, VWDialogEventArgs& eventArgs);
				void	OnDataListBrowser(Sint32 controlID, VWDialogEventArgs& eventArgs);
				void	OnUseCatalog( Sint32 controlID, VWDialogEventArgs& eventArgs );
				void	OnCatByStyleBtn( Sint32 controlID, VWDialogEventArgs& eventArgs );

			private:
				bool			AddItem( Sint16 paramIndex, const TXString & displayText, TXString & newDisplayText );
				void			LoadCatalog(TXString & catalogName );
				void			UpdateCatalogInfo();
				void			UpdateListBrowser();

				VWStaticTextCtrl	fStyleNameCapiton;
				VWStaticTextCtrl	fStyleNameText;
				VWListBrowserCtrl	fListBrowser;
				
				VWCheckButtonCtrl	fCatalogText;
				VWPullDownMenuCtrl	fCatalogPopup;
				VWStyleButtonCtrl	fCatByStyleButton;
				VWImageButtonCtrl	fChooseCatItemButton;
				VWStaticTextCtrl	fCatItemName;

				EFolderSpecifier	fFolderSpec;
				TXString			fRelativePath;
				TXStringArray		fXMLCatalogNames;
				TXStringArray		fTXTCatalogNames;


				TXString			fLBByStyle;
				TXString			fLBByInstance;
				TXString			fLBByCatalog;
				size_t				fImageIndexByInst;
				size_t				fImageIndexByStyle;
				size_t				fImageIndexByCat;

				TXString			fNoCatalogsFound;
				TXString			fNoCatalogChosen;


				TXString			fStyleName;

				bool				fbShowCurrentValues;

				IWidgetsProvider *	fpWidgetsProvider;

				bool				fUsesCatalog;
				TXStringArray		fParamNames;
				VWCatalogSupport	fCatalogSupport;



		};

	}
}
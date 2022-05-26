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
		class VWSelectCatalog : public VWDialog
		{
			public:
								VWSelectCatalog();
				virtual			~VWSelectCatalog();

				void			SetFolderSpecifier( EFolderSpecifier folderSpec );
				void			SetRelativePath( const TXString & relativePath );
				
				TXString		GetSelectedCatalog();
				void			SetSelectedCatalog( const TXString & selectedCatalog );


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
				void	OnAttachCatalog( Sint32 controlID, VWDialogEventArgs& eventArgs );
				void	OnDetachCatalog( Sint32 controlID, VWDialogEventArgs& eventArgs );
				void	OnDataListBrowser( Sint32 controlID, VWDialogEventArgs& eventArgs );
				
				bool		fAttachCatalog;
				bool		fDetachCatalog;

			private:
				EFolderSpecifier	fFolderSpecifier;
				TXString			fRelativePath;
				TXString			fSelectedCatalog;

				TXStringArray		fXMLCatalogNames;
				TXStringArray		fTXTCatalogNames;

				size_t				fSelectedCatalogRow;
				


		};

	}
}
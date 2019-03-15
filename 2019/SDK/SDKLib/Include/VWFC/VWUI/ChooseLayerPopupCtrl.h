//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Control.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWChooseLayerPopupCtrl : public VWControl
		{
		public:
			enum EChooseLayerControlType {
				eAllLayers,
				eDesignLayers,
				eSheetLayers
			};

							VWChooseLayerPopupCtrl(TControlID id);
			virtual			~VWChooseLayerPopupCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, short widthInStdChar, EChooseLayerControlType type);

		// attributes
		public:
			void			Refresh();

			void			GetSelectedLayer( TXString & selectedClass ) const;
			void			SetSelectedLayer( const TXString & selectedClass );

			short			GetSelectedIndex() const;
			void			SelectIndex( short nIndex );

			void			InsertProposedLayer( const TXString & proposedClass );

		};
	}
}
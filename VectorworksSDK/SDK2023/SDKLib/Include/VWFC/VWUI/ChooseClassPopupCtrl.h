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
		class VWChooseClassPopupCtrl : public VWControl
		{
		public:
							VWChooseClassPopupCtrl(TControlID id);
			virtual			~VWChooseClassPopupCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, short widthInStdChar, bool bShowDefaultStaticItems = true);

		// attributes
		public:
			void			Refresh();

			void			GetSelectedClass( TXString & selectedClass ) const;
			void			SetSelectedClass( const TXString & selectedClass );

			size_t			GetSelectedIndex() const;
			void			SelectIndex( size_t nIndex );

			void			InsertProposedClass( const TXString & proposedClass );

			bool			GetChoiceIndex( const TXString& choiceToFind, size_t& choiceIndex) const; // Returns true if the choice was found
		};
	}
}
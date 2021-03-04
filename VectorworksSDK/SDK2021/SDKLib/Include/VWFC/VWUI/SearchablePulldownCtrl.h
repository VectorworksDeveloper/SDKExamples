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
		class VWSearchablePulldownCtrl : public VWControl
		{
			public:
								VWSearchablePulldownCtrl(TControlID id);
				virtual			~VWSearchablePulldownCtrl( );

				virtual bool	CreateControl(VWDialog* pDlg, short widthInStdChar);

				void			Clear();
				void			Add(const TXString& idName, const TXString& text, const TXString& toolTip=TXString(), const TXString& iconSpec=TXString());
				void			AddChild(const TXString& idName, const TXString& text, const TXString& parentIdName, const TXString& toolTip=TXString(), const TXString& iconSpec=TXString());

				// static choices show up at the top of the regular choices and cannot be search. they are used for general predefined fixed options typically
				void			ClearStaticChoices();
				void			AddStaticChoice(const TXString& idName, const TXString& text, const TXString& toolTip=TXString(), const TXString& iconSpec=TXString());

				void			AddHeaderItem(const TXString& text, const TXString& toolTip = TXString(), const TXString& iconSpec = TXString());

				TXString		GetSelectedItem();
				bool			SetSelectedItem(const TXString& idName);

				bool			GetTextByID(const TXString& idName, TXString& outText);
				bool			GetIDByText(const TXString& text, TXString& outIdName);
		};
	}
}
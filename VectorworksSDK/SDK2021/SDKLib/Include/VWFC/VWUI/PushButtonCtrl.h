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
		class VWPushButtonCtrl : public VWControl
		{
		public:
							VWPushButtonCtrl(TControlID id);
			virtual			~VWPushButtonCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& text);

		// attributes
		public:
			void	SetIconPushButtonImage(const TXString& imageSpec);
			void	SetIconPushButtonImageUsingFullFilePath(IFileIdentifier* imgFileID);
			void	SetIconPushButtonState(bool pressed);
			bool	GetIconPushButtonState() const;
		};
	}
}
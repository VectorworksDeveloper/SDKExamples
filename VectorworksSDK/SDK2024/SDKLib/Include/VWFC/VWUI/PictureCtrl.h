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
		class VWPictureCtrl : public VWControl
		{
		public:
							VWPictureCtrl(TControlID id);
			virtual			~VWPictureCtrl();

			virtual bool    CreateControl(VWDialog* pDlg, const TXString& imageSpec);
			virtual bool	CreateControl(VWDialog* pDlg, Sint32 iWidthPixels, Sint32 iHeightPixels);

		// attributes
		public:
			void			SetImage(const TXString& imageSpec);
			void			SetImage(VectorWorks::UI::IIconPtr icon);
			void			SetImageUsingFullFilePath(IFileIdentifier* imgFileID);
		};
	}
}

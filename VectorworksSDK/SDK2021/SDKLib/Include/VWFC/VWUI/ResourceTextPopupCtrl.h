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
		class VWResourceTextPopupCtrl : public VWControl
		{
		public:
							VWResourceTextPopupCtrl(TControlID id);
			virtual			~VWResourceTextPopupCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, Sint32 widthInStdChar);

		// attributes
		public:
			void			PullDownResourceLayoutInit(VectorWorks::Extension::IResourceManagerContent* content);
			void			PullDownResourceLayoutSetSelectedResourceName(const TXString& name);
			TXString		PullDownResourceLayoutGetSelectedResourceName() const;
		};
	}
}
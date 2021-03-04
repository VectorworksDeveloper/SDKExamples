#pragma once

#include "Control.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWSeparatorCtrl : public VWControl
		{
		public:
							VWSeparatorCtrl( TControlID id );
			virtual			~VWSeparatorCtrl( );
		
			virtual bool	CreateControl( VWDialog* pDlg, short width );
		};
	}
}



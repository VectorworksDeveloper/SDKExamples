#pragma once

#include "Control.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWImageButtonCtrl : public VWControl
		{
		public:
							VWImageButtonCtrl( TControlID id );
			virtual			~VWImageButtonCtrl( );
			
			virtual bool	CreateControl( VWDialog* pDlg, const TXString& imageSpec, int buttonWidth = 1 );


		// attributes
		public:
			virtual bool	UpdateImage( const TXString& imageSpec );
		};
	}
}



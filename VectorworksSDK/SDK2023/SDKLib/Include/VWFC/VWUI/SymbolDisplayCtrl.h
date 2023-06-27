#pragma once

#include "Control.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWSymbolDisplayCtrl : public VWControl
		{
		public:
							VWSymbolDisplayCtrl( TControlID id );
			virtual			~VWSymbolDisplayCtrl( );
			
			virtual bool	CreateControl( VWDialog* pDlg, short width, short height, short margin );

		// attributes
		public:
			virtual void	Update( const TXString& resourceName, TRenderMode renderMode, TStandardView view );

		};
	}
}



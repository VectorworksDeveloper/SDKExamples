#include "StdHeaders.h"

#include "VWFC/VWUI/SeparatorCtrl.h"


using namespace VWFC::VWUI;

VWSeparatorCtrl::VWSeparatorCtrl( TControlID id ) : VWControl(id)
{
}


VWSeparatorCtrl::~VWSeparatorCtrl( )
{
}


bool VWSeparatorCtrl::CreateControl( VWDialog* pDlg, short width )
{
	::GS_CreateSeparator( gCBP, pDlg->GetControlID(), fControlID, width );
	
	return VWControl::CreateControl( pDlg );
}

#include "StdHeaders.h"

#include "VWFC/VWUI/SeparatorCtrl.h"


using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWSeparatorCtrl::VWSeparatorCtrl( TControlID id ) : VWControl(id, {eCompSeparator})
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

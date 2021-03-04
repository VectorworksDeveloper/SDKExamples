#include "StdAfx.h"

#include "ExtMenu.h"
#include "ExtTool.h"

using namespace VectorWorks::Filing;
using namespace TesterModule;

namespace TesterModule
{
	// --------------------------------------------------------------------------------------------------------
	static SMenuDef		gMenuDef = {
		/*Needs*/			0x00,
		/*NeedsNot*/		0x00,
		/*Title*/			{"CExtMenu", "title"},
		/*Category*/		{"CExtMenu", "category"},
		/*HelpText*/		{"CExtMenu", "help"},
		/*VersionCreated*/	16,
		/*VersoinModified*/	0,
		/*VersoinRetired*/	0
	};

	/*static SSTRResource	gMenuChunksDef[] = {
		{ {12000, 4}, "" },
		{ {12000, 5}, "" },
		{ {12000, 6}, "" },
		{ {12000, 7}, "" },
		{ {12000, 8}, "" },
		{ {NULL, NULL}, NULL }
	};*/
}

// --------------------------------------------------------------------------------------------------------
// {ACC6EE12-7A4B-45AF-AD23-2E462710E87A}
IMPLEMENT_VWMenuExtension(
	/*Extension class*/	CExtMenu,
	/*Event sink*/		CMenu_EventSink,
	/*Universal name*/	"CExtMenu",
	/*Version*/			1,
	/*UUID*/			0xacc6ee12, 0x7a4b, 0x45af, 0xad, 0x23, 0x2e, 0x46, 0x27, 0x10, 0xe8, 0x7a );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtMenu::CExtMenu(CallBackPtr cbp)
	: VWExtensionMenu( cbp, gMenuDef, NULL )
//	: VWExtensionMenu( cbp, gMenuDef, gMenuChunksDef )
{
}

CExtMenu::~CExtMenu()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CMenu_EventSink::CMenu_EventSink(IVWUnknown* parent)
	: VWMenu_EventSink( parent )
{
}

CMenu_EventSink::~CMenu_EventSink()
{
}
/*
//std::ofstream* outFile;
void FEO_CallBack(Handle h, CallBackPtr cbp, void *env)
{
  try {
   MCObjectHandle h1 = gSDK->DuplicateObject(h);
  VWFC::VWObjects::VWBodyObj obj(h1);
   gSDK->DeleteObject(h1, false);
 }
 catch (VWBadObjectTypeException& e) {
  //(*outFile) << e.fszDescription << std::endl;
 }
 catch (...) {
 // (*outFile) << "Unknown error" << std::endl;
 }
}*/

void CMenu_EventSink::DoInterface()
{
	MCObjectHandle	h_dtm	= gSDK->FirstSelectedObject();

	VCOMPtr<IDTMLibrary> pDTM( IID_DTMLibrary );
	VCOMPtr<IDTMSettings> pDTMSettings( IID_DTMSettings );
	SDTMGraphicData sdtm_data;
	if(VCOM_SUCCEEDED(pDTM->GetSettings(h_dtm, IID_DTMSettings, &pDTMSettings)))
	{
		bool ok = false;
		ok = ok;
		sdtm_data;
	}


//  gSDK->ForEachObject( allObjects /*+ descendIntoAll*/, FEO_CallBack, 0 );

//	const VWIID&	iidToolExt	= CExtTool::_GetIID();
//	gSDK->RunTempTool( iidToolExt );

	gSDK->AlertInform( "CMenu_EventSink::DoInterface" );

}

#include "StdAfx.h"

#include "DlgSystemObjPrefs.h"

// dialog control IDs
#define		kOK                   1
#define		kCancel               2
#define		kSystemTypeLbl        4
#define		kSysObjTypePopup      5

using namespace DemoSystem::UI;

EVENT_DISPATCH_MAP_BEGIN( CDlgSystemObjPrefs );
EVENT_DISPATCH_MAP_END;

CDlgSystemObjPrefs::CDlgSystemObjPrefs(short type)
{
	// Assign settings tag to this dialog so it would save it's position and size automatically
	this->SetSavedSettingsTag( "SDKSamplesEnergy", "DlgSystemObjPrefs" );
	fSysObjTypePopup = type == (short)VectorWorks::EnergyAnalysis::ESystemObjectType::VentilationSystem ? 1 : 0;
}

CDlgSystemObjPrefs::~CDlgSystemObjPrefs()
{
}

bool CDlgSystemObjPrefs::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "SDKSamplesEnergy/DialogLayout/DlgSystemObjPrefs.vs" );
}

void CDlgSystemObjPrefs::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	VWPullDownMenuCtrl* sysObjType = this->GetPullDownMenuCtrlByID( kSysObjTypePopup );

	sysObjType->AddItem( TXResStr( "DlgSystemObjPrefs", "HeatingSolar" ), 0 );
	sysObjType->AddItem( TXResStr( "DlgSystemObjPrefs", "Ventilation" ), 1 );
}

void CDlgSystemObjPrefs::OnDDXInitialize()
{
	this->AddDDX_PulldownMenu( kSysObjTypePopup, & fSysObjTypePopup );

}

void CDlgSystemObjPrefs::OnUpdateUI()
{
	VWDialog::OnUpdateUI();
}

short CDlgSystemObjPrefs::GetSystemValue() const
{
	short result = (short)VectorWorks::EnergyAnalysis::ESystemObjectType::VentilationSystem;

	if( fSysObjTypePopup == 0 )
	{
		result = (short)VectorWorks::EnergyAnalysis::ESystemObjectType::HeatingSolar;
	}

	return result;
}



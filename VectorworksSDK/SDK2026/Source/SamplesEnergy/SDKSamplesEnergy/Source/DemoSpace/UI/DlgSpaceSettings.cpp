#include "StdAfx.h"

#include "DlgSpaceSettings.h"

// dialog control IDs
#define		kOK                   1
#define		kCancel               2
#define		kHeightTxt            4
#define		kHeightVal            5
#define		kHeightUn             6
#define		kIncludeChechBox      7
#define		kManualCheckBox       8
#define		kAreaTxt              9
#define		kAreaVal              10
#define		kAreaUn               11
#define		kAreaFactorTxt        12
#define		kAreaFactorVal        13
#define		kAdvancedBtn          14

using namespace DemoSpace::UI;

EVENT_DISPATCH_MAP_BEGIN( CDlgSpaceSettings );
ADD_DISPATCH_EVENT( kAdvancedBtn, OnAdvancedBtn );
EVENT_DISPATCH_MAP_END;

CDlgSpaceSettings::CDlgSpaceSettings(const CSpaceEnergyData& data, IEnergySpacePtr energyData)
	: fEnergyUnits( IID_EnergyUnits )
{
	// Assign settings tag to this dialog so it would save it's position and size automatically
	this->SetSavedSettingsTag( "DemoSpace", "DlgSpaceSettings" );

	fHeightVal			= fEnergyUnits->ConvertX2Document( EEnergyUnitType::M, data.fHeight / 1000.0 );
	fIncludeChechBox	= energyData->GetIncludeInEnergyAnalysis();
	fAreaVal			= fEnergyUnits->ConvertX2Document( EEnergyUnitType::SqM, data.fArea );
	fAreaFactorVal		= energyData->GetAreaFactor();
	fManualCheckBox		= data.fIsManualArea;

	fEnergyData = energyData;
}

CDlgSpaceSettings::~CDlgSpaceSettings()
{
}

void CDlgSpaceSettings::GetData(CSpaceEnergyData& data)
{
	data.fIsManualArea	= fManualCheckBox;
	data.fArea			= fEnergyUnits->ConvertDocument2X( EEnergyUnitType::SqM, fAreaVal );
	data.fHeight		= fEnergyUnits->ConvertDocument2X( EEnergyUnitType::M, fHeightVal ) * 1000.0;

	fEnergyData->SetIncludeInEnergyAnalysis( fIncludeChechBox );
	fEnergyData->SetAreaFactor( fAreaFactorVal );
}

bool CDlgSpaceSettings::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "SDKSamplesEnergy/DialogLayout/DlgSpaceSettings.vs" );
}

void CDlgSpaceSettings::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	this->GetStaticTextCtrlByID( kHeightUn )->SetControlText( fEnergyUnits->GetDocumentUnitString_X( EEnergyUnitType::M ) );
	this->GetStaticTextCtrlByID( kAreaUn )->SetControlText( fEnergyUnits->GetDocumentUnitString_X( EEnergyUnitType::SqM ) );
}

void CDlgSpaceSettings::OnDDXInitialize()
{
	this->AddDDX_EditReal( kHeightVal, & fHeightVal, VWEditRealCtrl::kEditControlReal );
	this->AddDDX_CheckButton( kIncludeChechBox, & fIncludeChechBox );
	this->AddDDX_CheckButton( kManualCheckBox, & fManualCheckBox );
	this->AddDDX_EditReal( kAreaVal, & fAreaVal, VWEditRealCtrl::kEditControlReal );
	this->AddDDX_EditReal( kAreaFactorVal, & fAreaFactorVal, VWEditRealCtrl::kEditControlReal );
}

void CDlgSpaceSettings::OnUpdateUI()
{
	VWDialog::OnUpdateUI();

	this->EnableControl( kManualCheckBox,	fIncludeChechBox );
	this->EnableControl( kAreaFactorTxt,	fIncludeChechBox );
	this->EnableControl( kAreaFactorVal,	fIncludeChechBox );
	this->EnableControl( kAdvancedBtn,		fIncludeChechBox );

	this->EnableControl( kAreaTxt,			fIncludeChechBox && fManualCheckBox );
	this->EnableControl( kAreaVal,			fIncludeChechBox && fManualCheckBox );
	this->EnableControl( kAreaUn,			fIncludeChechBox && fManualCheckBox );
}

void CDlgSpaceSettings::OnAdvancedBtn(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	fEnergyData->DialogUI_EditAdvancedOptionsDlg();
}

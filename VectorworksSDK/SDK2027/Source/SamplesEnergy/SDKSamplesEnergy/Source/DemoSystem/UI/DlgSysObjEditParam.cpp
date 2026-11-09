#include "StdAfx.h"

#include "DlgSysObjEditParam.h"

// dialog control IDs
#define		kOK                   1
#define		kCancel               2
#define		kParamNameTxt         4
#define		kSwapCtrl             5
#define		kSwapBool             6
#define		kParamValueBool       7
#define		kSwapTxtInt           8
#define		kParamValueInt        9
#define		kSwapReal             10
#define		kParamValueReal       11
#define		kSwapTxt              12
#define		kParamValueTxt        13

using namespace DemoSystem::UI;
using namespace VectorWorks::EnergyAnalysis;

EVENT_DISPATCH_MAP_BEGIN( CDlgSysObjEditParam );
EVENT_DISPATCH_MAP_END;

CDlgSysObjEditParam::CDlgSysObjEditParam(const SParamInfo& paramInfo)
{
	// Assign settings tag to this dialog so it would save it's position and size automatically
	this->SetSavedSettingsTag( "SDKSamplesEnergy", "DlgSysObjEditParam" );

	fSwapPaneIndx	= (size_t)paramInfo.fParamType;
	fParamName		= paramInfo.fName;
	fParamValueBool = paramInfo.fBoolValue;
	fParamValueInt	= paramInfo.fIntValue;
	fParamValueReal = paramInfo.fDoubleValue;
	fParamValueTxt	= paramInfo.fStrValue;

	this->InitParamNameWidth();
}

CDlgSysObjEditParam::~CDlgSysObjEditParam()
{
}

bool CDlgSysObjEditParam::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "SDKSamplesEnergy/DialogLayout/DlgSysObjEditParam.vs" );
}

void CDlgSysObjEditParam::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	this->GetStaticTextCtrlByID( kParamNameTxt )->SetControlText( fParamName );
	this->GetSwapCtrlByID( kSwapCtrl )->SetActivePaneIndex( fSwapPaneIndx );
	this->GetCheckButtonCtrlByID( kParamValueBool )->SetState( fParamValueBool );
	this->GetEditIntegerCtrlByID( kParamValueInt )->SetEditInteger( fParamValueInt );
	this->GetEditRealCtrlByID( kParamValueReal )->SetEditReal( fParamValueReal, VWEditRealCtrl::kEditControlReal );
	this->GetEditTextCtrlByID( kParamValueTxt )->SetControlText( fParamValueTxt );
}

void CDlgSysObjEditParam::OnDDXInitialize()
{
	this->AddDDX_CheckButton( kParamValueBool, & fParamValueBool );
	this->AddDDX_EditInteger( kParamValueInt, & fParamValueInt );
	this->AddDDX_EditReal( kParamValueReal, & fParamValueReal, VWEditRealCtrl::kEditControlReal );
	this->AddDDX_EditText( kParamValueTxt, & fParamValueTxt );

}

void CDlgSysObjEditParam::OnUpdateUI()
{
	VWDialog::OnUpdateUI();
}

bool CDlgSysObjEditParam::GetParamValueBool() const
{
	return fParamValueBool;
}

Sint32 CDlgSysObjEditParam::GetParamValueInt() const
{
	return fParamValueInt;
}

double CDlgSysObjEditParam::GetParamValueDouble() const
{
	return fParamValueReal;
}

TXString CDlgSysObjEditParam::GetParamValueString() const
{
	return fParamValueTxt;
}

void CDlgSysObjEditParam::InitParamNameWidth()
{
	VectorWorks::Scripting::IVectorScriptEnginePtr scriptEngine( VectorWorks::Scripting::IID_VectorScriptEngine );
    if ( scriptEngine )
    {
		size_t nameLen = fParamName.GetLength();
		scriptEngine->Repository_SetValue( "v_ParamNameWidth", VWVariant( ( short )nameLen ) );
	}
}



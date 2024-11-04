#include "StdAfx.h"

#include "DlgWindowSettings.h"

// dialog control IDs
#define		kOK                   1
#define		kCancel               2
#define		kTxtObjOptions        4
#define		kTxtType              5
#define		kPopupType            6
#define		kTxtWidth             7
#define		kEditWidth            8
#define		kTxtHeight            9
#define		kEditHeight           10
#define		kChkHasTilting        11
#define		kSepEA                12
#define		kTxtEA                13
#define		kChkIncludeToEA       14
#define		kTxtUValue            15
#define		kRadioAutoCalc        16
#define		kTxtCalcValue         17
#define		kTxtCalcAutoUnit      18
#define		kRadioManCalc         19
#define		kEditUvalue           20
#define		kTxtCalcManUnit       21
#define		kTxtFrame             22
#define		kPopupFrame           23
#define		kTxtGlazing           24
#define		kPopupGlazing         25
#define		kSepShading           26
#define		kTxtShading           27
#define		kTxtGeneral           28
#define		kPopupGeneral         29
#define		kTxtSurroungind       30
#define		kPopupSurrounding     31
#define		kTxtSummShading       32
#define		kPopupSummShading     33
#define		kTxtAddShading        34
#define		kPopupAddShading      35
#define		kBtnAdvanced          36
#define		kTxtDoorType          37
#define		kPopupDoorType        38

using namespace DemoWindow::UI;
using namespace DemoWindow;

EVENT_DISPATCH_MAP_BEGIN( CDlgWindowSettings );
ADD_DISPATCH_EVENT( kEditWidth, OnDimensionChange );
ADD_DISPATCH_EVENT( kEditHeight, OnDimensionChange );
ADD_DISPATCH_EVENT( kChkHasTilting, OnChckBoxTilting );
ADD_DISPATCH_EVENT( kChkIncludeToEA, OnChckBoxIncludeToEA );
ADD_DISPATCH_EVENT( kRadioManCalc, OnRadioBtn );
ADD_DISPATCH_EVENT( kRadioAutoCalc, OnRadioBtn );
ADD_DISPATCH_EVENT( kEditUvalue, OnChangeUValue);
ADD_DISPATCH_EVENT( kPopupFrame, OnPopupFrame );
ADD_DISPATCH_EVENT( kPopupGlazing, OnPopupGlazing );
ADD_DISPATCH_EVENT( kPopupDoorType, OnPopupDoorType );
ADD_DISPATCH_EVENT( kPopupGeneral, OnPopupShadingGeneral );
ADD_DISPATCH_EVENT( kPopupSurrounding, OnPopupShadingSurround );
ADD_DISPATCH_EVENT( kPopupSummShading, OnPopupShadingSummerShading );
ADD_DISPATCH_EVENT( kPopupAddShading, OnPopupShadingAddShading );
ADD_DISPATCH_EVENT( kBtnAdvanced, OnBtnAdvanced );
ADD_DISPATCH_EVENT( kPopupType, OnPopupType );
EVENT_DISPATCH_MAP_END;

CDlgWindowSettings::CDlgWindowSettings(const Data::CWindowEnergyData& data, VectorWorks::EnergyAnalysis::IEnergyBuildingElementWinDoorPtr winDoorData)
: fEAUnits( VectorWorks::EnergyAnalysis::IID_EnergyUnits )
{
	// Assign settings tag to this dialog so it would save it's position and size automatically
	this->SetSavedSettingsTag( "SDKSamplesEnergy", "DlgWindowSettings" );

	fEAWinDoor		= winDoorData;
	
	// get pointers to system popups
	fEAFrame		= fEAWinDoor->GetFrame();
	fEAGlazing		= fEAWinDoor->GetGlazing();
	fEADoorType		= fEAWinDoor->GetDoorType();

	fPopupType		= (short)data.fType;
	fEditWidth		= data.fWidth;
	fEditHeight		= data.fHeight;
	fChkHasTilting	= data.fHasTilting;
	fChkIncludeToEA	= fEAWinDoor->GetIncludeInEnergyAnalysis();
	
	// enable/disable controls for auto/manual input of U value
	VectorWorks::EnergyAnalysis::ECalculationMode	calcMode	=  fEAWinDoor->GetUValueCalculationMode();
	fRadioAutoCalc	= calcMode == VectorWorks::EnergyAnalysis::ECalculationMode::Automatic;
	fRadioManCalc	= calcMode == VectorWorks::EnergyAnalysis::ECalculationMode::Manual;
	
	// get U value and set the edit manual control
	double	uvalue	= fEAWinDoor->GetUValue( true );
	if ( fEAUnits->IsUsedUValue() )
	{
		// U value
		fEditUvalue	= fEAUnits->ConvertX2Document( VectorWorks::EnergyAnalysis::EEnergyUnitType::WPSqMK, uvalue );
	}
	else
	{
		// R value
		double	rvalue	= 0;
		if ( ! ::DoubleIsNearlyZero(uvalue) )
		{
			rvalue	= 1 / uvalue;
		}
		fEditUvalue	= fEAUnits->ConvertX2Document( VectorWorks::EnergyAnalysis::EEnergyUnitType::SqMKPW, rvalue );
	}

	fPopupType	= (short)data.fType;
}

CDlgWindowSettings::~CDlgWindowSettings()
{
}

void CDlgWindowSettings::GetData(Data::CWindowEnergyData& outdata, VectorWorks::EnergyAnalysis::IEnergyBuildingElementWinDoorPtr& outWinDoorData) const
{
	outWinDoorData			= fEAWinDoor;
	outdata.fHasTilting		= fChkHasTilting;
	outdata.fHeight			= fEditHeight;
	outdata.fIncludeToEA	= fChkIncludeToEA;
	outdata.fType			= (Data::EType)fPopupType;
	outdata.fWidth			= fEditWidth;
}

bool CDlgWindowSettings::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "SDKSamplesEnergy/DialogLayout/DlgWindowSettings.vs" );
}

void CDlgWindowSettings::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	// fill type popup
	VWPullDownMenuCtrl*	popup	= this->GetPullDownMenuCtrlByID( kPopupType );
	popup->AddItem(TXResStr("ExtObjDemoWindow", "Type_Window"));
	popup->AddItem(TXResStr("ExtObjDemoWindow", "Type_Door"));
	popup->AddItem(TXResStr("ExtObjDemoWindow", "Type_WinDoor"));

	// fill & select system popups
	fEAFrame->DialogUI_Fill( this->GetDialogID(), kPopupFrame );
	fEAGlazing->DialogUI_Fill( this->GetDialogID(), kPopupGlazing );
	fEADoorType->DialogUI_Fill( this->GetDialogID(), kPopupDoorType );
	
	// fill & select shading popups:
	fEAWinDoor->DialogUI_Fill_ShadingGeneral( this->GetDialogID(), kPopupGeneral );
	fEAWinDoor->DialogUI_Fill_ShadingSurrounding( this->GetDialogID(), kPopupSurrounding );
	fEAWinDoor->DialogUI_Fill_ShadingSummer( this->GetDialogID(), kPopupSummShading );
	fEAWinDoor->DialogUI_Fill_ShadingAdditional( this->GetDialogID(), kPopupAddShading );

	// show units depending on settings
	TXString	textUnits	= fEAUnits->GetDocumentUnitString_X( fEAUnits->IsUsedUValue() ? VectorWorks::EnergyAnalysis::EEnergyUnitType::WPSqMK : VectorWorks::EnergyAnalysis::EEnergyUnitType::SqMKPW );
	this->GetStaticTextCtrlByID( kTxtCalcAutoUnit )->SetControlText( textUnits );
	this->GetStaticTextCtrlByID( kTxtCalcManUnit )->SetControlText( textUnits );

	// show R or U value, depending on documet units
	VWStaticTextCtrl*	txtUvalue	= this->GetStaticTextCtrlByID( kTxtUValue );
	TXString			text		= txtUvalue->GetControlText();
	text.Replace("^1", (const char*)fEAUnits->GetValueText(fEAUnits->IsUsedUValue()) );
	txtUvalue->SetControlText( text );

	// update the U value controls
	this->UpdateEnergyData();
	this->UpdateAutoUValueCtrl();
}

void CDlgWindowSettings::OnDDXInitialize()
{
	this->AddDDX_PulldownMenu( kPopupType, & fPopupType );
	this->AddDDX_EditReal( kEditWidth, & fEditWidth, VWEditRealCtrl::kEditControlReal );
	this->AddDDX_EditReal( kEditHeight, & fEditHeight, VWEditRealCtrl::kEditControlReal );
	this->AddDDX_CheckButton( kChkHasTilting, & fChkHasTilting );
	this->AddDDX_CheckButton( kChkIncludeToEA, & fChkIncludeToEA );
	this->AddDDX_RadioButton( kRadioAutoCalc, & fRadioAutoCalc );
	this->AddDDX_RadioButton( kRadioManCalc, & fRadioManCalc );
	this->AddDDX_EditReal( kEditUvalue, & fEditUvalue, VWEditRealCtrl::kEditControlReal );
}

void CDlgWindowSettings::OnUpdateUI()
{
	VWDialog::OnUpdateUI();

	// enable/disable controls for U-value depending on radio buttons
	this->EnableControl( kTxtUValue,		fChkIncludeToEA );
	this->EnableControl( kRadioAutoCalc,	fChkIncludeToEA );
	this->EnableControl( kTxtCalcValue,		fRadioAutoCalc && fChkIncludeToEA );
	this->EnableControl( kTxtCalcAutoUnit,	fRadioAutoCalc && fChkIncludeToEA );
	this->EnableControl( kRadioManCalc,		fChkIncludeToEA );
	this->EnableControl( kEditUvalue,		fRadioManCalc && fChkIncludeToEA );
	this->EnableControl( kTxtCalcManUnit,	fRadioManCalc && fChkIncludeToEA );
	this->EnableControl( kTxtFrame,			fPopupType != (short)Data::EType::Door && fChkIncludeToEA );
	this->EnableControl( kPopupFrame,		fPopupType != (short)Data::EType::Door && fChkIncludeToEA );
	this->EnableControl( kTxtGlazing,		fPopupType != (short)Data::EType::Door && fChkIncludeToEA );
	this->EnableControl( kPopupGlazing,		fPopupType != (short)Data::EType::Door && fChkIncludeToEA );
	this->EnableControl( kPopupDoorType,	fPopupType != (short)Data::EType::Window && fChkIncludeToEA );
	this->EnableControl( kTxtDoorType,		fPopupType != (short)Data::EType::Window && fChkIncludeToEA );
	this->EnableControl( kTxtShading,		fChkIncludeToEA );
	this->EnableControl( kTxtGeneral,		fChkIncludeToEA );
	this->EnableControl( kPopupGeneral,		fChkIncludeToEA );
	this->EnableControl( kTxtSurroungind,	fChkIncludeToEA );
	this->EnableControl( kPopupSurrounding, fChkIncludeToEA );
	this->EnableControl( kTxtSummShading,	fChkIncludeToEA );
	this->EnableControl( kPopupSummShading, fChkIncludeToEA );
	this->EnableControl( kTxtAddShading,	fChkIncludeToEA );
	this->EnableControl( kPopupAddShading,	fChkIncludeToEA );
	this->EnableControl( kBtnAdvanced,		fChkIncludeToEA );
}

void CDlgWindowSettings::OnDimensionChange(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	this->UpdateEnergyData();
	this->UpdateAutoUValueCtrl();
}

void CDlgWindowSettings::OnBtnAdvanced(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	fEAWinDoor->DialogUI_EditAdvancedOptionsDlg();
}

void CDlgWindowSettings::OnPopupFrame(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	// energy analysis plugin will take care for this control, just send the IDs
	fEAFrame->DialogUI_Select( this->GetDialogID(), kPopupFrame );
	fEAFrame->DialogUI_Fill( this->GetDialogID(), kPopupFrame );
	this->UpdateEnergyData();
	this->UpdateAutoUValueCtrl();
}

void CDlgWindowSettings::OnPopupGlazing(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	// energy analysis plugin will take care for this control, just send the IDs
	fEAGlazing->DialogUI_Select( this->GetDialogID(), kPopupGlazing );
	fEAGlazing->DialogUI_Fill( this->GetDialogID(), kPopupGlazing );
	this->UpdateEnergyData();
	this->UpdateAutoUValueCtrl();
}

void CDlgWindowSettings::OnPopupDoorType(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	// energy analysis plugin will take care for this control, just send the IDs
	fEADoorType->DialogUI_Select( this->GetDialogID(), kPopupDoorType );
	fEADoorType->DialogUI_Fill( this->GetDialogID(), kPopupDoorType );
	this->UpdateEnergyData();
	this->UpdateAutoUValueCtrl();
}

void CDlgWindowSettings::OnPopupShadingGeneral(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	// energy analysis plugin will take care for this control, just send the IDs
	fEAWinDoor->DialogUI_Select_ShadingGeneral( this->GetDialogID(), kPopupGeneral );
	fEAWinDoor->DialogUI_Fill_ShadingGeneral( this->GetDialogID(), kPopupGeneral );
}

void CDlgWindowSettings::OnPopupShadingSurround(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	// energy analysis plugin will take care for this control, just send the IDs
	fEAWinDoor->DialogUI_Select_ShadingSurrounding( this->GetDialogID(), kPopupSurrounding );
	fEAWinDoor->DialogUI_Fill_ShadingSurrounding( this->GetDialogID(), kPopupSurrounding );
}

void CDlgWindowSettings::OnPopupShadingSummerShading(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	// energy analysis plugin will take care for this control, just send the IDs
	fEAWinDoor->DialogUI_Select_ShadingSummer( this->GetDialogID(), kPopupSummShading );
	fEAWinDoor->DialogUI_Fill_ShadingSummer( this->GetDialogID(), kPopupSummShading );
}

void CDlgWindowSettings::OnPopupShadingAddShading(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	// energy analysis plugin will take care for this control, just send the IDs
	fEAWinDoor->DialogUI_Select_ShadingAdditional( this->GetDialogID(), kPopupAddShading );
	fEAWinDoor->DialogUI_Fill_ShadingAdditional( this->GetDialogID(), kPopupAddShading );
}

void CDlgWindowSettings::OnChangeUValue(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	if (eventArgs.GetEventData() == 1 /* kEditControlGainedFocus */ && fRadioManCalc )
	{
		// update the U value and be careful if there is used R-value or U value
		double uValue = 0.0;
		if ( fEAUnits->IsUsedUValue() )
		{
			uValue = fEditUvalue;
		}
		else
		{
			// R value
			if ( ! ::DoubleIsNearlyZero( fEditUvalue ) )
			{
				uValue = 1 / fEditUvalue;
			}
		}

		fEAWinDoor->SetUValue( fEAUnits->ConvertDocument2X( VectorWorks::EnergyAnalysis::EEnergyUnitType::SqMKPW, uValue ), true );
	}	
}

void CDlgWindowSettings::OnRadioBtn(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	// the way of U-value calculation is changed, update it
	fEAWinDoor->SetUValueCalculationMode( fRadioAutoCalc ? VectorWorks::EnergyAnalysis::ECalculationMode::Automatic : VectorWorks::EnergyAnalysis::ECalculationMode::Manual );
	if ( fRadioManCalc )
	{
		double uValue = 0.0;
		if ( fEAUnits->IsUsedUValue() )
		{
			uValue = fEditUvalue;
		}
		else
		{
			// R-value
			if ( ! ::DoubleIsNearlyZero( fEditUvalue ) )
			{
				uValue = 1 / fEditUvalue;
			}
		}

		fEAWinDoor->SetUValue( fEAUnits->ConvertDocument2X( VectorWorks::EnergyAnalysis::EEnergyUnitType::SqMKPW, uValue ), true );
	}

	// update auto U value controls to show actual U value
	this->UpdateAutoUValueCtrl();
}

void CDlgWindowSettings::OnChckBoxIncludeToEA (Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	fEAWinDoor->SetIncludeInEnergyAnalysis( fChkIncludeToEA );
}

void CDlgWindowSettings::OnPopupType(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	fEAWinDoor->SetType( ( VectorWorks::EnergyAnalysis::EWinDoorType )fPopupType );
	this->UpdateEnergyData();
	this->UpdateAutoUValueCtrl();
}

void CDlgWindowSettings::UpdateEnergyData()
{
	// when the dimensions of the window are changed the area is changed
	fEAWinDoor->SetArea( (fEditWidth * fEditHeight) / 1000000.0, true );	// !! be careful! The inerface expects sq meters !!
	
	// width is changed also
	fEAWinDoor->SetWidth( fEditWidth / 1000.0 );	// !! be careful! The inerface expects meters !!

	// glazing area is changed also
	if( fPopupType == (short)Data::EType::Window )
	{
		double	glazingArea	= (fEditWidth-kFrameThickness*2) * (fEditHeight-kFrameThickness*2);
		fEAWinDoor->SetGlazingArea( glazingArea / 1000000.0 );	// !! be careful! The inerface expects sq meters !!
	}
	else if( fPopupType == (short)Data::EType::Door )
	{
		double	glazingArea	= (fEditWidth-kFrameThickness*2) * (fEditHeight-kFrameThickness);
		fEAWinDoor->SetGlazingArea( glazingArea / 1000000.0 );	// !! be careful! The inerface expects sq meters !!
	}
	else
	{
		double width = fEditWidth / 2.0;
		double glazingArea	= (width-kFrameThickness*2) * (fEditHeight-kFrameThickness*2);
		fEAWinDoor->SetGlazingArea( glazingArea / 1000000.0 );	// !! be careful! The inerface expects sq meters !!
		fEAWinDoor->SetFrameArea( (fEditHeight * width) / 1000000.0 - glazingArea / 1000000.0 );

		glazingArea	= (width-kFrameThickness*2) * (fEditHeight-kFrameThickness);
		fEAWinDoor->SetGlazingArea( glazingArea / 1000000.0, VectorWorks::EnergyAnalysis::EValueType::HybridDoor );	// !! be careful! The inerface expects sq meters !!
		fEAWinDoor->SetFrameArea( (fEditHeight * width) / 1000000.0 - glazingArea / 1000000.0, VectorWorks::EnergyAnalysis::EValueType::HybridDoor );
	}

	// glazing length is changed also
	if( fPopupType == (short)Data::EType::Window )
	{
		double glazingLength = (fEditHeight-kFrameThickness*2)*2 + (fEditWidth-kFrameThickness*2)*2;
		fEAWinDoor->SetGlazingLength( glazingLength / 1000.0 );	// !! be careful! The inerface expects meters !!
	}
	else if( fPopupType == (short)Data::EType::Door )
	{
		double glazingLength = (fEditHeight-kFrameThickness)*2 + (fEditWidth-kFrameThickness*2)*2;
		fEAWinDoor->SetGlazingLength( glazingLength / 1000.0 );	// !! be careful! The inerface expects meters !!
	}
	else
	{
		double width = fEditWidth / 2.0;
		double glazingLength = (fEditHeight-kFrameThickness*2)*2 + (width-kFrameThickness*2)*2;
		fEAWinDoor->SetGlazingLength( glazingLength / 1000.0 );	// !! be careful! The inerface expects meters !!

		glazingLength = (fEditHeight-kFrameThickness)*2 + (width-kFrameThickness*2)*2;
		fEAWinDoor->SetGlazingLength( glazingLength / 1000.0, VectorWorks::EnergyAnalysis::EValueType::HybridDoor );	// !! be careful! The inerface expects meters !!
	}

	// frame length is changed also
	if( fPopupType == (short)Data::EType::Window )
	{
		double frameLength = fEditHeight*2 + fEditWidth*2;
		fEAWinDoor->SetFrameLength( frameLength / 1000.0 );	// !! be careful! The inerface expects meters !!
	}
	else if( fPopupType == (short)Data::EType::Door )
	{
		double frameLength = fEditHeight*2 + fEditWidth + kFrameThickness*2;
		fEAWinDoor->SetFrameLength( frameLength / 1000.0 );	// !! be careful! The inerface expects meters !!
	}
	else
	{
		double width = fEditWidth / 2.0;
		double frameLength = fEditHeight + width*2;
		fEAWinDoor->SetFrameLength( frameLength / 1000.0 );	// !! be careful! The inerface expects meters !!

		frameLength = fEditHeight + width + kFrameThickness*2;
		fEAWinDoor->SetFrameLength( frameLength / 1000.0, VectorWorks::EnergyAnalysis::EValueType::HybridDoor );	// !! be careful! The inerface expects meters !!
	}

	// update summer ventilation data. Clear width, clear height and clear area are changed.
		// Clear width is the rough opening minus twice the width of the window frame.
	double	clearWidth	= fEditWidth - 2*kFrameThickness;
		// Clear height is the rough opening minus twice the height of the window frame.
	double	clearHeight	= (Data::EType)fPopupType == Data::EType::Door ? fEditHeight - kFrameThickness : fEditHeight - 2*kFrameThickness;
		// Clear area is the area of the rough opening without the frame area.
	double	clearArea	= fEditWidth * fEditHeight;
	VectorWorks::EnergyAnalysis::SWinDoorSummerVentilationData	ventData;
	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayGF, ventData );
	ventData.fClearWidth	= clearWidth;
	ventData.fClearHeight	= clearHeight;
	ventData.fClearArea		= clearArea;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayGF, ventData );

	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayUF, ventData );
	ventData.fClearWidth	= clearWidth;
	ventData.fClearHeight	= clearHeight;
	ventData.fClearArea		= clearArea;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayUF, ventData );

	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::Night, ventData );
	ventData.fClearWidth	= clearWidth;
	ventData.fClearHeight	= clearHeight;
	ventData.fClearArea		= clearArea;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::Night, ventData );
}

void CDlgWindowSettings::UpdateAutoUValueCtrl()
{
	// set temporary the calculation mode to auto to force calculate the U value
	VectorWorks::EnergyAnalysis::ECalculationMode	calcMode	= fEAWinDoor->GetUValueCalculationMode();
	fEAWinDoor->SetUValueCalculationMode( VectorWorks::EnergyAnalysis::ECalculationMode::Automatic );
	double	uvalue	= fEAWinDoor->GetUValueAutoCalculated();
	fEAWinDoor->SetUValueCalculationMode( calcMode );

	if ( ! fEAUnits->IsUsedUValue() )
	{
		// show R value
		if ( ! ::DoubleIsNearlyZero(uvalue) )
		{
			uvalue	= 1 / uvalue;
		}
		else
		{
			uvalue	= 0;
		}
		uvalue = fEAUnits->ConvertX2Document( VectorWorks::EnergyAnalysis::EEnergyUnitType::SqMKPW, uvalue );
	}
	else
	{
		uvalue = fEAUnits->ConvertX2Document( VectorWorks::EnergyAnalysis::EEnergyUnitType::WPSqMK, uvalue );
	}
	
	VWStaticTextCtrl*	txtUvalueAuto	= this->GetStaticTextCtrlByID( kTxtCalcValue );
	TXString	textValue;
	textValue.Format("%.2f", uvalue );
	txtUvalueAuto->SetControlText( textValue );
}

void CDlgWindowSettings::OnChckBoxTilting(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	// tilting affects the summer ventilation data
	VectorWorks::EnergyAnalysis::SWinDoorSummerVentilationData	ventData;
	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayGF, ventData );
	ventData.fTilting	= fChkHasTilting;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayGF, ventData );

	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayUF, ventData );
	ventData.fTilting	= fChkHasTilting;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayUF, ventData );

	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::Night, ventData );
	ventData.fTilting	= fChkHasTilting;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::Night, ventData );
}

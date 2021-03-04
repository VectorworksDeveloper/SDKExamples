//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "ExtObjDemoWindow.h"
#include "ExtObjDemoWindow_ShapePane.h"
#include "Data/WindowEnergyData.h"
#include "UI/DlgWindowSettings.h"
#include "WindowObject.h"

using namespace DemoWindow;

namespace DemoWindow
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_DefaultPoint,
		/*ParametricName*/				"EnergyDemoWindow",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjDemoWindow", "DefaultTool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjDemoWindow", "DefaultTool_title"},
		/*Category*/					{"ExtObjDemoWindow", "DefaultTool_category"},
		/*HelpText*/					{"ExtObjDemoWindow", "DefaultTool_helptext"},
		/*VersionCreated*/				21,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*OverrideHelpID*/				"",
		/*IconSpec*/					"SDKSamplesEnergy/Images/ExtObjDemoWindowDefTool.png",
		/*CursorImageSpec*/				"",
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjDemoWindow", "LocalizedName"},
		/*SubType*/					kParametricSubType_Point,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

	static SParametricParamChc	gArrChoices[] = {
		//------
		// Type list
		{ 128,	"Window",				{"ExtObjDemoWindow", "Type_Window"} },
		{ 128,	"Door",					{"ExtObjDemoWindow", "Type_Door"} },
		{ 128,	"Win/Door",				{"ExtObjDemoWindow", "Type_WinDoor"} },
		//------
		// TERMINATE
		{ NULL, "", {0,0} }
	};

	static SParametricParamDef gArrParameters[] = {
		{ "Height",			{"ExtObjDemoWindow", "Height"},			"2\"",			"2\"",				kFieldCoordDisp,		0	},
		{ "Width",			{"ExtObjDemoWindow", "Width"},			"2\"",			"2\"",				kFieldCoordDisp,		0	},
		{ "Type",			{"ExtObjDemoWindow", "Type"},			"Window",		"Window",			kFieldPopUp,			128	},
		{ "HasTilting",		{"ExtObjDemoWindow", "HasTilting"},		"False",		"False",			kFieldBoolean,			0	},
		{ "__IsNew",		{"ExtObjDemoWindow", "__IsNew"},		"True",			"True",				kFieldBoolean,			0	},
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}


// --------------------------------------------------------------------------------------------------------
// {F1004345-EBC5-4651-B037-EE39942D5CB9}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjDemoWindow,
	/*Event sink*/		CObjDemoWindow_EventSink,
	/*Universal name*/	"EnergyDemoWindow",
	/*Version*/			1,
	/*UUID*/			0xf1004345, 0xebc5, 0x4651, 0xb0, 0x37, 0xee, 0x39, 0x94, 0x2d, 0x5c, 0xb9 );

// Test with VectorScript:
// SetSelect(CreateCustomObject('DemoWindow',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjDemoWindow::CExtObjDemoWindow(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjDemoWindow::~CExtObjDemoWindow()
{
}

void CExtObjDemoWindow::DefineSinks()
{
	this->DefineSink<CExtObjDemoWindow_ShapePane>( IID_ProviderShapePane );
}

// --------------------------------------------------------------------------------------------------------
// {F91BC0E1-8DA8-49E7-A9C3-B77B0830DE0F}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjDemoWindowDefTool,
	/*Event sink*/		VWToolEmpty_EventSink,
	/*Universal name*/	"DemoWindowTool",
	/*Version*/			1,
	/*UUID*/			0xf91bc0e1, 0x8da8, 0x49e7, 0xa9, 0xc3, 0xb7, 0x7b, 0x8, 0x30, 0xde, 0xf );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjDemoWindowDefTool::CExtObjDemoWindowDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjDemoWindowDefTool::~CExtObjDemoWindowDefTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjDemoWindow_EventSink::CObjDemoWindow_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjDemoWindow_EventSink::~CObjDemoWindow_EventSink()
{
}

EObjectEvent CObjDemoWindow_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );



	return kObjectEventNoErr;
}

EObjectEvent CObjDemoWindow_EventSink::Recalculate()
{
	DemoWindow::CWindowObject	object( fhObject );

	object.UpdateData();
	object.DrawObject();
	object.SaveObjectData();

	return kObjectEventNoErr;
}

EObjectEvent CObjDemoWindow_EventSink::Preference()
{
	EObjectEvent result	= kObjectEventNoErr;

	Data::CWindowEnergyData	data;
	data.LoadCurrentSettings();

	VectorWorks::EnergyAnalysis::IEnergyBuildingElementWinDoorPtr	energyData( VectorWorks::EnergyAnalysis::IID_EnergyBuildingElementWinDoor );
	energyData->LoadCreate( VWRecordFormatObj::GetRecordFormat( "EnergyDemoWindow" ) );

	DemoWindow::UI::CDlgWindowSettings	dlg( data, energyData );
	if ( dlg.RunDialogLayout( "SettingsDlg" ) == kDialogButton_Ok )
 	{
 		dlg.GetData( data, energyData );
 		data.SaveCurrentSettings();
 
 		energyData->Save();
 	}
 	else
 	{
 		result = kObjectEventPrefCancel;
 	}

	return result;
}

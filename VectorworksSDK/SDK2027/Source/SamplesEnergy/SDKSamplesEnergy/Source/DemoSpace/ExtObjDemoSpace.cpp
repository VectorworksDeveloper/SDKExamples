//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "ExtObjDemoSpace.h"
#include "ExtObjDemoSpace_ShapePane.h"
#include "DemoSpaceObject.h"
#include "UI/DlgSpaceSettings.h"

using namespace DemoSpace;
using namespace DemoSpace::UI;

namespace DemoSpace
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_Default2DPath,
		/*ParametricName*/				"EnergyDemoSpace",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjDemoSpace", "DefaultTool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjDemoSpace", "DefaultTool_title"},
		/*Category*/					{"ExtObjDemoSpace", "DefaultTool_category"},
		/*HelpText*/					{"ExtObjDemoSpace", "DefaultTool_helptext"},
		/*VersionCreated*/				21,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*OverrideHelpID*/				"",
		/*IconSpec*/					"SDKSamplesEnergy/Images/ExtObjDemoSpaceDefTool.png",
		/*CursorImageSpec*/				"",
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjDemoSpace", "LocalizedName"},
		/*SubType*/					kParametricSubType_2DPath,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

	static SParametricParamDef gArrParameters[] = {
		{ "Height",					{"ExtObjDemoSpace", "Height"},					"10'",		"3m",		kFieldCoordDisp,	0 },	// we use CoordDisp as we let VW manager the unit of this field
		{ "IsManualArea",			{"ExtObjDemoSpace", "IsManualArea"},			"False",	"False",	kFieldBoolean,		0 },
		{ "Area",					{"ExtObjDemoSpace", "Area"},					"0",		"0",		kFieldReal,			0 },	// we used real to save value at appropriate unit, then we use text as we manage the unit of this field
		{ "__IsNew",				{"", ""},										"true",		"true",		kFieldBoolean,		0 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}

// --------------------------------------------------------------------------------------------------------
// {DD1AC209-F01E-4F3A-A547-F842422BAF42}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjDemoSpaceDefTool,
	/*Event sink*/		VWToolEmpty_EventSink,
	/*Universal name*/	"SpacesEnergyTool",
	/*Version*/			1,
	/*UUID*/			0x6536c510, 0x3c32, 0x40b4, 0xb9, 0x35, 0xa, 0x5, 0xaf, 0x65, 0x6e, 0xa1 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjDemoSpaceDefTool::CExtObjDemoSpaceDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjDemoSpaceDefTool::~CExtObjDemoSpaceDefTool()
{
}


// --------------------------------------------------------------------------------------------------------
// {D255DD59-2FAD-4407-AACC-F548EB41A305}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjDemoSpace,
	/*Event sink*/		CObjDemoSpace_EventSink,
	/*Universal name*/	"EnergyDemoSpace",
	/*Version*/			1,
	/*UUID*/			0x7d8aaf5e, 0x4350, 0x4645, 0xb6, 0x9e, 0x2e, 0xec, 0x61, 0xd7, 0xa4, 0x15 );

// Test with VectorScript:
// SetSelect(CreateCustomObject('EnergyDemoSpace',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjDemoSpace::CExtObjDemoSpace(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters )
{
}

CExtObjDemoSpace::~CExtObjDemoSpace()
{
}

void CExtObjDemoSpace::DefineSinks()
{
	this->DefineSink<CExtObjSpacesEnergy_ShapePane>( IID_ProviderShapePane );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjDemoSpace_EventSink::CObjDemoSpace_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjDemoSpace_EventSink::~CObjDemoSpace_EventSink()
{
}

EObjectEvent CObjDemoSpace_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );



	return kObjectEventNoErr;
}

EObjectEvent CObjDemoSpace_EventSink::Recalculate()
{
	CDemoSpaceObject spaceObject( fhObject );

	spaceObject.DrawObject();
	spaceObject.SaveObjectData();	

	return kObjectEventNoErr;
}

 EObjectEvent CObjDemoSpace_EventSink::Preference()
 {
	 EObjectEvent result = kObjectEventNoErr;

	 CSpaceEnergyData data;
	 data.LoadCurrentSettings();

	 IEnergySpacePtr	energyData( IID_EnergySpace );
	 MCObjectHandle		hRecFormat	= VWRecordFormatObj::GetRecordFormat( "EnergyDemoSpace" );

	 if( !hRecFormat )
	 {
		 hRecFormat = VWParametricObj::DefineCustomObject( "EnergyDemoSpace", false );
	 }

	 energyData->LoadCreate( hRecFormat );

	 CDlgSpaceSettings dlg( data, energyData );

	if ( dlg.RunDialogLayout( "SettingsDlg" ) == kDialogButton_Ok )
	{
		dlg.GetData( data );
		data.SaveCurrentSettings();

		energyData->Save();
	}
	else
	{
		result = kObjectEventPrefCancel;
	}

	 return result;
 }

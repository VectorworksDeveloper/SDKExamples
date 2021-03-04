#include "StdAfx.h"

#include "ExtObjDemoSystem.h"
#include "ExtObjDemoSystem_ShapePane.h"
#include "UI/DlgSystemObjPrefs.h"
#include "SystemObject.h"

using namespace DemoSystem;

namespace DemoSystem
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_DefaultPoint,
		/*ParametricName*/				"EnergyDemoSystem",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjDemoSystem", "DefaultTool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjDemoSystem", "DefaultTool_title"},
		/*Category*/					{"ExtObjDemoSystem", "DefaultTool_category"},
		/*HelpText*/					{"ExtObjDemoSystem", "DefaultTool_helptext"},
		/*VersionCreated*/				23,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*OverrideHelpID*/				"",
		/*IconSpec*/					"SDKSamplesEnergy/Images/ExtToolDemoSystem.png",
		/*CursorImageSpec*/				"",
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjDemoSystem", "LocalizedName"},
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
		//------
		// TERMINATE
		{ NULL, "", {0,0} }
	};

	static SParametricParamDef gArrParameters[] = {
		{ "SystemObjectType",	{"ExtObjDemoSystem", "Type"},			"0",	"0",	kFieldLongInt,	0 },
		{ "ParamName",			{"ExtObjDemoSystem", "ParamNamePopup"}, "",		"",		kFieldPopUp,	0 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}

// --------------------------------------------------------------------------------------------------------
// {E886D30E-EFF5-4114-BCFB-FE2F1B53FA16}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjDemoSystem,
	/*Event sink*/		CObjDemoSystem_EventSink,
	/*Universal name*/	"EnergyDemoSystem",
	/*Version*/			1,
	/*UUID*/			0xe886d30e, 0xeff5, 0x4114, 0xbc, 0xfb, 0xfe, 0x2f, 0x1b, 0x53, 0xfa, 0x16 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjDemoSystem::CExtObjDemoSystem(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjDemoSystem::~CExtObjDemoSystem()
{
}

void CExtObjDemoSystem::DefineSinks()
{
	this->DefineSink<CExtObjDemoSystem_ShapePane>( IID_ProviderShapePane );
}

// --------------------------------------------------------------------------------------------------------
// {64253E7A-AB1A-45B1-99FC-48C9A3AA5398}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjDemoSystemDefTool,
	/*Event sink*/		VWToolEmpty_EventSink,
	/*Universal name*/	"DemoSystemTool",
	/*Version*/			1,
	/*UUID*/			0x64253e7a, 0xab1a, 0x45b1, 0x99, 0xfc, 0x48, 0xc9, 0xa3, 0xaa, 0x53, 0x98 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjDemoSystemDefTool::CExtObjDemoSystemDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjDemoSystemDefTool::~CExtObjDemoSystemDefTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjDemoSystem_EventSink::CObjDemoSystem_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjDemoSystem_EventSink::~CObjDemoSystem_EventSink()
{
}

EObjectEvent CObjDemoSystem_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );

	return kObjectEventNoErr;
}

EObjectEvent CObjDemoSystem_EventSink::Recalculate()
{
	DemoSystem::CSystemObject	object( fhObject, VWParametricObj( fhObject ).GetParamLong( "SystemObjectType" ) );

	object.DrawObject();
	object.Save();

	return kObjectEventNoErr;
}

EObjectEvent CObjDemoSystem_EventSink::Preference()
{
	EObjectEvent result	= kObjectEventNoErr;

	MCObjectHandle			hFormat = VWRecordFormatObj::GetRecordFormat( "EnergyDemoSystem" );
	short					sysType = VWRecordFormatObj( hFormat ).GetParamLong( "SystemObjectType" );
	UI::CDlgSystemObjPrefs	dlg		= UI::CDlgSystemObjPrefs( sysType );

	if( dlg.RunDialogLayout( "DlgSystemObjPrefs" ) == kDialogButton_Ok )
 	{
		VWRecordFormatObj( hFormat ).SetParamLong( "SystemObjectType", dlg.GetSystemValue() );
		VectorWorks::EnergyAnalysis::IEnergySystemObjectPtr energySysObj( VectorWorks::EnergyAnalysis::IID_EnergySystemObject );

		if( sysType != dlg.GetSystemValue() && energySysObj->IsHandleContainingData( hFormat ) )
		{
			energySysObj->DeleteDataFromHandle( hFormat );
		}

		energySysObj->LoadCreate( hFormat, (VectorWorks::EnergyAnalysis::ESystemObjectType)dlg.GetSystemValue() );
		energySysObj->Save();

		TXString paramName;
		VectorWorks::EnergyAnalysis::CSystemDataParam::EType type;
		VectorWorks::EnergyAnalysis::EEnergyUnitType unitType;

		energySysObj->GetParamInfo( 0, paramName, type, unitType );
		VWRecordFormatObj( hFormat ).SetParamString( "ParamName", paramName );
 	}
 	else
 	{
 		result = kObjectEventPrefCancel;
 	}

	return result;
}

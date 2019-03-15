#include "StdAfx.h"

#include "ExtObjAdvComplex.h"
#include "AdvComplexShapePane.h"
#include "AdvComplexReshape3D.h"

using namespace Advanced;

namespace Advanced
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef	gToolDef = {
		/*ToolType*/					eExtensionToolType_DefaultPoint,
		/*ParametricName*/				"AdvComplexObj",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"CExtObjAdvComplex", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"CExtObjAdvComplex", "tool_title"},
		/*Category*/					{"CExtObjAdvComplex", "tool_category"},
		/*HelpText*/					{"CExtObjAdvComplex", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*OverrideHelpID*/				"",
		/*Icon Specifier*/				"TesterModule/Images/CExtTool.png",
		/*Cursor Specifier */			""
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"CExtObjAdvComplex", "localized_name"},
		/*SubType*/					kParametricSubType_Point,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};


	static SParametricParamDef gArrParameters[] = {
		{ "p1",			{"CExtObjAdvComplex", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"CExtObjAdvComplex", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "layer",		{"CExtObjAdvComplex", "param3"},		"Proxy",	"Proxy",	kFieldLayersPopup,	0 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}


// --------------------------------------------------------------------------------------------------------
// {8A4B197E-B8FF-48F5-B05F-B99F29665D53}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjAdvComplex,
	/*Event sink*/		CObjAdvComplex_EventSink,
	/*Universal name*/	"AdvComplexObj",
	/*Version*/			1,
	/*UUID*/			0x8a4b197e, 0xb8ff, 0x48f5, 0xb0, 0x5f, 0xb9, 0x9f, 0x29, 0x66, 0x5d, 0x53 );

// Test with VectorScript:
// SetSelect(CreateCustomObject('AdvComplexObj',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjAdvComplex::CExtObjAdvComplex(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters )
//	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjAdvComplex::~CExtObjAdvComplex()
{
}

void CExtObjAdvComplex::DefineSinks()
{
	this->DefineSink<CAdvComplexShapePane>( IID_ProviderShapePane );
	this->DefineSink<CAdvComplexReshape3D>( IID_ProviderReshape3D );
}

// --------------------------------------------------------------------------------------------------------
// {3C3F9864-CA82-4417-BFF8-DE4FE7F6B902}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjAdvComplexDefTool,
	/*Event sink*/		VWToolEmpty_EventSink,
	/*Universal name*/	"AdvComplexObjTool",
	/*Version*/			1,
	/*UUID*/			0x3c3f9864, 0xca82, 0x4417, 0xbf, 0xf8, 0xde, 0x4f, 0xe7, 0xf6, 0xb9, 0x2 );

// SetSelect(CreateCustomObject('AdvComplexObjTool', 0,0,0) );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjAdvComplexDefTool::CExtObjAdvComplexDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjAdvComplexDefTool::~CExtObjAdvComplexDefTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjAdvComplex_EventSink::CObjAdvComplex_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjAdvComplex_EventSink::~CObjAdvComplex_EventSink()
{
}

EObjectEvent CObjAdvComplex_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );

	extProps->SetObjectProperty( objectID, kObjXPropSupportProxyObjects, true );

	return kObjectEventNoErr;
}

EObjectEvent CObjAdvComplex_EventSink::Recalculate()
{
	VWPoint3D	offset( 0, 0, 0 );

	MCObjectHandle	hProxyParent	= gSDK->GetProxyParent( fhObject );
	if ( hProxyParent == NULL )
	{
		VWParametricObj		paramObj( fhObject );

		TXString		layerName	= paramObj.GetParamString( "layer" );
		MCObjectHandle	hLayer		= gSDK->GetNamedLayer( layerName );
		gSDK->CreateProxyObjOnLayer( fhObject, hLayer );
	
		VWPolygon3DObj	poly;
		poly.AddVertex( offset + VWPoint3D(50, 10, 0) );
		poly.AddVertex( offset + VWPoint3D(100, 0, 0) );
		poly.AddVertex( offset + VWPoint3D(100, 100, 0) );
		poly.AddVertex( offset + VWPoint3D(10, 80, 0) );
		poly.SetClosed( true );

		VWPolygon2DObj	poly2D;
		poly2D.AddVertex( offset + VWPoint2D( - 100, 0 ) );
		poly2D.AddVertex( offset + VWPoint2D( 100, 0 ) );
		poly2D.AddVertex( offset + VWPoint2D( 0, 100 ) );
		poly2D.SetClosed( true );

		gSDK->AlertInform( "reset: main object" );
	}
	else
	{
		VWPolygon3DObj	poly;
		poly.AddVertex( offset + VWPoint3D(50, 100, 0) );
		poly.AddVertex( offset + VWPoint3D(100, 100, 0) );
		poly.SetClosed( true );

		VWLocus3DObj loc( VWPoint3D( 0, 0, 0 ) );

		VWPolygon2DObj	poly2D;
		poly2D.AddVertex( offset + VWPoint2D( - 100, 0 ) );
		poly2D.AddVertex( offset + VWPoint2D( - 20, 20 ) );
		poly2D.AddVertex( offset + VWPoint2D( 0, 100 ) );
		poly2D.AddVertex( offset + VWPoint2D( 20, 20 ) );
		poly2D.AddVertex( offset + VWPoint2D( 100, 0 ) );
		poly2D.SetClosed( true );

		gSDK->AlertInform( "reset: PROXY object" );
	}

	return kObjectEventNoErr;
}

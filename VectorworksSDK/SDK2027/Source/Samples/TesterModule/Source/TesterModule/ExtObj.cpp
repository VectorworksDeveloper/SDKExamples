#include "StdAfx.h"

#include "ExtObj.h"

using namespace TesterModule;

namespace TesterModule
{
	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"CExtObj", "localized_name"},
		/*SubType*/					kParametricSubType_Point,
		/*ResetOnMove*/				true,
		/*ResetOnRotate*/			true,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

	static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{"CExtObj", "choice1"} },
		{ 128,	"Arc",					{"CExtObj", "choice2"} },
		{ 128,	"Bezier",				{"CExtObj", "choice3"} },
		{ 128,	"None",					{"CExtObj", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"CExtObj", "choice5"} },
		//------
		// TERMINATE
		{ 0, "", {0,0} }
	};

	static SParametricParam2Def gArrParameters[] = {
		{ "p1",			{"CExtObj", "param1"},		kFieldBoolean		},
		{ "p2",			{"CExtObj", "param2"},		kFieldBoolean		},
		{ "p3",			{"CExtObj", "param3"},		kFieldText			},
		{ "p4",			{"CExtObj", "param4"},		kFieldText			},
		{ "p5",			{"CExtObj", "param5"},		kFieldCoordDisp	},
		{ "p6",			{"CExtObj", "param6"},		kFieldPopUp,		128 },
		{ "p7",			{"CExtObj", "param7"},		kFieldPopUp,		129 },
		{ "pAngle",		{"CExtObj", "param8"},		kFieldAngle			 },
		{ "pArea",		{"CExtObj", "param9"},		kFieldArea			 },
		{ "pVolume",	{"CExtObj", "param10"},		kFieldVolume		 },
		{ "pClass",		{"CExtObj", "param11"},		kFieldClassesPopup	 },
		{ "pLayer",		{"CExtObj", "param12"},		kFieldLayersPopup	 },

		{ "pFieldClass",			{"CExtObj", "param_FieldClass"},	kFieldClass	, 0,
			[](bool metric, const TXString& initialValue, const TXString& univParamName, IRecordItem* outValue)
			{
				outValue->SetFieldClass( gSDK->GetNoneClassID() );
			}},

		{ "pFieldBuildingMaterial",	{"CExtObj", "param_FieldBuildingMaterial"},		kFieldBuildingMaterial	},
		{ "pFieldFill",				{"CExtObj", "param_FieldFill"},					kFieldFill				},
		{ "pFieldPenStyle",			{"CExtObj", "param_FieldPenStyle"},				kFieldPenStyle			},
		{ "pFieldPenWeight",		{"CExtObj", "param_FieldPenWeight"},			kFieldPenWeight			},
		{ "pFieldColor",			{"CExtObj", "param_FieldColor"},				kFieldColor				},
		{ "pFieldTexture",			{"CExtObj", "param_FieldTexture"},				kFieldTexture			},
		{ "pFieldSymDef",			{"CExtObj", "param_FieldSymDef"},				kFieldSymDef			},

		// TERMINATE
		{  }
	};
}

// --------------------------------------------------------------------------------------------------------
// {3BA4CC4B-B330-4F61-9594-64D8E5BC803E}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObj,
	/*Event sink*/		CObj_EventSink,
	/*Universal name*/	"CExtObj",
	/*Version*/			1,
	/*UUID*/			0x3ba4cc4b, 0xb330, 0x4f61, 0x95, 0x94, 0x64, 0xd8, 0xe5, 0xbc, 0x80, 0x3e );
// Test:
// SetSelect(CreateCustomObject('CExtObj',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObj::CExtObj(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObj::~CExtObj()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObj_EventSink::CObj_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObj_EventSink::~CObj_EventSink()
{
}

EObjectEvent CObj_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );

	//...

	return kObjectEventNoErr;
}

EObjectEvent CObj_EventSink::Recalculate()
{
	VWParametricObj paramObj( fhObject );
	InternalIndex		pp1 = paramObj.GetParamClass			( "pFieldClass"				);
	InternalIndex		pp2 = paramObj.GetParamBuildingMaterial	( "pFieldBuildingMaterial"	);
	VWPattern			pp3 = paramObj.GetParamFill				( "pFieldFill"				);
	VWPattern			pp4 = paramObj.GetParamPenStyle			( "pFieldPenStyle"			);
	Uint8				pp5 = paramObj.GetParamPenWeight		( "pFieldPenWeight"			);
	ColorRef			pp6 = paramObj.GetParamColor			( "pFieldColor"				);
	InternalIndex		pp7 = paramObj.GetParamTexture			( "pFieldTexture"			);
	InternalIndex		pp8 = paramObj.GetParamSymDef			( "pFieldSymDef"			);

	pp1; 	pp2; 	pp3; 	pp4; 	pp5; 	pp6; 	pp7; 	pp8; 

	TransformMatrix	matrix;
	gSDK->GetEntityMatrix( fhObject, matrix );

	WorldPt	ptOrigin;
	gSDK->GetUserOriginFP( ptOrigin );

	TXString	strText1;
	strText1.Format( "ObjPos: x=%f y=%f       UserOriginFP: x=%f y=%f", matrix.P().x, matrix.P().y, ptOrigin.x, ptOrigin.y );
	VWTextBlockObj	textObj1( strText1 );

	return kObjectEventNoErr;
}

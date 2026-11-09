#include "StdAfx.h"

#include "ExtVSFunc.h"

using namespace TesterModule;

namespace TesterModule
{
	// --------------------------------------------------------------------------------------------------------
	SFunctionDef	gArrFunctionDefs[] = {
		{
			/* fName */				"Add",
			/* fCategory */			"Test Category",
			/* fDescription */		"This is test function",
			/* fVersion */			0,
			/* fScope */			0,
			/* fHasReturnValue */	true,
			/* fParams */ {
				{ "p1",					kIntegerArgType },
				{ "p2",					kIntegerArgType },
				{ "RETURN",				kIntegerArgType },
				{ NULL,					kIntegerArgType },
				{ NULL,					kIntegerArgType },
				{ NULL,					kIntegerArgType },
				{ NULL,					kIntegerArgType },
				{ NULL,					kIntegerArgType },
				{ NULL,					kIntegerArgType },
				{ NULL,					kIntegerArgType },
				{ NULL,					kIntegerArgType }
			}
		},
		// TERMINATE
		{ NULL, NULL, NULL, 0, 0, FALSE, { {NULL,kIntegerArgType}, {NULL,kIntegerArgType}, {NULL,kIntegerArgType}, {NULL,kIntegerArgType}, {NULL,kIntegerArgType}, {NULL,kIntegerArgType}, {NULL,kIntegerArgType}, {NULL,kIntegerArgType}, {NULL,kIntegerArgType}, {NULL,kIntegerArgType}, {NULL,kIntegerArgType} } }
	};
}

// --------------------------------------------------------------------------------------------------------
// {D5450395-6AAE-4F1B-889E-ADB7D1F583DE}
BEGIN_VWVSFunctions(
	/*Extension class*/	CExtVSFuncs,
	/*Universal name*/	"CExtVSFuncs",
	/*Version*/			1,
	/*UUID*/			0xd5450395, 0x6aae, 0x4f1b, 0x88, 0x9e, 0xad, 0xb7, 0xd1, 0xf5, 0x83, 0xde );
ADD_VWVSFunctions_ROUTINE( CMyVSRoutines );
END_VWVSFunctions;

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtVSFuncs::CExtVSFuncs(CallBackPtr cbp)
	: VWExtensionVSFunctions( cbp, gArrFunctionDefs )
{
}

CExtVSFuncs::~CExtVSFuncs()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
// define dispatch map
BEGIN_LIB_DISPATCH_MAP_Ex( CMyVSRoutines, gArrFunctionDefs );
	ADD_LIB_FUNCTION_Ex( "Add",			OnAdd	);
END_LIB_DISPATCH_MAP_Ex;

// --------------------------------------------------------------------------------------------------------
CMyVSRoutines::CMyVSRoutines()
{
}

CMyVSRoutines::~CMyVSRoutines()
{
}

void CMyVSRoutines::OnAdd(VWPluginLibraryArgTable& argTable)
{
	short	a	= argTable.GetArgument(0).GetArgInteger();
	short	b	= argTable.GetArgument(1).GetArgInteger();

	argTable.GetResult().SetArgInteger( a + b );
}


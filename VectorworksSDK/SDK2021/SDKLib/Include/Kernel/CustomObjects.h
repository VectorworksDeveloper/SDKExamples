//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Utility functions and custom resource structures for Plug-in Objects.
//

#ifndef _CustomObjects_
#define _CustomObjects_

#include "RecordHandler.h"		// need type FormatHandle

//====================================================================================================
//	STRUCTS
//
//	Structure definitions that coorespond to custom resource templates in GSTMPL.rsrc
//
//====================================================================================================

//--------------------------------------------------
//	'Prm#'	Parameter resource.
//--------------------------------------------------
#define OST_Prm							'Prm#'
const short kUnivParmResID				= 128;

// UnivParmSpec is the repeating part of the 'Prm#' resource in memory.
//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
struct UnivParmSpec {
	Str63	fUniversalName;		// Universal Name of a Parameter.  Limited to 20 characters as of VW 10.
	Str63	fLocalizedName;		// Localized Name of a Parameter.  Supports up to 63 characters.
	Str255	fDefaultValue;		// Default value for this parameter.  If text, it is Localized.
	Byte	fPad;				// pad byte
	Byte	fType;				// Type of this parameter.  Constants define in MiniCadCallBacks.h
	short 	fChoices;			// For parameters of type Popup or Radio, this is the resource ID of possible choices.
};
#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
//--------------------------------------------------------------------

typedef struct UnivParmSpec UnivParmSpec, *UnivParmSpecPtr;
typedef UnivParmSpec UnivParmSpecArray[1];

// UnivParmTable is an entire 'Prm#' resource in memory.  Call GetResource and assign resulting handle to a UnivParmTabHandle.
//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
struct UnivParmTable {
	short 				numParms;		// number of entries in the following array.
	UnivParmSpecArray	parms;			// array of UnivParmSpec structs
};
#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
//--------------------------------------------------------------------

typedef struct UnivParmTable *UnivParmTabPtr, **UnivParmTabHandle;


//--------------------------------------------------
//	'Chc#'	Choice resource stores choices for popup and radio button parameter.
//--------------------------------------------------
#define OST_Chc								'Chc#'
// The resource id of the Chc# resource is specified in the fChoices field of a Prm# resource for a specific parameter.

// The "ParmChoice" structure describes one entry in a 'Chc#' resource.  It contains a pair of names.
//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
struct ParmChoice {
	Str255	fUniversalChoiceName;		// Universal Name of a Popup or Radio choice.
	Str255	fLocalizedChoiceName;		// Localized Name of a Popup or Radio choice.
};
#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
//--------------------------------------------------------------------

typedef struct ParmChoice ParmChoice, *ParmChoicePtr;
typedef ParmChoice ParmChoiceArray[1]; 

// The "ParmChoiceTable" structure describes the entire 'Chc#' resource in memory.   Call GetResource and assign resulting handle to a ParmChoiceTabHandle.
//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
struct ParmChoiceTable {
	short 				numChoices;		// number of entries in the following array.
	ParmChoiceArray		choices;		// array of ParmChoice structs.
};
#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
//--------------------------------------------------------------------

typedef struct ParmChoiceTable *ParmChoiceTabPtr, **ParmChoiceTabHandle;


//====================================================================================================
//	FUNCTIONS
//
// Convenience functions for use by the plug-in tool and regeneration code.
//
//====================================================================================================
Boolean GetCustomObjectDefinition(CallBackPtr cbp, MCObjectHandle parmHand, MCObjectHandle& recordHand, MCObjectHandle& formatHand);

#endif
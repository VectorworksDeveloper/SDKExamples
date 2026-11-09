//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Utility functions for SDK Plug-in Objects.
//

#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-COMMENT LINE.  [DMB, 10/30/95]



//====================================================================================================
//	STRUCTS
//
//====================================================================================================


// Plug-in Object Definition Resource
// This resource is used to define the name of an SDK Plug-in Object. 
// It contains two names: a universal name and a localizable name. 
// The universal name is set by the developer of the plug-in, and should never be changed. 
// The localizable name can be changed by distributors who are localizing the product for 
// a different language.  It can be translated.  
// VectorWorks will always display the localizable name in the user interface.
// (If the localizable name is empty then the universal name is displayed.)
// This resource was added for VectorWorks 10.0.0.  
//
// New for VW 10.0.0.
#define OST_PDEf						'PDEf'	
const short kPluginObjDefResID			= 128;
//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)

struct PluginObjDef {
	TXString universalName;	// universal name should NOT be changed when translating plug-ins.
	TXString displayName; 	// localizable name should be translated to appropriate language.
	short version;
};
#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
//--------------------------------------------------------------------

typedef struct PluginObjDef *PluginObjDefPtr, **PluginObjDefHand;

/*
//----------------------------------------------------------------------------
Boolean GetCustomObjectDefinition(CallBackPtr cbp, MCObjectHandle parmHand, RecordHandle& recordHand, FormatHandle& formatHand)
//
//	Should only be called from Regeneration code, not from Tool code.
//	Given handle to object instance, retrieve its record node and format node.
//	Returns true if successful.
//
{
	Boolean found = false;

	// Loop to find record among all record nodes on aux list.
	RecordHandle record = (RecordHandle) GS_FindAuxObject( cbp, MCObjectHandle(parmHand), recordNode);
	FormatHandle format = NULL;
	while( record && !found){
		format = (FormatHandle) GS_GetDefinition(cbp, (MCObjectHandle) record);
		if (format) {
			TFormatHandler currFormatHandler((MCObjectHandle)format);
			if (currFormatHandler.IsParametric()) {
				// If we find a recordNode on the aux list of the kParametricNode, and its formatNode has the parametric bit set,
				// then we can assume it is "the one".  No name checking is necessary.  JAK 9/27/99 Fix for VW 8.5.0.
				found = true;
			}
		}

		if (found == false)
			record = (RecordHandle) GS_NextAuxObject(cbp, GS_NextObject(cbp, (MCObjectHandle)record), recordNode);	// loop increment			
	}
	
	if (found) {
		recordHand = RecordHandle(record);
		formatHand = FormatHandle(format);
		return true;
	}
	else {
		DSTOP((kJeff, "Regenerate function failed to find a record or format for this parametric.\n"));
		return false;
	}
}
*/
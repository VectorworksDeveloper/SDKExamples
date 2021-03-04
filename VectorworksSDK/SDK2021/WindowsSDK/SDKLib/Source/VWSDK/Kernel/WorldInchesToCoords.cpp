//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Provides implementation for two functions that convert from 
// Minicad coords to worldSpace inches.
//


#include "StdHeaders.h"

#include "Kernel/WorldInchesToCoords.h"

// This must follow all header files.
#undef THIS_FILE
DECLARE_THIS_FILE


Boolean GS_API WorldInchesToCoords(CallBackPtr UNUSED(cbp), double_param inches, WorldCoord& coords)
{ 	
	coords = inches * kWorldCoordsPerInch;
	return true; 
} 

double_gs CoordsToWorldInches(CallBackPtr UNUSED(cbp), WorldCoord coords)
{ 	
	return coords / kWorldCoordsPerInch;
} 

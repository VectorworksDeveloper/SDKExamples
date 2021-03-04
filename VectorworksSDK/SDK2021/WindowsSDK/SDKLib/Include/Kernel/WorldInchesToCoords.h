//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Provides implementation for two functions that convert from 
// Minicad coords to worldSpace inches.
//

#ifndef WORLD_INCH_TO_COORDS
#define WORLD_INCH_TO_COORDS

#pragma once

#include "MiniCadCallBacks.h"

Boolean GS_API WorldInchesToCoords(CallBackPtr cbp, double_param inches, WorldCoord& coords);

double_gs GS_API CoordsToWorldInches(CallBackPtr cbp, WorldCoord coords);

#endif


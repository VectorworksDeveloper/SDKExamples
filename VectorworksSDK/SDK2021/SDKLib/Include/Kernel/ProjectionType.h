//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// This file contains the definition of the ProjectionType structure, which stores
// information about the viewpoint, type of projection, and current rendering mode.
// This was split off from MinicadCallbacks.h to reduce dependencies.
//

#ifndef _PROJECTIONTYPE_H_
#define _PROJECTIONTYPE_H_ 1
#pragma once

#include "MCCoordTypes.h"

//////////////////////////////////////////////////////////////////////////////////////////
// ProjectionType

//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

struct ProjectionType {
	const TransformMatrix&  ScreenMatrix() const { return screenMatrix; }
	short RenderMode() const { return render; }
	short Projection() const { return projection; }

	void SetTransformMatrix(const TransformMatrix&  matrix)
		{ screenMatrix = matrix; }
	void SetRenderMode(short newMode) { render = newMode; }
	void SetProjection(short newProjection) { projection = newProjection; }

	ProjectionType& operator=(const ProjectionType& inProj)	{ memcpy(this, &inProj, sizeof(ProjectionType)); return *this; }

	int Compare(const ProjectionType& inRight, bool inbIncludeRenderMode) const
	// Returns
	//  1	- we are greater than inRight
	//  0	- we are equal to inRight
	// -1	- we are less than inRight
	{
		int outResult = 1;

		int matResult = screenMatrix.Compare(inRight.screenMatrix);

		if (matResult != 0)
			outResult = matResult;
		else {

			if (projection < inRight.projection)
				outResult = -1;
			else if (projection == inRight.projection) {

				if (clipDistance < inRight.clipDistance)
					outResult = -1;
				else if (clipDistance == inRight.clipDistance) {

					if (crsPersDistance < inRight.crsPersDistance)
						outResult = -1;
					else if (crsPersDistance == inRight.crsPersDistance) {
						int clipResult = projClipRect.Compare(inRight.projClipRect);

						if ( ! inbIncludeRenderMode)
							outResult = clipResult;
						else {

							if (clipResult != 0)
								outResult = clipResult;
							else {

								if (render < inRight.render)
									outResult = -1;
								else if (render == inRight.render)
									outResult = 0;
							}
						}
					}
				}
			}
		}

		return outResult;
	}

	TransformMatrix			screenMatrix;
	short					projection;
	short					render;
	WorldCoord				crsPersDistance;
	WorldCoord				clipDistance;
	WorldRect				projClipRect;
	
	void ByteSwap();
	/**
		Translates old Lightworks modes of rendering to the new Maxon modes of rendering.
	 
		@created Lyndsey Ferguson
		@date 04/23/2010
	*/
	void TranslateToRenderModeVW2011();
};
#pragma pack(pop)	// END 2 BYTE STUCTURE AIGNMENT <.vwx file format>


#endif // _PROJECTIONTYPE_H_

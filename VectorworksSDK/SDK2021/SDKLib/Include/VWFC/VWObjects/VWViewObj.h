//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "VWLayerObj.h"
#include "VWClass.h"

namespace VWFC
{
	using namespace VectorWorks;

	namespace VWObjects
	{
		// ---------------------------------------------------------------------------------
		class VWViewObj : public VWObject
		{
		public:
						VWViewObj();
						VWViewObj(const VWViewObj& src);
						VWViewObj(MCObjectHandle hView);
						virtual		~VWViewObj();

			VWViewObj&	operator=(const VWViewObj& src);

			size_t		GetNumLayers();
			void		GetLayerVisibility(size_t index, InternalIndex& outName, ELayerVisibility& outVisibility);

			size_t		GetNumClasses();
			void		GetClassVisibility(size_t index, InternalIndex& outClassID, EClassVisibility& outVisibility);

			TransformMatrix GetMatrix();

			void		StoreView();
			void		RestoreView();

			// Return true if the specified object handle is a view object
			static bool		IsViewObject(MCObjectHandle hObj);

		private:
			GSHandle	fhViewObj;
		};
	}
}

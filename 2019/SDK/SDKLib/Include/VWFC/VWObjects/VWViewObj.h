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
			virtual		~VWViewObj();

			VWViewObj&	operator=(const VWViewObj& src);

			size_t		GetNumLayers();
			void		GetLayerVisibility(size_t index, InternalIndex& outName, ELayerVisibility& outVisibility);

			size_t		GetNumClasses();
			void		GetClassVisibility(size_t index, InternalIndex& outClassID, EClassVisibility& outVisibility);

			void		StoreView();
			void		RestoreView();

		private:
			GSHandle	fhViewObj;
		};
	}
}
